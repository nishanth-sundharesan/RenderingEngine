#pragma once
#include <vector>

namespace Library_3
{
	class Utility final
	{
	public:
		Utility() = delete;
		~Utility() = delete;

		Utility(const Utility& rhs) = delete;
		Utility& operator=(const Utility& rhs) = delete;

		Utility(const Utility&& rhs) = delete;
		Utility& operator=(const Utility&& rhs) = delete;

		static void LoadBinaryFile(const std::string& filename, std::vector<char>& data);
	};
}