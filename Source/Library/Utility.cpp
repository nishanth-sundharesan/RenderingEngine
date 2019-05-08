#include "Pch.h"
#include "Utility.h"
#include <vector>
#include <fstream>

using namespace std;

namespace Library
{
	void Utility::LoadBinaryFile(const string& filename, vector<char>& data)
	{
		ifstream file(filename.c_str(), ios::binary);
		if (file.bad())
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


