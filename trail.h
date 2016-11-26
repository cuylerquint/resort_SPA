#include <math.h>
typedef struct {
	int id;
	int diff;
	int weight;
	Waypoint top;
	Waypoint bot;
	int (*set_trail_weight)();
} Trail;

int set_trail_weight(Trail * self)
{
	int delta_x,delta_y, delta_z;
	double  weight;
	delta_x = (self->bot.x - self->top.x);
	delta_y = (self->bot.y - self->top.y);
	delta_z = (self->bot.z - self->top.z);
	delta_x = abs(delta_x)*abs(delta_x);delta_y = abs(delta_y)*abs(delta_y);delta_z = abs(delta_z)*abs(delta_z);
	weight = abs(delta_x) + abs(delta_y) + abs(delta_z);
	weight = sqrt(weight);
	if(self->diff == 1)
		weight = weight + (weight * .3);
	else if (self->diff == 2)
		weight = weight + (weight * .2);
	else
		weight = weight + (weight * .1);
	return weight;
	
}


void init_Trail(Trail * this, int id ,int diff, int top_waypoint_id, int bot_waypoint_id, Waypoint * waypoints);
