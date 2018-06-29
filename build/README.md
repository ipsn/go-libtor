# go-libtor - Self-contained Tor from Go

[![GoDoc](https://godoc.org/github.com/ipsn/go-libtor?status.svg)](https://godoc.org/github.com/ipsn/go-libtor) [![Travis](https://travis-ci.org/ipsn/go-libtor.svg?branch=master)](https://travis-ci.org/ipsn/go-libtor)

The `go-libtor` project is a self-contained, fully statically linked Tor library for Go. It consists of an elaborate suite of Go/CGO wrappers around the original C/C++ Tor library and its dependencies ([zlib](https://github.com/madler/zlib), [libevent](https://github.com/libevent/libevent) and [openssl](https://github.com/openssl/openssl)).

| Library  | Commit |
|:--------:|:------:|
| zlib     | [`{{.zlib}}`](https://github.com/madler/zlib/commit/{{.zlib}})               |
| libevent | [`{{.libevent}}`](https://github.com/libevent/libevent/commit/{{.libevent}}) |
| openssl  | [`{{.openssl}}`](https://github.com/openssl/openssl/commit/{{.openssl}})     |
| tor      | [`{{.tor}}`](https://gitweb.torproject.org/tor.git/commit/?id={{.tor}})      |

The library currently is supported on Linux `amd64`, both with `libc` and `musl`. More platforms will be added as I get to them, but my priorities are around Linux derivatives.

## Credits

This repository is maintained by Péter Szilágyi ([@karalabe](https://github.com/karalabe)), but authorship of all code contained inside belongs to the individual upstream projects.

## License

3-Clause BSD.
