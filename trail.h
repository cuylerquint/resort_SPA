typedef struct {
	int id;
	int diff;
	int weight;
	Waypoint top;
	Waypoint bot;
	int (*set_weight)();
} Trail;

int *set_weight(Trail * self)
{
	printf("id:%d",self->id);
	return(&self->id);
}


void init_Trail(Trail * me, int id, int diff, Waypoint * top, Waypoint * bot);
