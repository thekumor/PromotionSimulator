#include "date.h"

namespace promsim
{

	Date::Date(std::uint16_t year, std::uint8_t month, std::uint8_t day)
		: Year(year), Month(month), Day(day)
	{
	}

	std::string Date::ToString(const char* fmt) const
	{
		std::string str;
		const char* c = fmt;

		while (*c != '\0')
		{
			switch (*c)
			{
				case 'Y':
				{
					str += std::to_string(static_cast<std::uint16_t>(Year));
				} break;

				case 'M':
				{
					str += std::to_string(static_cast<std::uint8_t>(Month));
				} break;

				case 'D':
				{
					str += std::to_string(static_cast<std::uint8_t>(Day));
				} break;

				default:
				{
					str += *c;
				} break;
			}

			c++;
		}

		return str;
	}

	void Date::Progress()
	{
		bool isLongMonth = (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12);
		bool isShortMonth = Month == 2;
		
		bool isLeapYear = Year % 4 == 0;

		Day++;

		if ((Day == 31 && !isLongMonth) || (Day == 32) ||
			(Month == 2 && Day == 29 && !isLeapYear) || (Month == 2 && Day == 30))
		{
			Month++;
			Day = 1;

			if (Month == 13)
			{
				Month = 1;
				Year++;
			}
		}
	}

	void Date::Fastforward(std::uint32_t days)
	{
		for (std::int32_t i = 0; i < days; i++)
			Progress();
	}

}