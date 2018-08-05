#pragma once
#include <string>

const int MONTHS_PER_YEAR = 12;
const int DAYS_PER_MONTH = 28;
const int DAYS_PER_WEEK = 7;
const int HOURS_PER_DAY = 1;
const int MINUTES_PER_HOUR = 60;
const int SECONDS_PER_MINUTE = 60;
const int SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
const int SECONDS_PER_DAY = HOURS_PER_DAY * SECONDS_PER_HOUR;						// 1 real world hour
const int SECONDS_PER_MONTH = SECONDS_PER_DAY * DAYS_PER_MONTH;						// 28 days in each month
const int SECONDS_PER_YEAR = SECONDS_PER_MONTH * 12;


	enum eDay
	{
		DAY_MONDAY,
		DAY_TUESDAY,
		DAY_WEDNESDAY,
		DAY_THURSDAY,
		DAY_FRIDAY,
		DAY_SATURDAY,
		DAY_SUNDAY,
		DAY_NONE
	};

	enum eMonth
	{
		MONTH_JAN,
		MONTH_FEB,
		MONTH_MAR,
		MONTH_APR,
		MONTH_MAY,
		MONTH_JUN,
		MONTH_JUL,
		MONTH_AUG,
		MONTH_SEP,
		MONTH_OCT,
		MONTH_NOV,
		MONTH_DEC,
		MONTH_NONE
	};

	class Time
	{
	public:
		Time();
		Time(short hour, short minute, short second, short centiSecond);
		~Time();

		float GetTimeSeconds();

		short _hour, _minute, _second, _centiSecond;
	};

	class Date
	{
	public:
		Date();
		Date(unsigned int year, eMonth month, short date, Time& t);
		//Date(short hour, short minute, float second);

		~Date();

		Time GetTime();

		static std::string GetDay(short index);
		static std::string GetMonth(short index);

		//bool GetHitDay(Date &timeStart, Date &timeEnd);


		eDay				_day;
		eMonth				_month;
		unsigned int		_year;
		short				_date;
		Time				_time;
		//short				_hour;
		//short				_minute;
		//float				_second;
		
	};
