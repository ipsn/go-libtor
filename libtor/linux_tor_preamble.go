// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.
// +build linux android

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/../linux/tor_config
#cgo CFLAGS: -I${SRCDIR}/../linux/tor
#cgo CFLAGS: -I${SRCDIR}/../linux/tor/src
#cgo CFLAGS: -I${SRCDIR}/../linux/tor/src/core/or
#cgo CFLAGS: -I${SRCDIR}/../linux/tor/src/ext
#cgo CFLAGS: -I${SRCDIR}/../linux/tor/src/ext/trunnel
#cgo CFLAGS: -I${SRCDIR}/../linux/tor/src/feature/api

#cgo CFLAGS: -DED25519_CUSTOMRANDOM -DED25519_CUSTOMHASH -DED25519_SUFFIX=_donna

#cgo LDFLAGS: -lm
*/
import "C"
