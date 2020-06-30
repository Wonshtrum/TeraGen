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
		Logger(const char* name, LogLevel level = trace, bool bold = false): m_name(name), m_level(level), m_bold(bold) {
			m_prompt = "%N: ";
			log(trace, "SYSTEM", 0, "Initialised");
		}

		~Logger() { log(trace, "SYSTEM", 0, "Terminated"); }

		void header(LogLevel level, const char* file, int line) {
			std::cout << (m_bold ? BOLD : "") << COLOR(m_colorCode[level]);
			int i = 0;
			bool mod = false;
			while (m_prompt[i]) {
				if (mod) {
					switch (m_prompt[i]) {
						case 'N':
							std::cout << m_name;
							break;
						case 'L':
							std::cout << m_levelCode[level];
							break;
						case 'f':
							std::cout << file;
							break;
						case 'l':
							std::cout << line;
							break;
						default:
							std::cout << m_prompt[i];
							break;
					}
					mod = false;
				} else if (m_prompt[i] == '%') {
					mod = true;
				} else {
					std::cout << m_prompt[i];
				}
				i++;
			}
		}
		
		template<typename... T>
		void log(LogLevel level, const char* file, int line, T... param) {
			if (level >= m_level) {
				header(level, file, line);
				int a[] = {(std::cout << param,0)...};
				if (a) {}
				std::cout << END << std::endl;
			}
		}

		void setLevel(LogLevel level) { m_level = level; }
		void setPrompt(std::string prompt) { m_prompt = prompt; }
		void setColorCode(LogLevel level, Color colorCode) { m_colorCode[level] = colorCode; }
		void setColorCodes(const Color* colorCode) {
			for (int i = 0 ; i < 6 ; i++) {
				m_colorCode[i] = colorCode[i];
			}
		}
		void setColorCodes(std::initializer_list<Color> colorCode) { setColorCodes(colorCode.begin()); }
		void setLevelCode(LogLevel level, std::string levelCode) { m_levelCode[level] = levelCode; }
		void setLevelCodes(const std::string* levelCode) {
			for (int i = 0 ; i < 6 ; i++) {
				m_levelCode[i] = levelCode[i];
			}
		}
		void setLevelCodes(std::initializer_list<std::string> levelCode) { setLevelCodes(levelCode.begin()); }
};

class LOG {
	private:
		static Logger* s_coreLogger;
		static Logger* s_appLogger;

	public:
		static void init() {
			s_coreLogger = new Logger("CORE", trace, true);
			s_appLogger = new Logger("APP");
		}

		static Logger* getCoreLogger() { return s_coreLogger; }
		static Logger* getAppLogger() { return s_appLogger; }

		static void terminate() {
			delete s_coreLogger;
			delete s_appLogger;
		}
};
