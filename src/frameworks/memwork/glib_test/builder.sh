#!/bin/bash
export G_SLICE=always-malloc
gcc -std=gnu99 $(pkg-config --cflags --libs glib-2.0) -g -Wall -pedantic *.c
