#pragma once

// Cross-platform deprecation warning
#ifdef __GNUC__
	// clang also has this defined. deprecated(message) is only for gcc>=4.5
	#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 5)
        #define OF_DEPRECATED_MSG(message, func) func __attribute__ ((deprecated(message)))
    #else
        #define OF_DEPRECATED_MSG(message, func) func __attribute__ ((deprecated))
    #endif
	#define OF_DEPRECATED(func) func __attribute__ ((deprecated))
	#define OF_INTERNAL_DEPRECATED(func) func __attribute__ ((deprecated("OF core deprecated")))
#elif defined(_MSC_VER)
	#define OF_DEPRECATED_MSG(message, func) __declspec(deprecated(message)) func
	#define OF_DEPRECATED(func) __declspec(deprecated) func
	#define OF_INTERNAL_DEPRECATED(func) __declspec(deprecated("OF core deprecated")) func
#else
	#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
	#define OF_DEPRECATED_MSG(message, func) func
	#define OF_DEPRECATED(func) func
#endif
