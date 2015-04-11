#!/bin/sh
set -e

if [ $(id -u) != 0 ]; then
	echo "this script must be run as root"
	echo ""
	echo "usage:"
	echo "su -"
	echo $0
    exit 1
fi

# update local package cache
pkg update

echo "installing gstreamer"
# install gstreamer 1.0
# * gstreamer-ffmpeg not yet at 1.0
# * FreeBSD has no ALSA, only OSS, therefore no gstreamer${GSTREAMER_VERSION}-alsa
pkg install gstreamer1 gstreamer1-libav
gstreamer-ffmpeg \
gstreamer1-plugins-pulse \
# base (partial?), good, bad, ugly
gstreamer1-plugins
# gstreamer plugins base not explixit ports, but
# gstreamer1-plugins-cdparanoia, gstreamer-plugins-gio,
# gstreamer1-plugins-libvisual, gstreamer1-plugins-ogg
# gstreamer1-plugins-pango, gstreamer1-plugins-theora
# gstreamer1-plugins-v4l2, gstreamer1-plugins-vorbis
# gstreamer1-plugins-ximagesrc
# complete list: http://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-base-plugins/html/
exit_code=$?
if [ $exit_code != 0 ]; then
	echo "error installing gstreamer, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi


echo "installing remaining codecs"
# header files of libmpg123 via source install?
pkg install audio/mpg123 multimedia/gstreamer1-plugins-ugly
exit_code=$?
if [ $exit_code != 0 ]; then
	echo "error installing mpg123 or gstreamer, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi


echo "installing GTK 3"
pkg install x11-toolkits/gtk30
exit_code=$?
if [ $exit_code != 0 ]; then
    echo "error installing dependencies, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi


echo "installing oF dependencies"
echo "installing dependencies *not* ported yet"
exit 23
# * libdc1394 equivalent to libraw1394-dev for oF?
#   * libraw1394 needs to be ported https://wiki.freebsd.org/FireWire
# * devd FreeBSD equivalient to udev -> oF needs to be ported
pkg install freeglut
# libasound2-dev
libXmu
libXxf86vm
#g++
libGL
libGLU
libglapi
libglesv2
libdc1394
# libraw1394-dev
# libudev-dev - devd adjustments needed
libdrm-dev
libglew-dev
libopenal-dev
libsndfile-dev
libfreeimage-dev
libcairo2-dev
python-lxml
python-argparse
libfreetype6-dev
libssl-dev
libpulse-dev
libusb-1.0-0-dev
libopencv-dev
libegl1-mesa-dev
libgles1-mesa-dev
libgles2-mesa-dev
exit_code=$?
if [ $exit_code != 0 ]; then
    echo "error installing dependencies, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi

