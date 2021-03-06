typedef struct {
	Resort resort;
	Route route;
} Astar;

// used linked list for open and closed_list

typedef struct {
	Waypoint waypoint;
	int f, g, path_weight;
} astar_node;



void init_Astar(Astar * me, Resort * resort, Route * route); 	
