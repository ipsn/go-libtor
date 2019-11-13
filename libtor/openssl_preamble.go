// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/../openssl_config
#cgo CFLAGS: -I${SRCDIR}/../openssl
#cgo CFLAGS: -I${SRCDIR}/../openssl/include
#cgo CFLAGS: -I${SRCDIR}/../openssl/crypto/ec/curve448
#cgo CFLAGS: -I${SRCDIR}/../openssl/crypto/ec/curve448/arch_32
#cgo CFLAGS: -I${SRCDIR}/../openssl/crypto/modes
*/
import "C"
