#!/bin/sh

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

echo ">>> installing gstreamer <<<"
# install gstreamer 1.0 + base (partial?), good, bad, ugly
pkg install gstreamer1 gstreamer1-libav gstreamer-ffmpeg \
    gstreamer1-plugins-pulse gstreamer1-plugins
exit_code=$?
if [ $exit_code != 0 ]; then
	echo "error installing gstreamer, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi


echo ">>> installing remaining codecs <<<"
# header files of libmpg123 via source install?
pkg install audio/mpg123 multimedia/gstreamer1-plugins-ugly
exit_code=$?
if [ $exit_code != 0 ]; then
	echo "error installing mpg123 or gstreamer, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi


echo ">>> installing GTK 3 <<<"
pkg install x11-toolkits/gtk30
exit_code=$?
if [ $exit_code != 0 ]; then
    echo "error installing dependencies, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi


echo ">>> installing oF dependencies <<<"
pkg install freeglut libXmu libXxf86vm libGL libGLU libglapi libglesv2 \
    libEGL libdc1394 libdrm libtheora libvorbis glew openal-soft \
    libsndfile freeimage cairo py-lxml py-argparse freetype2 openssl \
    pulseaudio opencv
exit_code=$?
if [ $exit_code != 0 ]; then
    echo "error installing dependencies, there could be an error with your internet connection"
    echo "if the error persists, please report an issue in github: http://github.com/openframeworks/openFrameworks/issues"
	exit $exit_code
fi

