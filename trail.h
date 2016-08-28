typedef struct {
	int id;
	int diff;
	int weight;
	Waypoint top;
	Waypoint bot;
} Trail;


void init_Trail(Trail * me, int id, int diff, int weight, Waypoint * top, Waypoint * bot);
