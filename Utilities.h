#pragma once

#include <random>

namespace Utilities
{
	inline int randomNumberGenerator(const int a, const int b)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}

	inline std::string getResourceLocation() 
	{
		return "Resources/";
	}

	inline std::string getFontName()
	{
		return "Armata";
	}


}