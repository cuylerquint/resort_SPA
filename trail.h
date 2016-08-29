typedef struct {
	int id;
	int diff;
	int weight;
	Waypoint top;
	Waypoint bot;
	struct Trail* (*set_weight) (struct Trail*);
} Trail;

struct Trail* Trail_set_weight(struct* me)
{
	printf("id:%d",me->id);
}


void init_Trail(Trail * me, int id, int diff, Waypoint * top, Waypoint * bot);
