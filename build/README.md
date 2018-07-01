# go-libtor - Self-contained Tor from Go

[![GoDoc](https://godoc.org/github.com/ipsn/go-libtor?status.svg)](https://godoc.org/github.com/ipsn/go-libtor) [![Travis](https://travis-ci.org/ipsn/go-libtor.svg?branch=master)](https://travis-ci.org/ipsn/go-libtor)

The `go-libtor` project is a self-contained, fully statically linked Tor library for Go. It consists of an elaborate suite of Go/CGO wrappers around the original C/C++ Tor library and its dependencies ([zlib](https://github.com/madler/zlib), [libevent](https://github.com/libevent/libevent) and [openssl](https://github.com/openssl/openssl)).

| Library  | Commit |
|:--------:|:------:|
| zlib     | [`{{.zlib}}`](https://github.com/madler/zlib/commit/{{.zlib}})               |
| libevent | [`{{.libevent}}`](https://github.com/libevent/libevent/commit/{{.libevent}}) |
| openssl  | [`{{.openssl}}`](https://github.com/openssl/openssl/commit/{{.openssl}})     |
| tor      | [`{{.tor}}`](https://gitweb.torproject.org/tor.git/commit/?id={{.tor}})      |

The library currently is supported on Linux `amd64`, `386`, `arm64` and `arm`; both with `libc` and `musl`. More platforms will be added as I get to them, but my priorities are around Linux derivatives.

## Installation

The goal of this library is to be a self-contained Tor package for Go. As such, it plays nice with the usual `go get` workflow. That said, building Tor and all its dependencies locally can take quite a while, so it's recommended to run `go get` in verbose mode.

```
$ go get -u -v -x github.com/ipsn/go-libtor
```

## Usage

The `go-libtor` project does not contain a full Go API to interface Tor with, rather only the smallest building block to start up an embedded instance. The reason for not providing more is because there is already a solid Go project out there ([github.com/cretz/bine](https://godoc.org/github.com/cretz/bine/tor)) which focuses on interfacing.

Using both project in combination however is fairly straightforward:

```go
package main

import (
	"context"
	"errors"
	"fmt"
	"log"
	"net/http"
	"os"
	"time"

	"github.com/cretz/bine/process"
	"github.com/cretz/bine/tor"
	"github.com/ipsn/go-libtor"
)

func main() {
	// Start tor with soem defaults + elevated verbosity
	fmt.Println("Starting and registering onion service, please wait a bit...")
	t, err := tor.Start(nil, &tor.StartConf{ProcessCreator: NewCreator(), DebugWriter: os.Stderr, NoHush: true})
	if err != nil {
		log.Panicf("Failed to start tor: %v", err)
	}
	defer t.Close()

	// Wait at most a few minutes to publish the service
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Minute)
	defer cancel()

	// Create an onion service to listen on any port but show as 80
	onion, err := t.Listen(ctx, &tor.ListenConf{RemotePorts: []int{80}})
	if err != nil {
		log.Panicf("Failed to create onion service: %v", err)
	}
	defer onion.Close()

	fmt.Printf("Open Tor browser and navigate to http://%v.onion\n", onion.ID)

	// Run a Hello World HTTP service until terminated
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "Hello, Tor!")
	})
	http.Serve(onion, nil)
}

// embeddedCreator implements process.Creator, permitting libtor to act as an API
// backend for the bine/tor Go interface.
type embeddedCreator struct{}

// NewCreator creates a process.Creator for statically linked Tor embedded in the
// binary.
func NewCreator() process.Creator {
	return embeddedCreator{}
}

// New implements process.Creator, creating a new embedded tor process.
func (embeddedCreator) New(ctx context.Context, args ...string) (process.Process, error) {
	if ctx == nil {
		ctx = context.Background()
	}
	return &embeddedProcess{ctx: ctx, args: args}, nil
}

// embeddedProcess implements process.Process, permitting libtor to act as an API
// backend for the bine/tor Go interface.
type embeddedProcess struct {
	ctx  context.Context
	args []string
	done chan int
}

// Start implements process.Process, starting up the libtor embedded process.
func (e *embeddedProcess) Start() error {
	if e.done != nil {
		return errors.New("already started")
	}
	done, err := libtor.Start(e.args...)
	if err != nil {
		return err
	}
	e.done = done
	return nil
}

// Wait implements process.Process, blocking until the embedded process terminates.
func (e *embeddedProcess) Wait() error {
	if e.done == nil {
		return errors.New("not started")
	}
	select {
	case <-e.ctx.Done():
		return e.ctx.Err()

	case code := <-e.done:
		if code == 0 {
			return nil
		}
		return fmt.Errorf("embedded tor failed: %v", code)
	}
}
```

*Note: Although the above code is lengthy, everything outside of the `main` method is boilerplate that can be separated into its own package. I'll either upstream that into `bine`, or add it here eventually if they do not accept it.*

## Credits

This repository is maintained by Péter Szilágyi ([@karalabe](https://github.com/karalabe)), but authorship of all code contained inside belongs to the individual upstream projects.

## License

3-Clause BSD.
