#include "NPC.h"

Routine::Routine(Map* map, Time startTime, const int startNodeIndex, const int endNodeIndex) : _startTime(startTime)
{
	//while (_nodes.size() == 0)
	//{
		_nodes = map->GetPath(startNodeIndex, endNodeIndex, &_cost);
	//}
	if (_nodes.size() == 0)
	{
		bool error = true;
	}
}

Routine::~Routine()
{

}

NPC::NPC()
{
	_homeNode = 0;// homeNode;
	for (int i = 0; i < DAYS_PER_WEEK; i++)
	{
		_routinesWeekly.push_back(std::map<float, Routine*>());
	}
}

NPC::~NPC()
{
	// empty routines

}

void NPC::SetHomeNode(int node)
{
	_homeNode = node;
}

void AddRandomRoutine(Map* map, std::vector<std::map<float, Routine*>*> &days, short startLocation, short endLocation)
{
	short hourThere = rand() % 30;
	short hourBack = hourThere + 10;
	
	Routine* routineThere = new Routine(map, Time(0, hourThere, 0, 0), startLocation, endLocation);
	Routine* routineBack = new Routine(map, Time(0, hourBack, 0, 0), endLocation, startLocation);
	for (auto &d : days)
	{
		d->insert(std::pair<float, Routine*>(routineThere->_startTime.GetTimeSeconds(), routineThere));
		d->insert(std::pair<float, Routine*>(routineBack->_startTime.GetTimeSeconds(), routineBack));
	}
}

void NPC::PopulateRoutines(Map* map)
{
	//Routine* routine1 = new Routine(map, Time(0, 0, 2, 0), 0, 2767);
	//Routine* routine2 = new Routine(map, Time(0, 8, 35, 0), 2767, 12499);
	//Routine* routine3 = new Routine(map, Time(0, 15, 45, 0), 12499, 0);
	//Routine* routine4 = new Routine(map, Time(0, 8, 35, 0), 0, 110);
	//Routine* routine5 = new Routine(map, Time(0, 15, 45, 0), 110, 0);

	// we map to finish time then we can use map::lower_bound to get closest?
	// mon to at - same routines
	short startLocation = _homeNode;//rand() % (MAP_SIZE);
	short endLocation = map->GetNonBlockedPointRand();//rand() % (MAP_SIZE);
	if (startLocation == endLocation)
	{
		bool stop = true;
	}
	//int* weeks;//
	std::vector<std::map<float, Routine*>*> days;
	days.push_back(&_routinesWeekly.at(0));
	days.push_back(&_routinesWeekly.at(1));
	days.push_back(&_routinesWeekly.at(2));
	days.push_back(&_routinesWeekly.at(3));
	days.push_back(&_routinesWeekly.at(4));
	days.push_back(&_routinesWeekly.at(5));

	AddRandomRoutine(map, days, startLocation, endLocation);
}

int NPC::GetLocation(UWorldTime &t)
{
	int position = _homeNode;
	float daysPassed = t.GetWorldTime() / SECONDS_PER_DAY;
	int dayIndex = (int(daysPassed)) % DAYS_PER_WEEK;
	std::map<float, Routine*> routine = _routinesWeekly.at(dayIndex);
	if (routine.size() == 0)
		return position;

	float sec = t.GetDate().GetTime().GetTimeSeconds();
	std::map<float, Routine*>::iterator it;
	it = routine.lower_bound(sec);
	it--;

	// if we only have one routine and we 
	//if (it == routine.end())
	//	it++;
	// we should now have current or last routine (start time)
	if (it != routine.end())
	{
		// we have routine
		if (it->second->_nodes.size())
		{
			// routine has nodes
			//agk::Print(it->first);
			// how many seconds after our start time?
			int diff = sec - it->first;
			if (diff < 0)
				diff = 0;
			if (diff >= it->second->_nodes.size())
				diff = it->second->_nodes.size() - 1;
			position = (int)it->second->_nodes.at(diff);
		}
	}
	return position;
}

