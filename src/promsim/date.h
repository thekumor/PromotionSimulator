#pragma once

// STL
#include <cstdint>
#include <string>

namespace promsim
{

	struct Date
	{
		Date(std::uint16_t year, std::uint8_t month, std::uint8_t day);
		Date() = default;

		std::string ToString(const char* fmt) const;
		void Progress();
		
		// A rather quick one, but don't kill an ant with a sledgehammer.
		void Fastforward(std::uint32_t days);

		std::uint16_t Year;
		std::uint8_t Month, Day;
	};

}