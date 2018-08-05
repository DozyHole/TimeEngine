#pragma once
#include "Date.h"
#include <vector>
#include "Map.h"
#include "WorldTime.h"
#include <map>

class Routine
{
public:
	Routine(Time startTime, Time finishTime);
	~Routine();
	Time						_startTime;
	Time						_finishTime;
	std::vector<unsigned int>	_nodes;
};

class NPC
{
public:
	NPC();
	~NPC();
	int							GetLocation(UWorldTime &t);
	void						PopulateRoutines();
	void						Draw();
	unsigned int				_homeNode;
	std::vector<Routine*>		_routines;  // monday - make 2d for whole week

	// work out float value (week) for routine end time
	std::map<float, Routine*>	_routinesWeekly;

};



