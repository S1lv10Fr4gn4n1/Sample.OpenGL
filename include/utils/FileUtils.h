#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace File {
	std::string getFileContent(const std::string &filePath) {
		std::ifstream file(filePath.c_str());
		if (!file.is_open()) {
			return "";
		}

		std::stringstream data;
		data << file.rdbuf();
		file.close();

		return data.str();
	}

}  // namespace File

#endif /* FILE_UTILS_H_ */
