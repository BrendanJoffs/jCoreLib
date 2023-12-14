#pragma once
#if DEBUG

#ifndef JCORELIB_ERROR_DEBUG_INFO
	#define JCORELIB_ERROR_DEBUG_INFO

	#define RESULT Internal::EndResult
	#define RETURN(X) return Internal::EndResult::##X

	#define MINIMUM_REPORTING_LEVEL Internal::MessageLevel::Debug

	#ifndef JCORELIB_ERROR_USE_TRACE
		#define DISABLE_TRACE
	#endif // !JCORELIB_ERROR_USE_TRACE

	#ifndef JCORELIB_ERROR_SELF_WARNINGS
		#define JCORELIB_ERROR_SELF_WARNINGS true
	#endif // !JCORELIB_ERROR_SELF_WARNING
#endif // !JCORELIB_ERROR_DEBUG_INFO

namespace Internal {

	EXTERNAL enum class EndResult : uint8_t {

		Success = 0,			// generic success code
		Failed = 1,				// generic failed code

		//general
		Flagged = 2,			// something was unexpectd, however nothing caused any erors.

		//ptr stuff
		NullIn = 3,				// Nullptr passed to non-nullptr allowed field.
		NullVar = 4,			// non-input variable set to nullptr when not allowed.
		NullOut = 5,			// function failed to find and returned nullptr instead of specified ptr type.
		
		//sizing stuffs
		Overflow = 6,			// data given was too lage to be stored in container. usually arrays
		IndexOutOfBounds = 7,	// attempt to access data at a location out of bounds.
		
		PLACEHOLDER
	};

}
#endif // DEBUG