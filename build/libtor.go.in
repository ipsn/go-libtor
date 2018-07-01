// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.

// Package libtor is a self-contained static tor library.
package libtor

// This file is a simplified clone from github.com/cretz/bine/process/embedded.

/*
#cgo linux,amd64,!android linux,arm64,!android CFLAGS: -DARCH_LINUX64
#cgo linux,386,!android linux,arm,!android     CFLAGS: -DARCH_LINUX32
#cgo android,amd64 android,arm64               CFLAGS: -DARCH_ANDROID64
#cgo android,386 android,arm                   CFLAGS: -DARCH_ANDROID32

#include <stdlib.h>
#include <or/tor_api.h>

static char** makeCharArray(int size) {
	return calloc(sizeof(char*), size);
}
static void setArrayString(char **a, char *s, int n) {
	a[n] = s;
}
static void freeCharArray(char **a, int size) {
	int i;
	for (i = 0; i < size; i++)
		free(a[i]);
	free(a);
}
*/
import "C"
import (
	"fmt"
)

// Start creates a new tor process, returning a termination channel.
func Start(args ...string) (chan int, error) {
	// Create the char array for the args
	args = append([]string{"tor"}, args...)

	charArray := C.makeCharArray(C.int(len(args)))
	for i, a := range args {
		C.setArrayString(charArray, C.CString(a), C.int(i))
	}
	// Build the tor configuration
	config := C.tor_main_configuration_new()
	if code := C.tor_main_configuration_set_command_line(config, C.int(len(args)), charArray); code != 0 {
		C.tor_main_configuration_free(config)
		C.freeCharArray(charArray, C.int(len(args)))
		return nil, fmt.Errorf("failed to set arguments: %v", int(code))
	}
	// Start tor and return
	done := make(chan int, 1)
	go func() {
		defer C.freeCharArray(charArray, C.int(len(args)))
		defer C.tor_main_configuration_free(config)
		done <- int(C.tor_run_main(config))
	}()
	return done, nil
}
