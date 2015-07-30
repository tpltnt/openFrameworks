#include "ofBaseSoundStream.h"
#include <ostream>  // for endl
#include "ofLog.h"  // for ofLog, ofLogNotice

void ofBaseSoundStream::printDeviceList() const {
	ofLogNotice("ofBaseSoundStream::printDeviceList") << std::endl << getDeviceList();
}
