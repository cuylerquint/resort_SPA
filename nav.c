#include <stdio.h>
#include <stdlib.h>
#include "waypoint.h"
#include "trail.h"
#include "chair.h"
#include "resort.h"
#include "route_request.h"
#include "Astar.h"


void write_to_suggested_dat(FILE * fo, Trail * trail);



void init_Astar(Astar * this, Resort * resort , Route * route)
{
	this->resort = *resort;
	this->route = *route;
}

void init_Route(Route * this, Waypoint * waypoints, int input_data[])
{
	
	for(int i = 0; i < 20;i++)
	{
		if(waypoints[i].id == input_data[0])
			this->start = waypoints[i];
		if(waypoints[i].id == input_data[1])
			this->finish = waypoints[i];
	}
	this->preference = input_data[2];
}

void init_Waypoint(Waypoint * me,int id, int x, int y, int z, int weight)
{
	me->id = id;
	me->x = x;
	me->y = y;
	me->z = z;
	me->weight = weight;
}

void init_Trail(Trail * this, int id ,int diff, int top_waypoint_id, int bot_waypoint_id, Waypoint * waypoints)
{

	this->id = id;
	this->diff = diff;
	for(int i = 0; i < 20;i++)
	{
		if(waypoints[i].id == top_waypoint_id)
			this->top = waypoints[i];
		if(waypoints[i].id == bot_waypoint_id)
			this->bot = waypoints[i];
	}
	this->set_weight = &set_weight;
	this->weight = this->set_weight(this);
}

void init_Chair(Chair * this, int id ,int weight, Waypoint * top, Waypoint * bot)
{
	this->id = id;
	this->top = *top;
	this->bot = *bot;
	this->weight = weight;
}

void init_Resort(Resort * this, Waypoint * waypoints, Chair * chairs, Trail * trails)
{
	this->waypoints = waypoints;
	this->chairs = chairs;
	this->trails = trails;
}

void make_default_waypoints(Waypoint * waypoints)
{
	init_Waypoint(&waypoints[0],1,0,500,0,0);
	init_Waypoint(&waypoints[1],2,0,400,100,0);
	init_Waypoint(&waypoints[2],3,100,400,100,0);
	init_Waypoint(&waypoints[3],4,100,400,0,0);
	init_Waypoint(&waypoints[4],5,0,300,200,0);
	init_Waypoint(&waypoints[5],6,200,300,200,0);
	init_Waypoint(&waypoints[6],7,200,300,0,0);
	init_Waypoint(&waypoints[7],8,0,200,300,0);
	init_Waypoint(&waypoints[8],9,300,200,300,0);
	init_Waypoint(&waypoints[9],10,300,200,0,0);
	init_Waypoint(&waypoints[10],11,0,100,400,0);
	init_Waypoint(&waypoints[11],12,400,100,400,0);
	init_Waypoint(&waypoints[12],13,400,100,0,0);
	init_Waypoint(&waypoints[13],14,0,0,500,0);
	init_Waypoint(&waypoints[14],15,250,0,500,0);
	init_Waypoint(&waypoints[15],16,500,0,500,0);
	init_Waypoint(&waypoints[16],17,500,0,250,0);
	init_Waypoint(&waypoints[17],18,500,0,0,0);
	init_Waypoint(&waypoints[18],19,175,100,250,0);
	init_Waypoint(&waypoints[19],20,250,500,175,0);	
}

void make_default_trails(Trail * trails, Waypoint * waypoints)
{
	//green list,id,diff,top_id,bot_id
	init_Trail(&trails[0],1,1,1,5,waypoints);
	init_Trail(&trails[1],2,1,5,8,waypoints);
	init_Trail(&trails[2],3,1,8,11,waypoints);
	init_Trail(&trails[3],4,1,11,14,waypoints);
	init_Trail(&trails[4],5,1,8,12,waypoints);
	init_Trail(&trails[5],6,1,11,15,waypoints);
	init_Trail(&trails[6],7,1,7,20,waypoints);
	init_Trail(&trails[7],8,1,20,16,waypoints);
	init_Trail(&trails[8],9,1,20,17,waypoints);

	//blue list,id,diff,top_id,bot_id
	init_Trail(&trails[9],10,2,1,3,waypoints);
	init_Trail(&trails[10],11,2,3,8,waypoints);
	init_Trail(&trails[11],12,2,3,6,waypoints);
	init_Trail(&trails[12],13,2,3,10,waypoints);
	init_Trail(&trails[13],14,2,19,14,waypoints);
	init_Trail(&trails[14],15,2,6,19,waypoints);
	init_Trail(&trails[15],16,2,6,9,waypoints);
	init_Trail(&trails[16],17,2,6,20,waypoints);
	init_Trail(&trails[17],18,2,20,18,waypoints);
	init_Trail(&trails[18],19,2,9,12,waypoints);
	init_Trail(&trails[19],20,2,12,16,waypoints);

	//black
	init_Trail(&trails[20],21,3,1,7,waypoints);
	init_Trail(&trails[21],22,3,7,10,waypoints);
	init_Trail(&trails[22],23,3,10,13,waypoints);
	init_Trail(&trails[23],24,3,13,18,waypoints);
	init_Trail(&trails[24],25,3,10,12,waypoints);
	init_Trail(&trails[25],26,3,13,17,waypoints);
	init_Trail(&trails[26],27,3,5,19,waypoints);
	init_Trail(&trails[27],28,3,19,16,waypoints);
	init_Trail(&trails[28],29,3,19,15,waypoints);
	
	printf("test:%d",trails[0].id);
}


void make_default_chairs(Chair * chairs, Waypoint * waypoints)
{
	init_Chair(&chairs[0],1,7,&waypoints[4],&waypoints[14]);
	init_Chair(&chairs[1],2,3,&waypoints[1],&waypoints[11]);
	init_Chair(&chairs[2],3,9,&waypoints[2],&waypoints[13]);
	init_Chair(&chairs[3],4,9,&waypoints[2],&waypoints[17]);
	init_Chair(&chairs[4],5,3,&waypoints[5],&waypoints[15]);
	init_Chair(&chairs[5],6,6,&waypoints[0],&waypoints[18]);
	init_Chair(&chairs[6],7,6,&waypoints[0],&waypoints[19]);
	init_Chair(&chairs[7],8,3,&waypoints[3],&waypoints[11]);
	init_Chair(&chairs[8],9,7,&waypoints[6],&waypoints[16]);
}

void get_input_data(int * input_data)
{
	int starting_location = 0, desired_location = 0,preference = 0;
	printf("Starting Locataion Point:");
	scanf("%d",&starting_location);
	printf("Desired Location Point:");
	scanf("%d",&desired_location);
	printf("\n1-Easy(Green)\n2-Medium(Blue)\n3-Hard(Black)\nSkill Preference:");
	scanf("%d",&preference);
	input_data[0] = starting_location;
	input_data[1] = desired_location;
	input_data[2] = preference;
	
}

void display_suggestion(int suggested_route[], Resort * resort)
{
	//from a list of trail ids, write those trail cooridnates for gnuplot to plot yellow lines for a placement
	// get trail from resort 
	// first index is giving address for resort->trails odd reason?! firgure out 
	FILE *fo;	
	fo = fopen("suggested.dat", "w+");	
	for(int i = 0; i < 29; i++){
		for(int j = 0;j < 29;j++){
			if(suggested_route[i] == resort->trails[j].id)
			{
				write_to_suggested_dat(fo,&resort->trails[j]);
				printf("\nR trail id: %d, suggested: %d",resort->trails[j].id, suggested_route[i]);
			}
		}
	}

	fclose(fo);
	system("killall gnuplot_qt");
	system("gnuplot routed_resort.gp -p");

}


void write_to_suggested_dat(FILE *fo,Trail * trail)
{
	
	fprintf(fo, "%d\t%d\t%d",trail->top.x,trail->top.y,trail->top.z);
	fprintf(fo, "\n%d\t%d\t%d\n\n",trail->bot.x,trail->bot.y,trail->bot.z);
	printf("\ntopWid: %d topx : %d topy: %d topz: %d",trail->top.id,trail->top.x,trail->top.y,trail->top.z);
	printf("\nbotWid: %d botx : %d boty: %d botz: %d",trail->bot.id,trail->bot.x,trail->bot.y,trail->bot.z);

}




int setup()
{
	Waypoint waypoints[20];
	Trail **trails = malloc(29 * sizeof(Trail*));
	Resort *resort = malloc(sizeof(Resort*));
	for(int i = 0 ; i < 29;i++)
		trails[i] =  malloc(sizeof(Trail));
	Chair chairs[10];
	Route *route = malloc(sizeof(Route));
	Astar *astar = malloc(sizeof(Astar));
	make_default_waypoints(waypoints);
	make_default_trails(*trails,waypoints);
	make_default_chairs(chairs,waypoints);
	init_Resort(resort,waypoints,chairs,*trails);
//	display_default_plot();
	system("gnuplot resort.gp -p");
	int input_data[3];
	get_input_data(input_data);
	init_Route(route,waypoints,input_data);
	init_Astar(astar,resort,route);
	int route_suggestion[29];
	route_suggestion[0] = 3;
	route_suggestion[1] = 2;
	display_suggestion(route_suggestion, resort);

	return(1);	
}

int main(void)
{
	setup();
	return(1);
}



