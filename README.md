# go-libtor - Self-contained Tor from Go

[![GoDoc](https://godoc.org/github.com/ipsn/go-libtor?status.svg)](https://godoc.org/github.com/ipsn/go-libtor) [![Travis](https://travis-ci.org/ipsn/go-libtor.svg?branch=master)](https://travis-ci.org/ipsn/go-libtor)

The `go-libtor` project is a self-contained, fully statically linked Tor library for Go. It consists of an elaborate suite of Go/CGO wrappers around the original C/C++ Tor library and its dependencies ([zlib](https://github.com/madler/zlib), [libevent](https://github.com/libevent/libevent) and [openssl](https://github.com/openssl/openssl)).

| Library  | Commit |
|:--------:|:------:|
| zlib     | [`cacf7f1d4e3d44d871b605da3b647f07d718623f`](https://github.com/madler/zlib/commit/cacf7f1d4e3d44d871b605da3b647f07d718623f)               |
| libevent | [`514dc7579c43e673bdf613e01690371438661260`](https://github.com/libevent/libevent/commit/514dc7579c43e673bdf613e01690371438661260) |
| openssl  | [`7725c76c3f685c306ef4f4125a8a3495e9978a68`](https://github.com/openssl/openssl/commit/7725c76c3f685c306ef4f4125a8a3495e9978a68)     |
| tor      | [`81b5483ee6167f8ea176ca33fa9c8deed684fb32`](https://gitweb.torproject.org/tor.git/commit/?id=81b5483ee6167f8ea176ca33fa9c8deed684fb32)      |

The library is currently supported on:

 - Linux `amd64`, `386`, `arm64` and `arm`; both with `libc` and `musl`.
 - Android `amd64`, `386`, `arm64` and `arm`; specifically via `gomobile`.

## Installation

The goal of this library is to be a self-contained Tor package for Go. As such, it plays nice with the usual `go get` workflow. That said, building Tor and all its dependencies locally can take quite a while, so it's recommended to run `go get` in verbose mode.

```
$ go get -u -v -x github.com/ipsn/go-libtor
```

You'll also need the [`bine`](https://github.com/cretz/bine) bindings to interface with the library:

```
go get -u github.com/cretz/bine/tor
```

## Usage

The `go-libtor` project does not contain a full Go API to interface Tor with, rather only the smallest building block to start up an embedded instance. The reason is because there is already a solid Go project out there ([github.com/cretz/bine](https://github.com/cretz/bine/tor)) which focuses on interfacing.

Using both projects in combination however is straightforward:

```go
package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"time"

	"github.com/cretz/bine/tor"
	"github.com/ipsn/go-libtor"
)

func main() {
	// Start tor with some defaults + elevated verbosity
	fmt.Println("Starting and registering onion service, please wait a bit...")
	t, err := tor.Start(nil, &tor.StartConf{ProcessCreator: libtor.Creator, DebugWriter: os.Stderr})
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

	fmt.Printf("Please open a Tor capable browser and navigate to http://%v.onion\n", onion.ID)

	// Run a Hello-World HTTP service until terminated
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "Hello, Tor!")
	})
	http.Serve(onion, nil)
}
```

The above code will:

 * Start up a new Tor process from within your statically linked binary
 * Register a new anonymous onion TCP endpoint for remote clients
 * Start an HTTP server using the Tor network as its transport layer

```
$ go run main.go

Starting and registering onion service, please wait a bit...
[...]
Enabling network before waiting for publication
[...]
Waiting for publication
[...]
Please open a Tor capable browser and navigate to http://s7t3iy76h54cjacg.onion
```

![Demo](https://raw.githubusercontent.com/ipsn/go-libtor/master/demo.png)

## Credits

This repository is maintained by Péter Szilágyi ([@karalabe](https://github.com/karalabe)), but authorship of all code contained inside belongs to the individual upstream projects.

## License

3-Clause BSD.
