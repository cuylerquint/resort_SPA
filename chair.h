typedef struct{
	int id;
	int weight;
	Waypoint top;
	Waypoint bot;
	int (*set_chair_weight)();
} Chair;

int set_chair_weight(Chair * self)
{
	int delta_x,delta_y, delta_z;
	double  weight;
	delta_x = (self->bot.x - self->top.x);
	delta_y = (self->bot.y - self->top.y);
	delta_z = (self->bot.z - self->top.z);
	delta_x = abs(delta_x)*abs(delta_x);delta_y = abs(delta_y)*abs(delta_y);delta_z = abs(delta_z)*abs(delta_z);
	weight = abs(delta_x) + abs(delta_y) + abs(delta_z);
	weight = sqrt(weight);
	return weight;
	
}

void init_Chair(Chair * me, int id, int weight, Waypoint * top , Waypoint * bot);
