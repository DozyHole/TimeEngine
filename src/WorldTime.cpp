//#include "TimeEngine.h"
#include "WorldTime.h"

UWorldTime::UWorldTime()
{
	_count				= 0.0f;
	_scale				= 1.0f;
	_t					= 0.0f;
	_timeYear			= 1246;
	_timeMonth			= 0;
	_timeDay			= 0.0f;
	_timeHour			= 0.0f;
	_timeMinute			= 0.0f;
	_timeSecond			= 0.0f;
}

UWorldTime::~UWorldTime() {}

void UWorldTime::Tick(float DeltaTime)
{
	_t += DeltaTime * _scale;
	CalculateDate();
}

std::string	UWorldTime::GetDateString()
{
	std::string date = std::to_string(_date._date + 1);
	if (date.length() == 1)
	{
		date = "0" + date;
	}
	std::string strDate = Date::GetDay(_date._day).substr(0, 3) + " " + date + " " + Date::GetMonth(_date._month).substr(0, 3) + " " + std::to_string(_date._year);
	return strDate;
}

//FString	UWorldTime::GetDateFString()
//{
//	std::string str = GetDateString();
//    FString strDate = FString(UTF8_TO_TCHAR(str.c_str()));
//	return strDate;
//}

//FString	UWorldTime::GetTimeFString()
//{
//	std::string str = GetTimeString();
//	FString strTime = FString(UTF8_TO_TCHAR(str.c_str()));
//	return strTime;
//}

std::string	UWorldTime::GetTimeString()
{
	// hour
	std::string hour = std::to_string(_date.GetTime()._hour);
	// minute
	std::string minute = std::to_string(_date.GetTime()._minute);
	if (minute.length() == 1)
	{
		minute = "0" + minute;
	}
	// second
	std::string second = std::to_string(_date.GetTime()._second);
	std::size_t pos = second.find(".");
	std::string strSec = second.substr(0, pos);
	if (strSec.length() == 1)
	{
		strSec = "0" + strSec;
	}
	// centisecond
	std::string centiSecond = std::to_string(_date.GetTime()._centiSecond);// second.substr(pos + 1, 2);
	if (centiSecond.size() == 1)
	{
		centiSecond = "0" + centiSecond;
	}
	std::string strTime = /*hour + ":" +  */minute + ":" + strSec +":" + centiSecond;
	return strTime;
	
}

float UWorldTime::GetWorldTime() const
{
	return _t;// timeWorld;
}

float UWorldTime::GetDayTime()
{
	return (float)(_date.GetTime()._second + _date.GetTime()._hour * SECONDS_PER_HOUR) + _count;
}

float UWorldTime::GetMinuteTime() const
{
	return _timeMinute;
}

void UWorldTime::SetScale(float scale)
{
	_scale = scale;
}

void UWorldTime::FastForward()
{
	if (_scale == 0.0f)
		_scale = 0.5f;
	else if (_scale == -0.5f)
		_scale = 0.0f;
	else if (_scale > 0.0f)
		_scale = _scale * 2.0f;
	else if (_scale < 0.0f)
		_scale = _scale * 0.5f;
}

void UWorldTime::Rewind()
{
	if (_scale == 0.0f)
		_scale = -0.5f;
	else if (_scale == 0.5f)
		_scale = 0.0f;
	else if (_scale > 0.0f)
		_scale = _scale * 0.5f;
	else if (_scale < 0.0f)
		_scale = _scale * 2.0f;
}

Date UWorldTime::GetDate() 
{
	return _date;
}

void UWorldTime::CalculateDate()
{
	// get rid of while loops once working?
	while (_t < 0.0)
	{
		_timeMonth--;
		if (_timeMonth == -1)
		{
			_timeMonth = MONTHS_PER_YEAR - 1;
			_timeYear--;
		}

		// _t is negative make it positive for previous month
		_t += SECONDS_PER_MONTH;
	}
	while (_t > SECONDS_PER_MONTH)
	{
		_timeMonth++;
		if (_timeMonth == MONTHS_PER_YEAR)
		{
			_timeMonth = 0;
			_timeYear++;
		}

		_t -= SECONDS_PER_MONTH;
	}
	// date
	_timeDay = (float)fmod(_t, SECONDS_PER_DAY);
	unsigned int date = ((unsigned int)(_t / SECONDS_PER_DAY)) % DAYS_PER_MONTH;
	// hour
	_timeHour = (float)fmod(_t, SECONDS_PER_HOUR);
	unsigned int hour = ((unsigned int)(_t / SECONDS_PER_HOUR)) % HOURS_PER_DAY;
	_timeMinute = (float)fmod(_t, SECONDS_PER_MINUTE);
	unsigned int minute = ((unsigned int)(_t / SECONDS_PER_MINUTE)) % MINUTES_PER_HOUR;
	unsigned int day = date % DAYS_PER_WEEK;
	short second =( (unsigned int)_t )% 60;
	float wholePart;
	short centiSecond = modf(_t, &wholePart) * 100;

	//_date = Date(_timeYear, (eDay)day, (eMonth)_timeMonth, date, hour, minute, _timeMinute);
	_date = Date(_timeYear, (eMonth)_timeMonth, date, Time(hour, minute, second, centiSecond));
}
