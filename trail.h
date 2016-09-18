#include <math.h>
typedef struct {
	int id;
	int diff;
	int weight;
	Waypoint top;
	Waypoint bot;
	int (*set_weight)();
} Trail;

int set_weight(Trail * self)
{
	printf("\nTopx: %d  Topy: %d Topz: %d", self->top.x, self->top.y, self->top.z);
	printf("\nBotx: %d  Boty: %d Botz: %d", self->bot.x, self->bot.y, self->bot.z);



	int delta_x,delta_y, delta_z;
	double  weight;
	delta_x = (self->bot.x - self->top.x);
	printf("\nfirst x: %d ", delta_x); 
	delta_y = (self->bot.y - self->top.y);
	printf("\nfirst y: %d ", delta_y); 
	delta_z = (self->bot.z - self->top.z);
	printf("\nfirst z: %d ", delta_z); 
	delta_x = abs(delta_x)*abs(delta_x);delta_y = abs(delta_y)*abs(delta_y);delta_z = abs(delta_z)*abs(delta_z);
	printf("\n s x: %d ", delta_x); 
	printf("\n s y: %d ", delta_y); 
	printf("\n s z: %d ", delta_z); 
	weight = abs(delta_x) + abs(delta_y) + abs(delta_z);
	weight = sqrt(weight);
	if(self->diff == 1)
		weight = weight + (weight * .3);
	else if (self->diff == 2)
		weight = weight + (weight * .2);
	else
		weight = weight + (weight * .1);
	printf("\nset_weight return:%f\n",weight);
	return(weight);
	
}


void init_Trail(Trail * me, int id, int diff, Waypoint * top, Waypoint * bot);
