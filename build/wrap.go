// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

// +build none

package main

import (
	"bytes"
	"errors"
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strings"
)

// nobuild can be used the prevent the wrappers from triggering a build after
// each step. This should only be used in production mode when there's a final
// build check outside of the wrapping.
var nobuild = flag.Bool("nobuild", false, "Prevents the wrappers from building")

func main() {
	flag.Parse()

	// Clean up any previously generated files
	files, err := ioutil.ReadDir(".")
	if err != nil {
		panic(err)
	}
	for _, file := range files {
		if file.IsDir() {
			if strings.HasSuffix(file.Name(), "_config") {
				os.RemoveAll(file.Name())
			}
			continue
		}
		if strings.HasSuffix(file.Name(), ".go") {
			os.Remove(file.Name())
		}
	}
	// Wrap each of the component libraries into megator
	if _, err := wrapZlib(*nobuild); err != nil {
		panic(err)
	}
	if _, err := wrapLibevent(*nobuild); err != nil {
		panic(err)
	}
	if _, err := wrapOpenSSL(*nobuild); err != nil {
		panic(err)
	}
	if _, err := wrapTor(*nobuild); err != nil {
		panic(err)
	}
	// Copy in the tor entrypoint wrapper
	blob, _ := ioutil.ReadFile(filepath.Join("build", "libtor.go.in"))
	ioutil.WriteFile("libtor.go", blob, 0644)
}

// wrapZlib clones the zlib library into the local repository and wraps it into
// a Go package.
//
// Zlib is a small and simple C library which can be wrapped by inserting an empty
// Go file among the C sources, causing the Go compiler to pick up all the loose
// sources and build them together into a static library.
func wrapZlib(nobuild bool) (string, error) {
	// Clone the upstream repository to wrap, it's fairly inactive, get master
	os.RemoveAll("zlib")

	cloner := exec.Command("git", "clone", "--depth", "1", "https://github.com/madler/zlib")
	cloner.Stdout = os.Stdout
	cloner.Stderr = os.Stderr

	if err := cloner.Run(); err != nil {
		return "", err
	}
	// Save the latest upstream commit hash for later reference
	parser := exec.Command("git", "rev-parse", "HEAD")
	parser.Dir = "zlib"

	commit, err := parser.CombinedOutput()
	if err != nil {
		fmt.Println(string(commit))
		return "", err
	}
	// Wipe everything from the library that's non-essential
	files, err := ioutil.ReadDir("zlib")
	if err != nil {
		return "", err
	}
	for _, file := range files {
		if file.IsDir() {
			os.RemoveAll(filepath.Join("zlib", file.Name()))
			continue
		}
		if ext := filepath.Ext(file.Name()); ext != ".h" && ext != ".c" {
			os.Remove(filepath.Join("zlib", file.Name()))
		}
	}
	// Generate Go wrappers for each C source individually
	for _, file := range files {
		if file.IsDir() {
			continue
		}
		if ext := filepath.Ext(file.Name()); ext == ".c" {
			name := strings.TrimSuffix(file.Name(), ext)
			ioutil.WriteFile("zlib_"+name+".go", []byte(fmt.Sprintf(zlibTemplate, name)), 0644)
		}
	}
	ioutil.WriteFile("zlib_preamble.go", []byte(zlibPreamble), 0644)

	// Ensure the library builds
	if !nobuild {
		builder := exec.Command("go", "install")
		builder.Stdout = os.Stdout
		builder.Stderr = os.Stderr

		return string(commit), builder.Run()
	}
	return string(commit), nil
}

// zlibPreamble is the CGO preamble injected to configure the C compiler.
var zlibPreamble = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/zlib
*/
import "C"
`

// zlibTemplate is the source file template used in zlib Go wrappers.
var zlibTemplate = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#include <zlib/%s.c>
*/
import "C"
`

// wrapLibevent clones the libevent library into the local repository and wraps
// it into a Go package.
//
// Libevent is a fairly straightforward C library, however it heavily relies on
// makefiles to mix-and-match the correct sources for the correct platforms. It
// also relies on autoconf and family to generate platform specific configs.
//
// Since it's not meaningfully feasible to build libevent without the make tools,
// yet that approach cannot create a portable Go library, we're going to hook
// into the original build mechanism and use the emitted events as a driver for
// the Go wrapping.
func wrapLibevent(nobuild bool) (string, error) {
	// Clone the upstream repository to wrap, it's fairly inactive, get master
	os.RemoveAll("libevent")

	cloner := exec.Command("git", "clone", "--depth", "1", "https://github.com/libevent/libevent")
	cloner.Stdout = os.Stdout
	cloner.Stderr = os.Stderr

	if err := cloner.Run(); err != nil {
		return "", err
	}
	// Save the latest upstream commit hash for later reference
	parser := exec.Command("git", "rev-parse", "HEAD")
	parser.Dir = "libevent"

	commit, err := parser.CombinedOutput()
	if err != nil {
		fmt.Println(string(commit))
		return "", err
	}
	// Configure the library for compilation
	autogen := exec.Command("./autogen.sh")
	autogen.Dir = "libevent"
	autogen.Stdout = os.Stdout
	autogen.Stderr = os.Stderr

	if err := autogen.Run(); err != nil {
		return "", err
	}
	configure := exec.Command("./configure", "--disable-shared", "--enable-static")
	configure.Dir = "libevent"
	configure.Stdout = os.Stdout
	configure.Stderr = os.Stderr

	if err := configure.Run(); err != nil {
		return "", err
	}
	// Hook the make system and gather the needed sources
	maker := exec.Command("make", "--dry-run", "libevent.la")
	maker.Dir = "libevent"

	out, err := maker.CombinedOutput()
	if err != nil {
		fmt.Println(string(out))
		return "", err
	}
	deps := regexp.MustCompile("source='([a-z_]+)\\.c'").FindAllStringSubmatch(string(out), -1)

	// Wipe everything from the library that's non-essential
	files, err := ioutil.ReadDir("libevent")
	if err != nil {
		return "", err
	}
	for _, file := range files {
		// Remove all folders apart from the headers
		if file.IsDir() {
			if file.Name() == "include" || file.Name() == "compat" {
				continue
			}
			os.RemoveAll(filepath.Join("libevent", file.Name()))
			continue
		}
		// Remove all files apart from the sources and license
		if file.Name() == "LICENSE" {
			continue
		}
		if ext := filepath.Ext(file.Name()); ext != ".h" && ext != ".c" {
			os.Remove(filepath.Join("libevent", file.Name()))
		}
	}
	// Generate Go wrappers for each C source individually
	for _, dep := range deps {
		ioutil.WriteFile("libevent_"+dep[1]+".go", []byte(fmt.Sprintf(libeventTemplate, dep[1])), 0644)
	}
	ioutil.WriteFile("libevent_preamble.go", []byte(libeventPreamble), 0644)

	// Inject the configuration headers and ensure everything builds
	os.MkdirAll(filepath.Join("libevent_config", "event2"), 0755)
	blob, _ := ioutil.ReadFile(filepath.Join("config", "libevent", "event-config.h"))
	ioutil.WriteFile(filepath.Join("libevent_config", "event2", "event-config.h"), blob, 0644)

	if !nobuild {
		builder := exec.Command("go", "install")
		builder.Stdout = os.Stdout
		builder.Stderr = os.Stderr

		return string(commit), builder.Run()
	}
	return string(commit), nil
}

// libeventPreamble is the CGO preamble injected to configure the C compiler.
var libeventPreamble = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/libevent_config
#cgo CFLAGS: -I${SRCDIR}/libevent
#cgo CFLAGS: -I${SRCDIR}/libevent/compat
#cgo CFLAGS: -I${SRCDIR}/libevent/include
*/
import "C"
`

// libeventTemplate is the source file template used in libevent Go wrappers.
var libeventTemplate = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#include <compat/sys/queue.h>
#include <%s.c>
*/
import "C"
`

// wrapOpenSSL clones the OpenSSL library into the local repository and wraps
// it into a Go package.
//
// OpenSSL is a fairly complex C library, heavily relying on makefiles to mix-
// and-match the correct sources for the correct platforms and it also relies on
// platform specific assembly sources for more performant builds.
//
// Since it's not meaningfully feasible to build OpenSSL without the make tools,
// yet that approach cannot create a portable Go library, we're going to hook
// into the original build mechanism and use the emitted events as a driver for
// the Go wrapping.
//
// In addition, assembly is disabled altogether to retain Go's portability. This
// is a downside we unfortunately have to live with for now.
func wrapOpenSSL(nobuild bool) (string, error) {
	// Clone the upstream repository to wrap
	os.RemoveAll("openssl")

	cloner := exec.Command("git", "clone", "https://github.com/openssl/openssl")
	cloner.Stdout = os.Stdout
	cloner.Stderr = os.Stderr

	if err := cloner.Run(); err != nil {
		return "", err
	}
	// OpenSSL is a security concern, switch to the latest stable code
	brancher := exec.Command("git", "branch", "-a")
	brancher.Dir = "openssl"

	out, err := brancher.CombinedOutput()
	if err != nil {
		return "", err
	}
	stables := regexp.MustCompile("remotes/origin/(OpenSSL_[0-9]_[0-9]_[0-9]-stable)").FindAllSubmatch(out, -1)
	if len(stables) == 0 {
		return "", errors.New("no stable branch found")
	}
	switcher := exec.Command("git", "checkout", string(stables[len(stables)-1][1]))
	switcher.Dir = "openssl"

	if out, err = switcher.CombinedOutput(); err != nil {
		fmt.Println(string(out))
		return "", err
	}
	// Save the latest upstream commit hash for later reference
	parser := exec.Command("git", "rev-parse", "HEAD")
	parser.Dir = "openssl"

	commit, err := parser.CombinedOutput()
	if err != nil {
		fmt.Println(string(commit))
		return "", err
	}
	// Configure the library for compilation
	config := exec.Command("./config", "no-shared", "no-dso", "no-zlib", "no-asm", "no-async")
	config.Dir = "openssl"
	config.Stdout = os.Stdout
	config.Stderr = os.Stderr

	if err := config.Run(); err != nil {
		return "", err
	}
	// Hook the make system and gather the needed sources
	maker := exec.Command("make", "--dry-run")
	maker.Dir = "openssl"

	if out, err = maker.CombinedOutput(); err != nil {
		fmt.Println(string(out))
		return "", err
	}
	deps := regexp.MustCompile("(?m)([a-z0-9_/-]+)\\.c$").FindAllStringSubmatch(string(out), -1)

	// Wipe everything from the library that's non-essential
	files, err := ioutil.ReadDir("openssl")
	if err != nil {
		return "", err
	}
	for _, file := range files {
		// Remove all folders apart from the headers
		if file.IsDir() {
			if file.Name() == "crypto" || file.Name() == "engines" || file.Name() == "include" || file.Name() == "ssl" {
				continue
			}
			os.RemoveAll(filepath.Join("openssl", file.Name()))
			continue
		}
		// Remove all files apart from the license and sources
		if file.Name() == "LICENSE" {
			continue
		}
		if ext := filepath.Ext(file.Name()); ext != ".h" && ext != ".c" {
			os.Remove(filepath.Join("openssl", file.Name()))
		}
	}
	// Generate Go wrappers for each C source individually
	for _, dep := range deps {
		// Skip any files not needed for the library
		if strings.HasPrefix(dep[1], "apps/") {
			continue
		}
		if strings.HasPrefix(dep[1], "fuzz/") {
			continue
		}
		if strings.HasPrefix(dep[1], "test/") {
			continue
		}
		// Anything else is wrapped directly with Go
		gofile := strings.Replace(dep[1], "/", "_", -1) + ".go"
		ioutil.WriteFile("openssl_"+gofile, []byte(fmt.Sprintf(opensslTemplate, dep[1])), 0644)
	}
	ioutil.WriteFile("openssl_preamble.go", []byte(opensslPreamble), 0644)

	// Inject the configuration headers and ensure everything builds
	os.MkdirAll(filepath.Join("openssl_config", "internal"), 0755)
	blob, _ := ioutil.ReadFile(filepath.Join("config", "openssl", "bn_conf.h"))
	ioutil.WriteFile(filepath.Join("openssl_config", "internal", "bn_conf.h"), blob, 0644)

	blob, _ = ioutil.ReadFile(filepath.Join("config", "openssl", "dso_conf.h"))
	ioutil.WriteFile(filepath.Join("openssl_config", "internal", "dso_conf.h"), blob, 0644)

	blob, _ = ioutil.ReadFile(filepath.Join("config", "openssl", "buildinf.h"))
	ioutil.WriteFile(filepath.Join("openssl_config", "buildinf.h"), blob, 0644)

	os.MkdirAll(filepath.Join("openssl_config", "openssl"), 0755)
	blob, _ = ioutil.ReadFile(filepath.Join("config", "openssl", "opensslconf.h"))
	ioutil.WriteFile(filepath.Join("openssl_config", "openssl", "opensslconf.h"), blob, 0644)

	if !nobuild {
		builder := exec.Command("go", "install")
		builder.Stdout = os.Stdout
		builder.Stderr = os.Stderr

		return string(commit), builder.Run()
	}
	return string(commit), nil
}

// opensslPreamble is the CGO preamble injected to configure the C compiler.
var opensslPreamble = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/openssl_config
#cgo CFLAGS: -I${SRCDIR}/openssl
#cgo CFLAGS: -I${SRCDIR}/openssl/include
#cgo CFLAGS: -I${SRCDIR}/openssl/crypto/include
#cgo CFLAGS: -I${SRCDIR}/openssl/crypto/ec/curve448
#cgo CFLAGS: -I${SRCDIR}/openssl/crypto/ec/curve448/arch_32
#cgo CFLAGS: -I${SRCDIR}/openssl/crypto/modes
*/
import "C"
`

// opensslTemplate is the source file template used in OpenSSL Go wrappers.
var opensslTemplate = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#define OPENSSLDIR "/usr/local/ssl"
#define ENGINESDIR "/usr/local/lib/engines"

#include <%s.c>
*/
import "C"
`

// wrapTor clones the Tor library into the local repository and wraps it into a
// Go package.
func wrapTor(nobuild bool) (string, error) {
	// Clone the upstream repository to wrap
	os.RemoveAll("tor")

	cloner := exec.Command("git", "clone", "--depth", "1", "--branch", "release-0.3.3", "https://git.torproject.org/tor.git")
	cloner.Stdout = os.Stdout
	cloner.Stderr = os.Stderr

	if err := cloner.Run(); err != nil {
		return "", err
	}
	// Save the latest upstream commit hash for later reference
	parser := exec.Command("git", "rev-parse", "HEAD")
	parser.Dir = "tor"

	commit, err := parser.CombinedOutput()
	if err != nil {
		fmt.Println(string(commit))
		return "", err
	}
	// Configure the library for compilation
	autogen := exec.Command("./autogen.sh")
	autogen.Dir = "tor"
	autogen.Stdout = os.Stdout
	autogen.Stderr = os.Stderr

	if err := autogen.Run(); err != nil {
		return "", err
	}
	configure := exec.Command("./configure", "--disable-gcc-hardening")
	configure.Dir = "tor"
	configure.Stdout = os.Stdout
	configure.Stderr = os.Stderr

	if err := configure.Run(); err != nil {
		return "", err
	}
	// Hook the make system and gather the needed sources
	maker := exec.Command("make", "--dry-run")
	maker.Dir = "tor"

	out, err := maker.CombinedOutput()
	if err != nil {
		fmt.Println(string(out))
		return "", err
	}
	deps := regexp.MustCompile("(?m)([a-z0-9_/-]+)\\.c$").FindAllStringSubmatch(string(out), -1)

	// Wipe everything from the library that's non-essential
	files, err := ioutil.ReadDir("tor")
	if err != nil {
		return "", err
	}
	for _, file := range files {
		// Remove all folders apart from the sources
		if file.IsDir() {
			if file.Name() == "src" {
				continue
			}
			os.RemoveAll(filepath.Join("tor", file.Name()))
			continue
		}
		// Remove all files apart from the license
		if file.Name() == "LICENSE" {
			continue
		}
		os.Remove(filepath.Join("tor", file.Name()))
	}
	// Wipe all the sources from the library that are non-essential
	files, err = ioutil.ReadDir(filepath.Join("tor", "src"))
	if err != nil {
		return "", err
	}
	for _, file := range files {
		if file.IsDir() {
			if file.Name() == "common" || file.Name() == "ext" || file.Name() == "lib" || file.Name() == "or" || file.Name() == "trace" || file.Name() == "trunnel" || file.Name() == "win32" {
				continue
			}
			os.RemoveAll(filepath.Join("tor", "src", file.Name()))
			continue
		}
		os.Remove(filepath.Join("tor", "src", file.Name()))
	}
	// Fix the string compatibility source to load the correct code
	blob, _ := ioutil.ReadFile(filepath.Join("tor", "src", "common", "compat.c"))
	ioutil.WriteFile(filepath.Join("tor", "src", "common", "compat.c"), bytes.Replace(blob, []byte("strlcpy.c"), []byte("ext/strlcpy.c"), -1), 0644)

	// Fix for 0.3.5 branch
	//blob, _ := ioutil.ReadFile(filepath.Join("tor", "src", "lib", "string", "compat_string.c"))
	//ioutil.WriteFile(filepath.Join("tor", "src", "lib", "string", "compat_string.c"), bytes.Replace(blob, []byte("strlcpy.c"), []byte("ext/strlcpy.c"), -1), 0644)

	// Generate Go wrappers for each C source individually
	for _, dep := range deps {
		// Skip any files not needed for the library
		if strings.HasPrefix(dep[1], "src/test/") {
			continue
		}
		if strings.HasPrefix(dep[1], "src/tools/") {
			continue
		}
		// Anything else is wrapped directly with Go
		if strings.HasSuffix(dep[1], "tor_main") { // skip main
			continue
		}
		gofile := strings.Replace(dep[1], "/", "_", -1) + ".go"
		ioutil.WriteFile("tor_"+gofile, []byte(fmt.Sprintf(torTemplate, dep[1])), 0644)
	}
	ioutil.WriteFile("tor_preamble.go", []byte(torPreamble), 0644)

	// Inject the configuration headers and ensure everything builds
	os.MkdirAll("tor_config", 0755)

	blob, _ = ioutil.ReadFile(filepath.Join("tor", "src", "win32", "orconfig.h"))
	ver := regexp.MustCompile("VERSION \".+\"").Find(blob)

	blob, _ = ioutil.ReadFile(filepath.Join("config", "tor", "orconfig.h"))
	blob = bytes.Replace(blob, []byte("VERSION \"\""), ver, -1)
	ioutil.WriteFile(filepath.Join("tor_config", "orconfig.h"), blob, 0644)

	blob, _ = ioutil.ReadFile(filepath.Join("config", "tor", "micro-revision.i"))
	ioutil.WriteFile(filepath.Join("tor_config", "micro-revision.i"), blob, 0644)

	if !nobuild {
		builder := exec.Command("go", "install")
		builder.Stdout = os.Stdout
		builder.Stderr = os.Stderr

		return string(commit), builder.Run()
	}
	return string(commit), nil
}

// torPreamble is the CGO preamble injected to configure the C compiler.
var torPreamble = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/tor_config
#cgo CFLAGS: -I${SRCDIR}/tor
#cgo CFLAGS: -I${SRCDIR}/tor/src
#cgo CFLAGS: -I${SRCDIR}/tor/src/common
#cgo CFLAGS: -I${SRCDIR}/tor/src/ext
#cgo CFLAGS: -I${SRCDIR}/tor/src/ext/trunnel
#cgo CFLAGS: -I${SRCDIR}/tor/src/or
#cgo CFLAGS: -I${SRCDIR}/tor/src/trunnel

#cgo CFLAGS: -DED25519_CUSTOMRANDOM -DED25519_CUSTOMHASH -DED25519_SUFFIX=_donna

#cgo LDFLAGS: -lm
*/
import "C"
`

// torTemplate is the source file template used in Tor Go wrappers.
var torTemplate = `// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#define BUILDDIR ""

#include <%s.c>
*/
import "C"
`
