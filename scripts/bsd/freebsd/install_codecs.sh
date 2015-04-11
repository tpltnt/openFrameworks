#!/bin/sh
set -e

if [ $(id -u) != 0 ]; then
	echo "this script must be run with root privileges"
	echo ""
	echo "usage:"
	echo "sudo "$0
	exit $exit_code
    exit 1
fi

# header files of libmpg123 via source install?
pkg install audio/mpg123 multimedia/gstreamer1-plugins-ugly
