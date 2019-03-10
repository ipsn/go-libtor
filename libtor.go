// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

// Package libtor is a self-contained static tor library.
package libtor

// This file is a wrapper around the internal libtor package to keep the original
// Go API, but move the thousands of generated Go files into a sub-folder, out of
// the way of the repo root.

import (
	"github.com/cretz/bine/process"
	"github.com/ipsn/go-libtor/libtor"
)

// ProviderVersion returns the Tor provider name and version exposed from the
// Tor embedded API.
func ProviderVersion() string {
	return libtor.ProviderVersion()
}

// Creator implements the bine.process.Creator, permitting libtor to act as an API
// backend for the bine/tor Go interface.
var Creator process.Creator = libtor.Creator
