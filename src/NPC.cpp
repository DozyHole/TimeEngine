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
}

NPC::~NPC()
{

}

void NPC::PopulateRoutines(Map* map)
{
	Routine* routine1 = new Routine(map, Time(0, 0, 2, 0), 0, 2767);
	Routine* routine2 = new Routine(map, Time(0, 8, 35, 0), 2767, 12499);
	Routine* routine3 = new Routine(map, Time(0, 15, 45, 0), 12499, 0);

	// we map to finish time then we can use map::lower_bound to get closest?
	_routinesWeekly[routine1->_startTime.GetTimeSeconds()] = routine1;
	_routinesWeekly[routine2->_startTime.GetTimeSeconds()] = routine2;
	_routinesWeekly[routine3->_startTime.GetTimeSeconds()] = routine3;
}

//#include "agk.h""
int NPC::GetLocation(UWorldTime &t)
{
	int position = _homeNode;
	float sec = t.GetDate().GetTime().GetTimeSeconds();
	std::map<float, Routine*>::iterator it;
	it = _routinesWeekly.lower_bound(sec);
	it--;
	// we should now have current or last routine (start time)
	if (it != _routinesWeekly.end())
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

