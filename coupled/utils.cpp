#include <fstream>
#include <iostream>

const char* readFile(const char* name) {
	std::streampos size;
	char* content;
	std::ifstream file(name);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
		content = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(content, size);
		file.close();
		return content;
	}
	std::cout << "Could not open file \"" << name << "\"" << std::endl;
	exit(EXIT_FAILURE);
}
