/*
  This file handles platform specific information and includes.
*/

#pragma once
#include <stdint.h>

enum ofTargetPlatform{
	OF_TARGET_OSX,
	OF_TARGET_WINGCC,
	OF_TARGET_WINVS,
	OF_TARGET_IOS,
	OF_TARGET_ANDROID,
	OF_TARGET_LINUX,
	OF_TARGET_LINUX64,
	OF_TARGET_LINUXARMV6L, // arm v6 little endian
	OF_TARGET_LINUXARMV7L, // arm v7 little endian
	OF_TARGET_EMSCRIPTEN
};

#ifndef OF_TARGET_IPHONE
    #define OF_TARGET_IPHONE OF_TARGET_IOS
#endif 


//-------------------------------
//  find the system type --------
//-------------------------------

// 		helpful:
// 		http://www.ogre3d.org/docs/api/html/OgrePlatform_8h-source.html

#if defined( __WIN32__ ) || defined( _WIN32 )
	#define TARGET_WIN32
#elif defined( __APPLE_CC__)
    #define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
    #include <TargetConditionals.h>

	#if TARGET_OS_IPHONE_SIMULATOR || TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || TARGET_IPHONE
		#define TARGET_OF_IPHONE
        #define TARGET_OF_IOS
		#define TARGET_OPENGLES
        #include <unistd.h>
	#else
		#define TARGET_OSX
	#endif
#elif defined (__ANDROID__)
	#define TARGET_ANDROID
	#define TARGET_OPENGLES
#elif defined(__ARMEL__)
	#define TARGET_LINUX
	#define TARGET_OPENGLES
	#define TARGET_LINUX_ARM
#elif defined(__EMSCRIPTEN__)
	#define TARGET_EMSCRIPTEN
	#define TARGET_OPENGLES
	#define TARGET_NO_THREADS
	#define TARGET_PROGRAMMABLE_GL
	#define TARGET_IMPLEMENTS_URL_LOADER
#else
	#define TARGET_LINUX
#endif

// then the the platform specific includes:
#ifdef TARGET_WIN32

	#define GLEW_STATIC
	#include "GL/glew.h"
	#include "GL/wglew.h"
   	#include "glu.h"
	#define __WINDOWS_DS__
	#define __WINDOWS_MM__
	#if (_MSC_VER)       // microsoft visual studio
		#include <stdint.h>
		#include <functional>
		#pragma warning(disable : 4068)		// unknown pragmas
		#pragma warning(disable : 4756)		// overflow in constant arithmetic
		#pragma warning(disable : 4800)		// 'Boolean' : forcing value to bool 'true' or 'false'

		// make microsoft visual studio complain less about double / float conversion and
		// truncation
		#pragma warning(disable : 4244)
		#pragma warning(disable : 4305)
		// warnings: http://msdn.microsoft.com/library/2c8f766e.aspx

		// NOMINMAX doesn't seem to work anymore in vs2015 so let's just remove them
		#undef min
		#undef max
	#endif

	#define TARGET_LITTLE_ENDIAN			// intel cpu

	// some gl.h files, like dev-c++, are old - this is pretty universal
	#ifndef GL_BGR_EXT
	#define GL_BGR_EXT 0x80E0
	#endif

	#define WIN32_HIGH_RES_TIMING

	// note: this is experimental!
	// uncomment to turn this on (only for windows machines)
	// if you want to try setting the timer to be high resolution
	// this could make camera grabbing and other low level
	// operations quicker, but you must quit the app normally,
	// ie, using "esc", rather than killing the process or closing
	// the console window in order to set the timer resolution back
	// to normal (since the high res timer might give the OS
	// problems)
	// info: http://www.geisswerks.com/ryan/FAQS/timing.html

#endif

#ifdef TARGET_OSX
	#ifndef __MACOSX_CORE__
		#define __MACOSX_CORE__
	#endif
	#include <unistd.h>
	#include "GL/glew.h"
	#include <OpenGL/gl.h>
	#include <ApplicationServices/ApplicationServices.h>

	#if defined(__LITTLE_ENDIAN__)
		#define TARGET_LITTLE_ENDIAN		// intel cpu
	#endif
#endif

#ifdef TARGET_LINUX

		#define GL_GLEXT_PROTOTYPES
        #include <unistd.h>

    #ifdef TARGET_LINUX_ARM
    	#ifdef TARGET_RASPBERRY_PI
        	#include "bcm_host.h"
        #endif
       
		#include "GLES/gl.h"
		#include "GLES/glext.h" 
		#include "GLES2/gl2.h"
		#include "GLES2/gl2ext.h"
		
		#define EGL_EGLEXT_PROTOTYPES
		#include "EGL/egl.h"
		#include "EGL/eglext.h"
    #else // normal linux
        #include <GL/glew.h>
        #include <GL/gl.h>
        #include <GL/glx.h>
    #endif

    // for some reason, this isn't defined at compile time,
    // so this hack let's us work
    // for 99% of the linux folks that are on intel
    // everyone one else will have RGB / BGR issues.
	//#if defined(__LITTLE_ENDIAN__)
		#define TARGET_LITTLE_ENDIAN		// intel cpu
	//#endif

        // some things for serial compilation:
        #define B14400	14400
        #define B28800	28800

#endif


#ifdef TARGET_OF_IOS
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>

	#import <OpenGLES/ES2/gl.h>
	#import <OpenGLES/ES2/glext.h>

	
	#define TARGET_LITTLE_ENDIAN		// arm cpu	
#endif

#ifdef TARGET_ANDROID
	#include <typeinfo>
	#include <unistd.h>
	#include <GLES/gl.h>
	#define GL_GLEXT_PROTOTYPES
	#include <GLES/glext.h>

	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

	#define TARGET_LITTLE_ENDIAN
#endif

#ifdef TARGET_EMSCRIPTEN
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
	#include "EGL/egl.h"
	#include "EGL/eglext.h"

	#define TARGET_LITTLE_ENDIAN
#endif

#ifndef __MWERKS__
  #include <cstdlib>
#endif
