# go-libtor - Self-contained Tor from Go

The `go-libtor` project is a self-contained, fully statically linked Tor library for Go. It consists of an elaborate suite of Go/CGO wrappers around the original C/C++ Tor library and its dependencies ([zlib](https://github.com/madler/zlib), [libevent](https://github.com/libevent/libevent) and [openssl](https://github.com/openssl/openssl)).

| Library  | Commit        |
|:--------:|:-------------:|
| zlib     | [{{.zlib}}](https://github.com/madler/zlib/commit/{{.zlib}})               |
| libevent | [{{.libevent}}](https://github.com/libevent/libevent/commit/{{.libevent}}) |
| openssl  | [{{.openssl}}](https://github.com/openssl/openssl/commit/{{.openssl}})     |
| tor      | [{{.tor}}](https://gitweb.torproject.org/tor.git/commit/?id={{.tor}})      |
