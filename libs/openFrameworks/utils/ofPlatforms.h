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


//--------------------------------------------
//
// 	Keyboard definitions
//
// 	ok -- why this?
// 	glut key commands have some annoying features,
// 	in that some normal keys have the same value as special keys,
// 	but we want ONE key routine, so we need to redefine several,
// 	so that we get some normalacy across keys routines
//
// 	(everything that comes through "glutSpecialKeyFunc" will get 256 added to it,
// 	to avoid conflicts, before, values like "left, right up down" (ie, 104, 105, 106) were conflicting with
// 	letters.. now they will be 256 + 104, 256 + 105....)

#define OF_KEY_MODIFIER 	0x0100
#define OF_KEY_RETURN		13
#define OF_KEY_ESC			27
#define OF_KEY_TAB          9
#define OF_KEY_COMMAND      OF_KEY_SUPER

// http://www.openframeworks.cc/forum/viewtopic.php?t=494
// some issues with keys across platforms:

#ifdef TARGET_OSX
  #define OF_KEY_BACKSPACE	127
  #define OF_KEY_DEL			8
#else
  #define OF_KEY_BACKSPACE	8
  #define OF_KEY_DEL			127
#endif

// zach - there are more of these keys, we can add them here...
// these are keys that are not coming through "special keys"
// via glut, but just other keys on your keyboard like

#define OF_KEY_F1			(1 | OF_KEY_MODIFIER)
#define OF_KEY_F2			(2 | OF_KEY_MODIFIER)
#define OF_KEY_F3			(3 | OF_KEY_MODIFIER)
#define OF_KEY_F4			(4 | OF_KEY_MODIFIER)
#define OF_KEY_F5			(5 | OF_KEY_MODIFIER)
#define OF_KEY_F6			(6 | OF_KEY_MODIFIER)
#define OF_KEY_F7			(7 | OF_KEY_MODIFIER)
#define OF_KEY_F8			(8 | OF_KEY_MODIFIER)
#define OF_KEY_F9			(9 | OF_KEY_MODIFIER)
#define OF_KEY_F10			(10 | OF_KEY_MODIFIER)
#define OF_KEY_F11			(11 | OF_KEY_MODIFIER)
#define OF_KEY_F12			(12 | OF_KEY_MODIFIER)
#define OF_KEY_LEFT			(100 | OF_KEY_MODIFIER)
#define OF_KEY_UP			(101 | OF_KEY_MODIFIER)
#define OF_KEY_RIGHT		(102 | OF_KEY_MODIFIER)
#define OF_KEY_DOWN			(103 | OF_KEY_MODIFIER)
#define OF_KEY_PAGE_UP		(104 | OF_KEY_MODIFIER)
#define OF_KEY_PAGE_DOWN	(105 | OF_KEY_MODIFIER)
#define OF_KEY_HOME			(106 | OF_KEY_MODIFIER)
#define OF_KEY_END			(107 | OF_KEY_MODIFIER)
#define OF_KEY_INSERT		(108 | OF_KEY_MODIFIER)
#define OF_KEY_CONTROL		(0x200 | OF_KEY_MODIFIER)
#define OF_KEY_ALT			(0x400 | OF_KEY_MODIFIER)
#define OF_KEY_SHIFT		(0x800 | OF_KEY_MODIFIER)
#define OF_KEY_SUPER		(0x1000 | OF_KEY_MODIFIER)
#define OF_KEY_LEFT_SHIFT	(0x1 | OF_KEY_SHIFT)
#define OF_KEY_RIGHT_SHIFT	(0x2 | OF_KEY_SHIFT)
#define OF_KEY_LEFT_CONTROL	(0x1 | OF_KEY_CONTROL)
#define OF_KEY_RIGHT_CONTROL (0x2 | OF_KEY_CONTROL)
#define OF_KEY_LEFT_ALT		(0x1 | OF_KEY_ALT)
#define OF_KEY_RIGHT_ALT	(0x2 | OF_KEY_ALT)
#define OF_KEY_LEFT_SUPER	(0x1 | OF_KEY_SUPER)
#define OF_KEY_RIGHT_SUPER	(0x2 | OF_KEY_SUPER)
#define OF_KEY_LEFT_COMMAND OF_KEY_LEFT_SUPER
#define OF_KEY_RIGHT_COMMAND OF_KEY_RIGHT_SUPER
// not sure what to do in the case of non-glut apps....

#define OF_MOUSE_BUTTON_1      0
#define OF_MOUSE_BUTTON_2      1
#define OF_MOUSE_BUTTON_3      2
#define OF_MOUSE_BUTTON_4      3
#define OF_MOUSE_BUTTON_5      4
#define OF_MOUSE_BUTTON_6      5
#define OF_MOUSE_BUTTON_7      6
#define OF_MOUSE_BUTTON_8      7
#define OF_MOUSE_BUTTON_LAST   OF_MOUSE_BUTTON_8
#define OF_MOUSE_BUTTON_LEFT   OF_MOUSE_BUTTON_1
#define OF_MOUSE_BUTTON_MIDDLE OF_MOUSE_BUTTON_2
#define OF_MOUSE_BUTTON_RIGHT  OF_MOUSE_BUTTON_3
