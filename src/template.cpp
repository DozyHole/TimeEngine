// Includes
#include "template.h"
#include "src/WorldTime.h"
#include "src/Map.h"
#include "src/NPC.h"

// Namespace
using namespace AGK;

app App;

UWorldTime t;
Map map;
NPC npc0;


void app::Begin(void)
{
	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	npc0.PopulateRoutines(&map);
	
}

int app::Loop (void)
{
	t.Tick(agk::GetFrameTime());
	agk::Print(t.GetDateString().c_str());
	agk::Print(t.GetTimeString().c_str());
	if (agk::GetRawKeyPressed(39))
	{
		t.FastForward();
	}
	if (agk::GetRawKeyPressed(37))
	{
		t.Rewind();
	}
	map.DrawNodes();

	// test pathfinder
	//float costOut;
	//std::vector<void*> path = map.GetPath(9874, 0, &costOut);
	//for (auto &p : path)
	//{
		//int index = (int)p;
		//Point point = map.GetPosition(index);
		//int colour = 0 | 255 << 8 | 0 << 16 | 255 << 24;
		//agk::DrawEllipse(point._x, point._y, 4, 4, colour, colour, 1);
	//}

	int pos = npc0.GetLocation(t);
	Point p = map.GetPosition(pos);
	
	int colour = 255 | 255 << 8 | 255 << 16 | 255 << 24;
	agk::DrawEllipse(p._x, p._y, 4, 4, colour, colour, 1);
	agk::Print(agk::ScreenFPS());
	agk::Sync();
	return 0; // return 1 to close app
}


void app::End (void)
{

}
