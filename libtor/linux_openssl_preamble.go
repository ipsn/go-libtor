// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.
// +build linux android

package libtor

/*
#cgo CFLAGS: -I${SRCDIR}/../linux/openssl_config
#cgo CFLAGS: -I${SRCDIR}/../linux/openssl
#cgo CFLAGS: -I${SRCDIR}/../linux/openssl/include
#cgo CFLAGS: -I${SRCDIR}/../linux/openssl/crypto/ec/curve448
#cgo CFLAGS: -I${SRCDIR}/../linux/openssl/crypto/ec/curve448/arch_32
#cgo CFLAGS: -I${SRCDIR}/../linux/openssl/crypto/modes
*/
import "C"
