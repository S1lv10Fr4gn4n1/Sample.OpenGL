#ifndef LOG_H_
#define LOG_H_

#include <cstdarg>
#include <cstdio>
#include <iostream>

namespace Log {
	inline void print(const char * _stringFormat, ...) {
		va_list args;
		va_start(args, _stringFormat);

		char * str = 0;
		vasprintf(&str, _stringFormat, args);
		std::cout << str << std::endl;
		va_end(args);
	}
}
#endif /* LOG_H_ */
