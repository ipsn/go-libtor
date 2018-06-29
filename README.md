# go-libtor - Self-contained Tor from Go

[![GoDoc](https://godoc.org/github.com/ipsn/go-libtor?status.svg)](https://godoc.org/github.com/ipsn/go-libtor) [![Travis](https://travis-ci.org/ipsn/go-libtor.svg?branch=master)](https://travis-ci.org/ipsn/go-libtor)

The `go-libtor` project is a self-contained, fully statically linked Tor library for Go. It consists of an elaborate suite of Go/CGO wrappers around the original C/C++ Tor library and its dependencies ([zlib](https://github.com/madler/zlib), [libevent](https://github.com/libevent/libevent) and [openssl](https://github.com/openssl/openssl)).

| Library  | Commit |
|:--------:|:------:|
| zlib     | [`cacf7f1d4e3d44d871b605da3b647f07d718623f`](https://github.com/madler/zlib/commit/cacf7f1d4e3d44d871b605da3b647f07d718623f)               |
| libevent | [`24236aed01798303745470e6c498bf606e88724a`](https://github.com/libevent/libevent/commit/24236aed01798303745470e6c498bf606e88724a) |
| openssl  | [`c7b9e7be89c987fbf065852d846ac4982a32941b`](https://github.com/openssl/openssl/commit/c7b9e7be89c987fbf065852d846ac4982a32941b)     |
| tor      | [`63cddead384d067604f44091e2a8a3f776ccd2bf`](https://gitweb.torproject.org/tor.git/commit/?id=63cddead384d067604f44091e2a8a3f776ccd2bf)      |

The library currently is supported on Linux `amd64`, both with `libc` and `musl`. More platforms will be added as I get to them, but my priorities are around Linux derivatives.

## Credits

This repository is maintained by Péter Szilágyi ([@karalabe](https://github.com/karalabe)), but authorship of all code contained inside belongs to the individual upstream projects.

## License

3-Clause BSD.
