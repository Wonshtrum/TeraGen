#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "core.h"
#include <iostream>
#include <string>

#define COLOR(x) "\033[38;5;" << x << "m"
#define BOLD "\033[1m"
#define END "\033[0m"

enum Color {
	black = 0,
	red = 1,
	green = 2,
	blue = 4,
	grey = 8,
	yellow = 11,
	lightBlue = 14,
	darkRed = 88
};

enum LogLevel {
	trace,
	debug,
	info,
	warning,
	error,
	critical
};

class Logger {
	private:
		const char* m_name;
		LogLevel m_level;
		bool m_bold;
		std::string m_prompt;
		Color m_colorCode[6] = {grey, lightBlue, green, yellow, red, darkRed};
		std::string m_levelCode[6] = {"TRC", "DBG", "INF", "WRN", "ERR", "CRT"};

	public:
		Logger(const char* name, LogLevel level = trace, bool bold = false);

		~Logger();

		void header(LogLevel level, const char* file, int line);

		template<typename... T>
		void log(LogLevel level, const char* file, int line, T... param) {
			if (level >= m_level) {
				header(level, file, line);
				int a[] = {(std::cout << param,0)...};
				if (a) {}
				std::cout << END << std::endl;
			}
		}

		void setLevel(LogLevel level);
		void setPrompt(std::string prompt);
		void setColorCode(LogLevel level, Color colorCode);
		void setColorCodes(const Color* colorCode);
		void setColorCodes(std::initializer_list<Color> colorCode);
		void setLevelCode(LogLevel level, std::string levelCode);
		void setLevelCodes(const std::string* levelCode);
		void setLevelCodes(std::initializer_list<std::string> levelCode);
};

class LOG {
	private:
		static Logger* s_coreLogger;
;
		static Logger* s_appLogger;
;

	public:
		static void init();

		static Logger* getCoreLogger();
		static Logger* getAppLogger();

		static void terminate();
};


#endif