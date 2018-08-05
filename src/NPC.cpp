#include "NPC.h"

Routine::Routine(Time startTime, Time finishTime) : _startTime(startTime), _finishTime(finishTime)
{
	//_nodes.push_back(0);
	//_nodes.push_back(10);
	//_nodes.push_back(11);
	//_nodes.push_back(12);
}

Routine::~Routine()
{

}

NPC::NPC()
{
	//_homeNode = 0;
	//Routine* routine1 = new Routine(Date(0, 1, 0), Date(0, 1, 10));
	//_routines.push_back(routine1);
}

NPC::~NPC()
{

}

void NPC::PopulateRoutines()
{
	Routine* routine1 = new Routine(Time(0, 0, 10, 0), Time(0, 0, 25, 0));
	Routine* routine2 = new Routine(Time(0, 0, 35, 0), Time(0, 0, 45, 0));
	Routine* routine3 = new Routine(Time(0, 1, 8, 0), Time(0, 1, 15, 0));
	Routine* routine4 = new Routine(Time(0, 30, 0, 0), Time(0, 30, 10, 0));

	routine1->_nodes = { 0, 1, 2, 3, 4 };
	routine2->_nodes = { 4, 5, 6, 7, 8};
	routine3->_nodes = { 8, 18, 28, 38, 48, 58, 68, 69, 79, 89, 99 };
	routine4->_nodes = { 88, 77, 66, 55, 44, 33, 22, 11, 0};

	// we map to finish time then we can use map::lower_bound to get closest?
	_routinesWeekly[routine1->_startTime.GetTimeSeconds()] = routine1;
	_routinesWeekly[routine2->_startTime.GetTimeSeconds()] = routine2;
	_routinesWeekly[routine3->_startTime.GetTimeSeconds()] = routine3;
	_routinesWeekly[routine4->_startTime.GetTimeSeconds()] = routine4;
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
			position = it->second->_nodes.at(diff);
		}
	}
	return position;
}

