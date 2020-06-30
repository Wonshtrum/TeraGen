#include "logger.h"


Logger::Logger(const char* name, LogLevel level, bool bold): m_name(name), m_level(level), m_bold(bold) {
	m_prompt = "%N: ";
	log(trace, "SYSTEM", 0, "Initialised");
}

Logger::~Logger() { log(trace, "SYSTEM", 0, "Terminated"); }

void Logger::header(LogLevel level, const char* file, int line) {
	std::cout << (m_bold ? BOLD : "") << COLOR(m_colorCode[level]);
	int i = 0;
	bool mod = false;
	while (m_prompt[i]) {
		if (mod) {
			switch (m_prompt[i]) {
				case 'N': std::cerr << m_name; break;
				case 'L': std::cerr << m_levelCode[level]; break;
				case 'f': std::cerr << file; break;
				case 'l': std::cerr << line; break;
				default : std::cerr << m_prompt[i]; break;
			}
			mod = false;
		} else if (m_prompt[i] == '%') {
			mod = true;
		} else {
			std::cerr << m_prompt[i];
		}
		i++;
	}
}

void Logger::setLevel(LogLevel level) { m_level = level; }
void Logger::setPrompt(std::string prompt) { m_prompt = prompt; }
void Logger::setColorCode(LogLevel level, Color colorCode) { m_colorCode[level] = colorCode; }
void Logger::setColorCodes(const Color* colorCode) {
	for (int i = 0 ; i < 6 ; i++) {
		m_colorCode[i] = colorCode[i];
	}
}
void Logger::setColorCodes(std::initializer_list<Color> colorCode) { setColorCodes(colorCode.begin()); }
void Logger::setLevelCode(LogLevel level, std::string levelCode) { m_levelCode[level] = levelCode; }
void Logger::setLevelCodes(const std::string* levelCode) {
	for (int i = 0 ; i < 6 ; i++) {
		m_levelCode[i] = levelCode[i];
	}
}
void Logger::setLevelCodes(std::initializer_list<std::string> levelCode) { setLevelCodes(levelCode.begin()); }

Logger* LOG::s_coreLogger;
Logger* LOG::s_appLogger;

void LOG::init() {
	s_coreLogger = new Logger("CORE", trace, true);
	s_appLogger = new Logger("APP");
}

Logger* LOG::getCoreLogger() { return s_coreLogger; }
Logger* LOG::getAppLogger() { return s_appLogger; }

void LOG::terminate() {
	delete s_coreLogger;
	delete s_appLogger;
}
