#pragma once
#include "PchLibrary.h"
#include <exception>

namespace Library
{
	class GameException : public std::exception
	{
	public:
		GameException(const char* const& message, HRESULT hr = S_OK);
		~GameException() = default;

		GameException(GameException& rhs) = default;
		GameException& operator=(GameException& rhs) = default;

		GameException(GameException&& rhs) = default;
		GameException& operator=(GameException&& rhs) = default;

		HRESULT GetHR() const;
		std::wstring GetWhatWString() const;

	private:
		HRESULT mHR;
	};

	inline void ThrowIfFailed(HRESULT hr, const char* const& message = "")
	{
		if (FAILED(hr))
		{
			throw GameException(message, hr);
		}
	}
}