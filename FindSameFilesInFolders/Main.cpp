#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdio.h>

std::string ltos(long l)
{
	std::stringstream os;
	os << l;
	std::string result;
	std::istringstream is(os.str());
	is >> result;
	return result;
}

static void RecursivePathToFindSameFile(std::string path, std::vector<std::string> &vector) {

	std::experimental::filesystem::path filePath(path);
	for (std::experimental::filesystem::recursive_directory_iterator next(filePath), end; next != end; next++) {
		if (std::experimental::filesystem::is_directory(next->path())) {
			continue;
		}

		std::string fileName = next->path().filename().string();
		std::string fileParentPath = next->path().parent_path().string();
		std::string fileFullPath = fileParentPath + "\\" + fileName;
		
		std::ifstream afile(fileFullPath);
		
		if (afile.good()) {
			afile.seekg(0, std::ios::end);
			long size = (long)afile.tellg();

			std::string key = fileName + "|file size:" + ltos(size);
			//std::cout << key << std::endl;
			if (std::find(vector.begin(), vector.end(), key) != vector.end()) {
				//contains
				std::cout << "del \"" + fileFullPath << "\"" << std::endl;
			}
			else {
				//not contains
				vector.push_back(key);
			}
		}
		afile.close();
	}
}


int main(int argc, char** argv) {

	std::vector<std::string> vecOfFolders = std::vector<std::string>();
	if (argc == 0) {
	
		std::cout << "Usage:" << std::endl;
		std::cout << "FindSameFilesInFolders.exe C:\app C:\app2" << std::endl;
		return 0;
	}
	for (int i = 0; i < argc; i++) {
		if (i == 0)continue;
		//std::cout << argv[i];
		vecOfFolders.push_back(argv[i]);
	}

	std::cout << "Found same files in foldrs:" << std::endl;
	if (vecOfFolders.size() > 0) {
		std::vector<std::string> FileNameAndSize = std::vector<std::string>();
		for (unsigned long i = 0; i < vecOfFolders.size(); i++) {
			//std::cout << vecOfFolders[i].c_str() << std::endl;
			RecursivePathToFindSameFile(vecOfFolders[i], FileNameAndSize);
		}
	}
		
	std::cout << "." <<std::endl;
	
	std::string anyString;
	std::cin >> anyString;
}