#include "Pch.h"
#include "GameException.h"

namespace Library
{
	GameException::GameException(const char* const& message, HRESULT hr)
		: exception(message), mHR(hr)
	{
	}

	HRESULT GameException::GetHR() const
	{
		return mHR;
	}

	std::wstring GameException::GetWhatWString() const
	{
		std::string whatString(what());
		std::wstring whatWString;
		whatWString.assign(whatString.begin(), whatString.end());

		return whatWString;
	}
}