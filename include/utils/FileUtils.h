#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "utils/Log.h"

const char* LOCAL_FILE_DIR = "";
const char* GLOBAL_FILE_DIR = "";

//std::string FindFileOrThrow(const std::string &strBasename) {
//	std::string strFilename = LOCAL_FILE_DIR + strBasename;
//	std::ifstream testFile(strFilename.c_str());
//	if (testFile.is_open())
//		return strFilename;
//
//	strFilename = GLOBAL_FILE_DIR + strBasename;
//	testFile.open(strFilename.c_str());
//	if (testFile.is_open())
//		return strFilename;
//
//	throw std::runtime_error("Could not find the file " + strBasename);
//}

char * loadFile(const char *filePath) {
	const size_t blockSize = 512;
	FILE *fp;
	char buf[blockSize];
	char *source = NULL;
	size_t tmp, sourceLength = 0;

	// open file
	fp = fopen(filePath, "r");
	if (!fp) {
		Log::print("shaderLoadSource(): Unable to open %s for reading\n", filePath);
		return NULL;
	}

	// read the entire file into a string
	while ((tmp = fread(buf, 1, blockSize, fp)) > 0) {
		char *newSource = (char*) malloc(sourceLength + tmp + 1);
		if (!newSource) {
			Log::print("shaderLoadSource(): malloc failed\n");
			if (source) {
				free(source);
			}
			return NULL;
		}

		if (source) {
			memcpy(newSource, source, sourceLength);
			free(source);
		}
		memcpy(newSource + sourceLength, buf, tmp);

		source = newSource;
		sourceLength += tmp;
	}

	// close the file and null terminate the string
	fclose(fp);

	if (source) {
		source[sourceLength] = '\0';
	}

	return source;
}

#endif /* FILE_UTILS_H_ */
