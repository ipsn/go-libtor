// go-libtor - Self-contained Tor from Go
// Copyright (c) 2018 Péter Szilágyi. All rights reserved.
// +build linux android

package libtor

/*
#include <compat/sys/queue.h>
#include <../bufferevent_ratelim.c>
*/
import "C"
