typedef struct{
	int id;
	int weight;
	Waypoint top;
	Waypoint bot;
} Chair;


void init_Chair(Chair * me, int id, int weight, Waypoint * top , Waypoint * bot);
