#ifndef __CORE_H__
#define __CORE_H__

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <initializer_list>
#include <functional>
#include "logger/logger.h"
#include "config.h"

#define S_BIND(x) std::bind(&x, std::placeholders::_1)
#define M_BIND(x) std::bind(&x, this, std::placeholders::_1)
#define BIND(x, y) std::bind(&x, &y, std::placeholders::_1)
typedef uint8_t Block;
typedef uint16_t ChunkId;

#ifdef DEBUG_MOD
	#define CORE_LOGGER      LOG::getCoreLogger()
	#define CORE_TRACE(...)  LOG::getCoreLogger()->log(trace, __FILE__, __LINE__, __VA_ARGS__)
	#define CORE_DEBUG(...)  LOG::getCoreLogger()->log(debug, __FILE__, __LINE__, __VA_ARGS__)
	#define CORE_INFO(...)   LOG::getCoreLogger()->log(info, __FILE__, __LINE__, __VA_ARGS__)
	#define CORE_WARN(...)   LOG::getCoreLogger()->log(warning, __FILE__, __LINE__, __VA_ARGS__)
	#define CORE_ERROR(...)  LOG::getCoreLogger()->log(error, __FILE__, __LINE__, __VA_ARGS__)
	#define CORE_CRITIC(...) LOG::getCoreLogger()->log(critical, __FILE__, __LINE__, __VA_ARGS__)

	#define APP_LOGGER      LOG::getAppLogger()
	#define APP_TRACE(...)  LOG::getAppLogger()->log(trace, __FILE__, __LINE__, __VA_ARGS__)
	#define APP_DEBUG(...)  LOG::getAppLogger()->log(debug, __FILE__, __LINE__, __VA_ARGS__)
	#define APP_INFO(...)   LOG::getAppLogger()->log(info, __FILE__, __LINE__, __VA_ARGS__)
	#define APP_WARN(...)   LOG::getAppLogger()->log(warning, __FILE__, __LINE__, __VA_ARGS__)
	#define APP_ERROR(...)  LOG::getAppLogger()->log(error, __FILE__, __LINE__, __VA_ARGS__)
	#define APP_CRITIC(...) LOG::getAppLogger()->log(critical, __FILE__, __LINE__, __VA_ARGS__)

	#define CORE_ASSERT(x, ...) { if (!(x)) { CORE_CRITIC("Assertion Failed: " __VA_ARGS__); exit(EXIT_FAILURE); }
	#define CORE_ASSERT_NOT(x, ...) { if (x) { CORE_CRITIC("Assertion Failed: " __VA_ARGS__); exit(EXIT_FAILURE); }

	#define APP_ASSERT(x, ...) { if (!(x)) { APP_CRITIC("Assertion Failed: " __VA_ARGS__); exit(EXIT_FAILURE); }
	#define APP_ASSERT_NOT(x, ...) { if (x) { APP_CRITIC("Assertion Failed: " __VA_ARGS__); exit(EXIT_FAILURE); }

#else
	#define CORE_TRACE(...)
	#define CORE_DEBUG(...)
	#define CORE_INFO(...)
	#define CORE_WARN(...)
	#define CORE_ERROR(...)
	#define CORE_CRITIC(...)

	#define APP_TRACE(...)
	#define APP_DEBUG(...)
	#define APP_INFO(...)
	#define APP_WARN(...)
	#define APP_ERROR(...)
	#define APP_CRITIC(...)

	#define CORE_ASSERT(x, ...)
	#define CORE_ASSERT_NOT(x, ...)

	#define APP_ASSERT(x, ...)
	#define APP_ASSERT_NOT(x, ...)

#endif

#endif
