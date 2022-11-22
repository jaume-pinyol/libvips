#!/bin/sh

# test the various restartable loaders

# webp and ppm use streams, but they mmap the input, so you can't close() the
# fd on minimise

# set -x
set -e

. ./variables.sh

if test_supported jpegload_source; then
	./test_resize_on_load $test_images/bad-width.jpg
fi


