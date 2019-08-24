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
	Time						_startTime;
	std::vector<void*>			_nodes;
	float						_cost;
};

// holds an array of routines that are ordered with a float value 
class RoutineSorted
{
public:
	RoutineSorted(Routine* routine, float startTime);

};

class NPC
{
public:
	NPC();
	~NPC();
	int							GetLocation(UWorldTime &t);
	void						PopulateRoutines(Map* map);
	void						SetHomeNode(int node);
	void						Draw();
	unsigned int				_homeNode;
	//std::vector<Routine*>		_routines;  // monday - make 2d for whole week

	// work out float value (week) for routine end time
	std::vector<std::map<float, Routine*> > _routinesWeekly;
};



