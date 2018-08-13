#include "NPC.h"

Routine::Routine(Time startTime, Time finishTime) : _startTime(startTime), _finishTime(finishTime)
{
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
	Routine* routine1 = new Routine(Time(0, 0, 10, 0), Time(0, 5, 25, 0));
	Routine* routine2 = new Routine(Time(0, 5, 35, 0), Time(0, 9, 45, 0));
	Routine* routine3 = new Routine(Time(0, 23, 25, 0), Time(0, 25, 15, 0));
	//Routine* routine4 = new Routine(Time(0, 30, 0, 0), Time(0, 30, 10, 0));

	//std::vector<void*> p1 = map->GetPath(0, 4);
	//std::vector<int> v1 = static_cast<std::vector<int> >(p1);

	//std::vector<int> p1Int(p1.begin(), p1.end());
	routine1->_nodes = map->GetPath(0, 2767);
	routine2->_nodes = map->GetPath(2767, 9874);
	routine3->_nodes = map->GetPath(9874, 0);

	//routine2->_nodes = { 4, 5, 6, 7, 8 };
	//routine3->_nodes = { 8, 18, 28, 38, 48, 58, 68, 69, 79, 89, 99 };
	//routine4->_nodes = { 88, 77, 66, 55, 44, 33, 22, 11, 0 };

	// we map to finish time then we can use map::lower_bound to get closest?
	_routinesWeekly[routine1->_startTime.GetTimeSeconds()] = routine1;
	_routinesWeekly[routine2->_startTime.GetTimeSeconds()] = routine2;
	_routinesWeekly[routine3->_startTime.GetTimeSeconds()] = routine3;
//	_routinesWeekly[routine4->_startTime.GetTimeSeconds()] = routine4;
}

#include "agk.h""
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
			agk::Print(it->first);
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

