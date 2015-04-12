**This port is incomplete and considered experimental**, but may be sufficient.

general notes
-------------
* [gstreamer plugins base]( http://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-base-plugins/html/) not explicitly in ports
* only (explicitly) listed base plugins:
  * gstreamer1-plugins-cdparanoia
  * gstreamer-plugins-gio
  * gstreamer1-plugins-libvisual
  * gstreamer1-plugins-ogg
  * gstreamer1-plugins-pango
  * gstreamer1-plugins-theora
  * gstreamer1-plugins-v4l2
  * gstreamer1-plugins-vorbis
  * gstreamer1-plugins-ximagesrc
* gstreamer-ffmpeg not yet at 1.0
* FreeBSD has no ALSA, only OSS, therefore no gstreamer${GSTREAMER_VERSION}-alsa
* use `gmake` instead of `make`


things to do
------------
* port udev code to devd
  * e.g. ofGstVideoGrabber (currently disabled because of missing devd support)
* adjust OS specific calls
  * `clock_nanosleep()` (ofTimer.cpp, ofUtils.cpp)
* port libraw1394 for [FireWire](https://wiki.freebsd.org/FireWire)
* upgrade freeglut port to 3.0
* replace OpenSSL with libreSSL


references
----------
* [FreeBSD handbook](https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/)
* [Porter's handbook](https://www.freebsd.org/doc/en_US.ISO8859-1/books/porters-handbook)
* [Developer's handbook](https://www.freebsd.org/doc/en_US.ISO8859-1/books/developers-handbook)
* FreeBSD wiki
  * [USB](https://wiki.freebsd.org/USB)
  * [graphics](https://wiki.freebsd.org/Graphics)
* [devd(8)](https://www.freebsd.org/cgi/man.cgi?query=devd&manpath=FreeBSD+10.1-RELEASE&format=html)
