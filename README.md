# go-libtor - Self-contained Tor from Go

The `go-libtor` project is a self-contained, fully statically linked Tor library for Go. It consists of an elaborate suite of Go/CGO wrappers around the original C/C++ Tor library and its dependencies ([zlib](https://github.com/madler/zlib), [libevent](https://github.com/libevent/libevent) and [openssl](https://github.com/openssl/openssl)).

| Library  | Commit        |
|:--------:|:-------------:|
| zlib     | [cacf7f1d4e3d44d871b605da3b647f07d718623f](https://github.com/madler/zlib/commit/cacf7f1d4e3d44d871b605da3b647f07d718623f)               |
| libevent | [24236aed01798303745470e6c498bf606e88724a](https://github.com/libevent/libevent/commit/24236aed01798303745470e6c498bf606e88724a) |
| openssl  | [c7b9e7be89c987fbf065852d846ac4982a32941b](https://github.com/openssl/openssl/commit/c7b9e7be89c987fbf065852d846ac4982a32941b)     |
| tor      | [63cddead384d067604f44091e2a8a3f776ccd2bf](https://gitweb.torproject.org/tor.git/commit/?id=63cddead384d067604f44091e2a8a3f776ccd2bf)      |
