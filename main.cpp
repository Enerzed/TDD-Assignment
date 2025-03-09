#include "FileManager.hpp"


int main()
{
	FileManager file_manager("C:\\Users\\laske\\source\\repos\\TOPO132\\folder_with_files\\");
	file_manager.EncryptAllFiles();
	getchar();
	file_manager.DecryptAllFiles();
}