typedef struct{
	Waypoint start;
	Waypoint finish;
	int preference;
} Route;


void init_Route(Route * me, Waypoint * waypoints, int input_data[]);


