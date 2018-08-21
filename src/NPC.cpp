#include "NPC.h"

Routine::Routine(Map* map, Time startTime, const int startNodeIndex, const int endNodeIndex) : _startTime(startTime)
{
	map;
	_nodes = map->GetPath(startNodeIndex, endNodeIndex, &_cost);
}

Routine::~Routine()
{

}

NPC::NPC()
{
	for (int i = 0; i < DAYS_PER_WEEK; i++)
	{
		_routinesWeekly.push_back(std::map<float, Routine*>());
	}
}

NPC::~NPC()
{
	// empty routines

}

void NPC::PopulateRoutines(Map* map)
{
	Routine* routine1 = new Routine(map, Time(0, 0, 2, 0), 0, 2767);
	Routine* routine2 = new Routine(map, Time(0, 8, 35, 0), 2767, 12499);
	Routine* routine3 = new Routine(map, Time(0, 15, 45, 0), 12499, 0);

	Routine* routine4 = new Routine(map, Time(0, 8, 35, 0), 0, 110);
	Routine* routine5 = new Routine(map, Time(0, 15, 45, 0), 110, 0);

	// we map to finish time then we can use map::lower_bound to get closest?
	// mon to at - same routines
	for (int i = 0; i < 6; i++)
	{
		std::map<float, Routine*>* day = &_routinesWeekly.at(i);
		day->insert(std::pair<float, Routine*>(routine1->_startTime.GetTimeSeconds(), routine1));
		day->insert(std::pair<float, Routine*>(routine2->_startTime.GetTimeSeconds(), routine2));
		day->insert(std::pair<float, Routine*>(routine3->_startTime.GetTimeSeconds(), routine3));
	}
	// goes to church on sunday :)
	std::map<float, Routine*>* day = &_routinesWeekly.at(6);
	day->insert(std::pair<float, Routine*>(routine4->_startTime.GetTimeSeconds(), routine4));
	day->insert(std::pair<float, Routine*>(routine5->_startTime.GetTimeSeconds(), routine5));
}

//#include "agk.h""
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
			position = (intptr_t)it->second->_nodes.at(diff);
            //position = (int)it->second->_nodes.at(diff);
		}
	}
	return position;
}

