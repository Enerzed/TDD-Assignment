#include "FileManager.hpp"


FileManager::FileManager(const std::string& folder_path) : folder_path(folder_path)
{
	rsa.GenerateKeys();
	aes.GenerateKeyAndIV();
}

std::vector<fs::path> FileManager::GetFilesInFolder() const
{
	std::vector<fs::path> files;
	for (const auto& entry : fs::directory_iterator(folder_path))
	{
		if (fs::is_regular_file(entry))
		{
			files.push_back(entry.path());
		}
	}
	return files;
}

void FileManager::ProcessFile(const fs::path& file_path, bool encrypt)
{
	std::ifstream input_file(file_path, std::ios::binary);
	if (!input_file)
	{
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return;
	}

	std::string content((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	input_file.close();

	std::string processed_content;
	if (encrypt)
	{
		processed_content = rsa.Encrypt(content);
		processed_content = aes.Encrypt(processed_content);
	}
	else
	{
		processed_content = aes.Decrypt(content);
		processed_content = rsa.Decrypt(processed_content);
	}

	std::ofstream output_file(file_path, std::ios::binary);
	if (!output_file)
	{
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return;
	}

	output_file << processed_content;
	output_file.close();
}

void FileManager::EncryptAllFiles()
{
	for (const auto& file_path : GetFilesInFolder())
	{
		ProcessFile(file_path, true);
	}
}

void FileManager::DecryptAllFiles()
{
	for (const auto& file_path : GetFilesInFolder())
	{
		ProcessFile(file_path, false);
	}
}