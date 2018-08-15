#pragma once
#include "Date.h"
#include <vector>
#include "Map.h"
#include "WorldTime.h"
#include <map>
#include "Map.h"

class Routine
{
public:
	Routine(Map* map, Time startTime, const int startNodeIndex, const int endNodeIndex);
	~Routine();
	//void SetPath();
	Time						_startTime;
	//Time						_finishTime;
	std::vector<void*>			_nodes;
	float						_cost;
};

class NPC
{
public:
	NPC();
	~NPC();
	int							GetLocation(UWorldTime &t);
	void						PopulateRoutines(Map* map);
	void						Draw();
	unsigned int				_homeNode;
	//std::vector<Routine*>		_routines;  // monday - make 2d for whole week

	// work out float value (week) for routine end time
	std::map<float, Routine*>	_routinesWeekly;

};



