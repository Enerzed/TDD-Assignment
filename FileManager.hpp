#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "RSAEncryption.hpp"
#include "AESEncryption.hpp"


namespace fs = std::filesystem;


class FileManager
{
private:
	std::string folder_path;

	RSAEncryption rsa;
	AESEncryption aes;

	std::vector<fs::path> GetFilesInFolder() const;
	void ProcessFile(const fs::path& filePath, bool encrypt);

public:
	FileManager(const std::string&);

	void EncryptAllFiles();
	void DecryptAllFiles();
};