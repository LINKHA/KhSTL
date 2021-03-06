#pragma once
#ifdef _MSC_VER
#	pragma warning(disable:4481)
#endif

// Shared library exports
/* #undef KH_STL_SHARED */
#if defined(_WIN32) && defined(KH_STL_SHARED)
#	ifdef _MSC_VER
#		pragma warning(disable:4251)
#	endif
#	ifdef AUTO_EXPORTS
#		define KH_STL_API __declspec(dllexport)
#	else
#		define KH_STL_API __declspec(dllimport)
#	endif
#else
#	define KH_STL_API
#endif
