#pragma once
#include <stdint.h>
#include "ofPlatformOS.h"

//-------------------------------
#define OF_VERSION_MAJOR 0
#define OF_VERSION_MINOR 9
#define OF_VERSION_PATCH 0
#define OF_VERSION_PRE_RELEASE "master"

//-------------------------------
#include "tesselator.h"
typedef TESSindex ofIndexType;

#define OF_EXIT_APP(val)		std::exit(val);


//------------------------------------------------ soundstream
// check if any soundstream api is defined from the compiler
#if !defined(OF_SOUNDSTREAM_RTAUDIO) && !defined(OF_SOUNDSTREAM_ANDROID) && !defined(OF_SOUNDSTREAM_IOS) && !defined(OF_SOUNDSTREAM_EMSCRIPTEN)
	#if defined(TARGET_LINUX) || defined(TARGET_WIN32) || defined(TARGET_OSX)
		#define OF_SOUNDSTREAM_RTAUDIO
	#elif defined(TARGET_ANDROID)
		#define OF_SOUNDSTREAM_ANDROID
	#elif defined(TARGET_OF_IOS)
		#define OF_SOUNDSTREAM_IOS
	#elif defined(TARGET_EMSCRIPTEN)
		#define OF_SOUNDSTREAM_EMSCRIPTEN
	#endif
#endif

//------------------------------------------------ soundplayer
// check if any soundplayer api is defined from the compiler
#if !defined(OF_SOUND_PLAYER_QUICKTIME) && !defined(OF_SOUND_PLAYER_FMOD) && !defined(OF_SOUND_PLAYER_OPENAL) && !defined(OF_SOUND_PLAYER_EMSCRIPTEN)
  #ifdef TARGET_OF_IOS
  	#define OF_SOUND_PLAYER_IPHONE
  #elif defined(TARGET_LINUX)
  	#define OF_SOUND_PLAYER_OPENAL
  #elif defined(TARGET_EMSCRIPTEN)
	#define OF_SOUND_PLAYER_EMSCRIPTEN
  #elif !defined(TARGET_ANDROID)
  	#define OF_SOUND_PLAYER_FMOD
  #endif
#endif

//------------------------------------------------ c++11
// check if the compiler supports c++11. vs hasn't updated the value
// of __cplusplus so we need to check for vs >= 2012 (1700)
#if __cplusplus>=201103 || _MSC_VER >= 1700
#define HAS_CPP11 1
#endif

//------------------------------------------------ thread local storage
// xcode has a bug where it won't support tls on some versions even
// on c++11, this is a workaround that bug
#if !defined(TARGET_OSX) && !defined(TARGET_OF_IOS)
	#define HAS_TLS 1
#elif __clang__
	#if __has_feature(cxx_thread_local)
		#define HAS_TLS 1
	#endif
#endif

//we don't want to break old code that uses ofSimpleApp
//so we forward declare ofBaseApp and make ofSimpleApp mean the same thing
class ofBaseApp;
typedef ofBaseApp ofSimpleApp;

// serial error codes
#define OF_SERIAL_NO_DATA 	-2
#define OF_SERIAL_ERROR		-1

// core: ---------------------------
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>  //for ostringsream
#include <iomanip>  //for setprecision
#include <fstream>
#include <algorithm>
#include <cfloat>
#include <map>
#include <stack>
#include <unordered_map>
#include <memory>

using namespace std;

#ifndef PI
	#define PI       3.14159265358979323846
#endif

#ifndef TWO_PI
	#define TWO_PI   6.28318530717958647693
#endif

#ifndef M_TWO_PI
	#define M_TWO_PI   6.28318530717958647693
#endif

#ifndef FOUR_PI
	#define FOUR_PI 12.56637061435917295385
#endif

#ifndef HALF_PI
	#define HALF_PI  1.57079632679489661923
#endif

#ifndef DEG_TO_RAD
	#define DEG_TO_RAD (PI/180.0)
#endif

#ifndef RAD_TO_DEG
	#define RAD_TO_DEG (180.0/PI)
#endif

#ifndef MIN
	#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
	#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef CLAMP
	#define CLAMP(val,min,max) ((val) < (min) ? (min) : ((val > max) ? (max) : (val)))
#endif

#ifndef ABS
	#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif

//--- OpenGL render options
enum ofFillFlag{
	OF_OUTLINE=	0,
	OF_FILLED = 1,
};

enum ofWindowMode{
	OF_WINDOW 		= 0,
	OF_FULLSCREEN 	= 1,
 	OF_GAME_MODE	= 2
};

// only used in ofRectangle
enum ofAspectRatioMode {
    OF_ASPECT_RATIO_IGNORE            = 0,
    OF_ASPECT_RATIO_KEEP              = 1,
    OF_ASPECT_RATIO_KEEP_BY_EXPANDING = 2,
};

// only used in ofRectangle
enum ofAlignVert {
    OF_ALIGN_VERT_IGNORE   = 0x0000,
    OF_ALIGN_VERT_TOP      = 0x0010,
    OF_ALIGN_VERT_BOTTOM   = 0x0020,
    OF_ALIGN_VERT_CENTER   = 0x0040,
};

// only used in ofRectangle
enum ofAlignHorz {
    OF_ALIGN_HORZ_IGNORE   = 0x0000,
    OF_ALIGN_HORZ_LEFT     = 0x0001,
    OF_ALIGN_HORZ_RIGHT    = 0x0002,
    OF_ALIGN_HORZ_CENTER   = 0x0004,
};

enum ofRectMode{
	OF_RECTMODE_CORNER=0,
 	OF_RECTMODE_CENTER=1
};

// only used in ofRectangle
enum ofScaleMode{
    // ofScaleMode can usually be interpreted as a concise combination of
    // an ofAspectRatioMode, an ofAlignVert and an ofAlignHorz.
    
    // fits the SUBJECT rect INSIDE the TARGET rect.
    // Preserves SUBJECTS's aspect ratio.
    // Final Subject's Area <= Target's Area.
    // Subject's Center == Target's Center
    OF_SCALEMODE_FIT     = 0,
    // FILLS the TARGET rect with the SUBJECT rect.
    // Preserves the SUBJECT's aspect ratio.
    // Subject's Area >= Target's Area.
    // Subject's Center == Target's Center
    OF_SCALEMODE_FILL    = 1,
    // Preserves the SUBJECT's aspect ratio.
    // Subject's Area is Unchanged
    // Subject's Center == Target's Center
    OF_SCALEMODE_CENTER  = 2, // centers the subject
    // Can CHANGE the SUBJECT's aspect ratio.
    // Subject's Area == Target's Area
    // Subject's Center == Target's Center
 	OF_SCALEMODE_STRETCH_TO_FILL = 3, // simply matches the target dims
};

enum ofImageType{
	OF_IMAGE_GRAYSCALE		= 0x00,
 	OF_IMAGE_COLOR			= 0x01,
 	OF_IMAGE_COLOR_ALPHA	= 0x02,
 	OF_IMAGE_UNDEFINED		= 0x03
};

#define		OF_MAX_STYLE_HISTORY	32
#define		OF_MAX_VIEWPORT_HISTORY	32
#define		OF_MAX_CIRCLE_PTS 1024

// Blend Modes
enum ofBlendMode{
	OF_BLENDMODE_DISABLED = 0,
	OF_BLENDMODE_ALPHA 	  = 1,
	OF_BLENDMODE_ADD 	  = 2,
	OF_BLENDMODE_SUBTRACT = 3,
	OF_BLENDMODE_MULTIPLY = 4,
	OF_BLENDMODE_SCREEN   = 5
};

//this is done to match the iPhone defaults 
//we don't say landscape, portrait etc because iPhone apps default to portrait while desktop apps are typically landscape
enum ofOrientation{
	OF_ORIENTATION_DEFAULT = 1,	
	OF_ORIENTATION_180 = 2,
    OF_ORIENTATION_90_LEFT = 3,
	OF_ORIENTATION_90_RIGHT = 4,
    OF_ORIENTATION_UNKNOWN = 5
};

// gradient modes when using ofBackgroundGradient
enum ofGradientMode {
	OF_GRADIENT_LINEAR = 0,
	OF_GRADIENT_CIRCULAR,
	OF_GRADIENT_BAR
};

// these are straight out of glu, but renamed and included here
// for convenience
//
// we don't mean to wrap the whole glu library (or any other library for that matter)
// but these defines are useful to give people flexibility over the polygonizer
//
// some info:
// http://glprogramming.com/red/images/Image128.gif
//
// also: http://glprogramming.com/red/chapter11.html
// (CSG ideas)

enum ofPolyWindingMode{
	OF_POLY_WINDING_ODD 	        ,
	OF_POLY_WINDING_NONZERO         ,
	OF_POLY_WINDING_POSITIVE        ,
	OF_POLY_WINDING_NEGATIVE        ,
	OF_POLY_WINDING_ABS_GEQ_TWO
};

#define 	OF_CLOSE						  (true)


enum ofHandednessType {OF_LEFT_HANDED, OF_RIGHT_HANDED};

enum ofMatrixMode {OF_MATRIX_MODELVIEW=0, OF_MATRIX_PROJECTION, OF_MATRIX_TEXTURE};

enum ofPixelFormat{
	// grayscale
	OF_PIXELS_GRAY = 0,
	OF_PIXELS_GRAY_ALPHA = 1,

	// rgb (can be 8,16 or 32 bpp depending on pixeltype)
	OF_PIXELS_RGB=2,
	OF_PIXELS_BGR=3,
	OF_PIXELS_RGBA=4,
	OF_PIXELS_BGRA=5,

	// rgb 16bit
	OF_PIXELS_RGB565=6,

	// yuv
	OF_PIXELS_NV12=7,
	OF_PIXELS_NV21=8,
	OF_PIXELS_YV12=9,
	OF_PIXELS_I420=10,
	OF_PIXELS_YUY2=11,
	OF_PIXELS_UYVY=12,

	// yuv planes
	OF_PIXELS_Y,
	OF_PIXELS_U,
	OF_PIXELS_V,
	OF_PIXELS_UV,
	OF_PIXELS_VU,

	OF_PIXELS_UNKNOWN=-1,
	OF_PIXELS_NATIVE=-2
};

#define OF_PIXELS_MONO OF_PIXELS_GRAY
#define OF_PIXELS_R OF_PIXELS_GRAY
#define OF_PIXELS_RG OF_PIXELS_GRAY_ALPHA


//--------------------------------------------
//ofBitmap draw mode
enum ofDrawBitmapMode{
	OF_BITMAPMODE_SIMPLE = 0,
	OF_BITMAPMODE_SCREEN,
	OF_BITMAPMODE_VIEWPORT,
	OF_BITMAPMODE_MODEL,
	OF_BITMAPMODE_MODEL_BILLBOARD
};

enum ofTextEncoding{
	OF_ENCODING_UTF8,
	OF_ENCODING_ISO_8859_15
};
