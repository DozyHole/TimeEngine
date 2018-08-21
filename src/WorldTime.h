#pragma once
#include "Date.h"
//#include "WorldTime.generated.h"


	//UCLASS(Blueprintable)
	class UWorldTime// : public UObject
	{
		//GENERATED_BODY()

	public:
		UWorldTime();
		~UWorldTime();

		/*
			Call each frame to update
		*/
		void			Tick(float DeltaTime);
		
		/*
			Returns raw world time as a float, Date object is calculated from this number
		*/
		float			GetWorldTime() const;

		/*
			Returns seconds passed for this current day
		*/
		float			GetDayTime();

		/*
			Returns seconds passed for this current day
		*/
		float			GetMinuteTime() const;

		/*
			Sets the rate at which time passes with 1.0f being normal
		*/
		void			SetScale(float scale);

		/*
			Increase rate at which time passes
		*/
		void			FastForward();

		/*
			Decrease rate at which time passes, can go negative
		*/

		void			Rewind();
		/*
			Returns const pointer to date object
		*/
		Date			GetDate();

		/*
			Returns date as a string for easy debugging
		*/
		std::string		GetDateString();

		/*
		Returns date as a string for easy debugging
		*/
		//UFUNCTION(BlueprintCallable, Category = "World Time")
		//FString			GetDateFString();

		/*
			Returns time as a string for easy debugging
		*/
		std::string		GetTimeString();



		//UFUNCTION(BlueprintCallable, Category = "World Time")
		//FString			GetTimeFString();

		// cache all different time values
		unsigned int	_timeYear;
		int				_timeMonth;
		float			_timeDay;
		float			_timeHour;
		float			_timeMinute;
		float			_timeSecond;
        Time            _tempTime;

	protected:
		void			CalculateDate();


		// world time
		float			_t;
		// this keeps track of decimal part of _t
		float           _count;
		// speed time is passing at
		float			_scale;
		// Date populated each frame
		Date			_date;

	};


