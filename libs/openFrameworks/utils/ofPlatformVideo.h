/*
  This includes handles the video specific platform issues
  mostly regarding the capture and playback.
 */

#pragma once
#include "ofPlatformOS.h"

enum ofLoopType{
	OF_LOOP_NONE=0x01,
	OF_LOOP_PALINDROME=0x02,
	OF_LOOP_NORMAL=0x03
};

//------------------------------------------------ capture
// check if any video capture system is already defined from the compiler
#if !defined(OF_VIDEO_CAPTURE_GSTREAMER) && !defined(OF_VIDEO_CAPTURE_QUICKTIME) && !defined(OF_VIDEO_CAPTURE_DIRECTSHOW) && !defined(OF_VIDEO_CAPTURE_ANDROID) && !defined(OF_VIDEO_CAPTURE_IOS)
	#ifdef TARGET_LINUX

		#define OF_VIDEO_CAPTURE_GSTREAMER

	#elif defined(TARGET_OSX)
		//on 10.6 and below we can use the old grabber
		#ifndef MAC_OS_X_VERSION_10_7
			#define OF_VIDEO_CAPTURE_QUICKTIME
		#else
			#define OF_VIDEO_CAPTURE_QTKIT
        #endif

	#elif defined (TARGET_WIN32)

		// comment out this following line, if you'd like to use the
		// quicktime capture interface on windows
		// if not, we default to videoInput library for
		// direct show capture...

		#define OF_SWITCH_TO_DSHOW_FOR_WIN_VIDCAP

		#ifdef OF_SWITCH_TO_DSHOW_FOR_WIN_VIDCAP
			#define OF_VIDEO_CAPTURE_DIRECTSHOW
		#else
			#define OF_VIDEO_CAPTURE_QUICKTIME
		#endif

	#elif defined(TARGET_ANDROID)

		#define OF_VIDEO_CAPTURE_ANDROID

	#elif defined(TARGET_EMSCRIPTEN)

		#define OF_VIDEO_CAPTURE_EMSCRIPTEN

	#elif defined(TARGET_OF_IOS)

		#define OF_VIDEO_CAPTURE_IOS

	#endif
#endif

//------------------------------------------------  video player
// check if any video player system is already defined from the compiler
#if !defined(OF_VIDEO_PLAYER_GSTREAMER) && !defined(OF_VIDEO_PLAYER_IOS) && !defined(OF_VIDEO_PLAYER_DIRECTSHOW) && !defined(OF_VIDEO_PLAYER_QUICKTIME) && !defined(OF_VIDEO_PLAYER_AVFOUNDATION) && !defined(OF_VIDEO_PLAYER_EMSCRIPTEN)
    #ifdef TARGET_LINUX
        #define OF_VIDEO_PLAYER_GSTREAMER
    #elif defined(TARGET_ANDROID)
        #define OF_VIDEO_PLAYER_ANDROID
    #elif defined(TARGET_OF_IOS)
        #define OF_VIDEO_PLAYER_IOS
	#elif defined(TARGET_WIN32) && !defined(__MINGW32__)
        #define OF_VIDEO_PLAYER_DIRECTSHOW
    #elif defined(TARGET_OSX)
        //for 10.8 and 10.9 users we use AVFoundation, for 10.7 we use QTKit, for 10.6 users we use QuickTime
        #ifndef MAC_OS_X_VERSION_10_7
            #define OF_VIDEO_PLAYER_QUICKTIME
        #elif !defined(MAC_OS_X_VERSION_10_8)
            #define OF_VIDEO_PLAYER_QTKIT
        #else
            #define OF_VIDEO_PLAYER_AVFOUNDATION
        #endif
    #elif defined(TARGET_EMSCRIPTEN)
        #define OF_VIDEO_PLAYER_EMSCRIPTEN
    #else
        #define OF_VIDEO_PLAYER_QUICKTIME
    #endif
#endif
