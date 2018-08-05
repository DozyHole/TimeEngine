//#include "TimeEngine.h"
#include "Date.h"

//using namespace TimeEngine;

// should date be split into day/date - day wil hold time and date will hold year/month/day? Day could be member variable of date?
Time::Time() : Time(0, 0, 0, 0)
{
}

Time::Time(short hour, short minute, short second, short centiSecond) : _hour(hour), _minute(minute), _second(second), _centiSecond(centiSecond)
{
}

Time::~Time()
{
}

float Time::GetTimeSeconds()
{
	float t = _hour * SECONDS_PER_HOUR + _minute * SECONDS_PER_MINUTE + _second + ((float)_centiSecond)/100.0f;
	return t;
}



//Date::Date() : _year(0), _day(DAY_MONDAY), _month(MONTH_JAN), _date(1), _hour(0), _minute(0), _second(0.0f) {}
Date::Date(unsigned int year, eMonth month, short date, Time& t) : _year(year), _month(month), _date(date),  _time(t) {}
//Date::Date(short hour, short minute, float second) : _year(0), _day(DAY_NONE), _month(MONTH_NONE), _date(0), _hour(hour), _minute(minute), _second(second) {}

Date::Date() {}
Date::~Date() {}

Time Date::GetTime()
{
	return _time;
}

std::string Date::GetDay(short index)
{
	std::string str("");
	switch (index)
	{
	case 0:
		str = "Monday";
		break;
	case 1:
		str = "Tuesday";
		break;
	case 2:
		str = "Wednesday";
		break;
	case 3:
		str = "Thursday";
		break;
	case 4:
		str = "Friday";
		break;
	case 5:
		str = "Saturday";
		break;
	case 6:
		str = "Sunday";
		break;
	}
	return str;
}

std::string Date::GetMonth(short index)
{
	std::string str("");
	switch (index)
	{
	case 0:
		str = "January";
		break;
	case 1:
		str = "February";
		break;
	case 2:
		str = "March";
		break;
	case 3:
		str = "April";
		break;
	case 4:
		str = "May";
		break;
	case 5:
		str = "June";
		break;
	case 6:
		str = "July";
		break;
	case 7:
		str = "August";
		break;
	case 8:
		str = "September";
		break;
	case 9:
		str = "October";
		break;
	case 10:
		str = "November";
		break;
	case 11:
		str = "December";
		break;
	}
	return str;
}


//bool Date::GetHitDay(Date &timeStart, Date &timeEnd)
//{
//	if (_hour >= timeStart._hour && _hour <= timeEnd._hour)
//	{
//		if (_minute >= timeStart._minute && _minute <= timeEnd._minute)
//		{
//			if (_second >= timeStart._second && _second <= timeEnd._second)
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
