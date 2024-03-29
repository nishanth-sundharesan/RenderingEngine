#include "PchLibrary.h"
#include "Utility.h"
#include <vector>
#include <fstream>

using namespace std;

namespace Library
{
	// TODO: Add code to load files from the output directory rather than changing it from the project settings as it cannot be committed. Probably with shlapi.
	void Utility::LoadBinaryFile(const string& filename, vector<char>& data)
	{
		ifstream file(filename.c_str(), ios::binary);
		if (file.fail())
		{
			throw GameException("Could not open file.");
		}

		file.seekg(0, ios::end);
		uint32_t size = static_cast<uint32_t>(file.tellg());

		if (size > 0)
		{
			data.resize(size);
			file.seekg(0, ios::beg);
			file.read(&data.front(), size);
		}

		file.close();
	}
}


