typedef struct {
	Resort resort;
	Route route;
	int * (*find_path)();	
} Astar;



int * find_path(Astar * self)
{
	
	int *route_suggestion = malloc(29 * sizeof(*route_suggestion));
	route_suggestion[0] = 2;
	route_suggestion[1] = 3;
	route_suggestion[2] = 4;

	return route_suggestion;
}

void init_Astar(Astar * me, Resort * resort, Route * route); 	
