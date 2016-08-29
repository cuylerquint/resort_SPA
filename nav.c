#include <stdio.h>
#include "waypoint.h"
#include "trail.h"
#include "chair.h"

void init_Waypoint(Waypoint * me,int id, int x, int y, int z, int weight){
	me->id = id;
	me->x = x;
	me->y = y;
	me->z = z;
	me->weight = weight;
}

void init_Trail(Trail * this, int id ,int diff, Waypoint * top, Waypoint * bot){
	this->id = id;
	this->diff = diff;
	this->top = *top;
	this->bot = *bot;
	this->weight = this->set_weight();
}
void init_Chair(Chair * this, int id ,int weight, Waypoint * top, Waypoint * bot){
	this->id = id;
	this->top = *top;
	this->bot = *bot;
	this->weight = weight;
}

void make_default_waypoints(Waypoint * waypoints){
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

void make_default_trails(Trial * trails, Waypoint * waypoints){
	init_Trail(&trials[0],1,1,


}


void make_default_chairs(Chair * chairs, Waypoint * waypoints){
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

void get_input_data(int * input_data){
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
void setup_route(Waypoint * waypoints,int input_data[]){
	int bound = sizeof(waypoints[0]);
	printf("bound:%d",bound);
	for(int i = 0; waypoints[i].id; i++){
		printf("\n%d",waypoints[i].id);
	}
}
int setup(){
	Waypoint waypoints[20];
	Trail trails[29];
	Chair chairs[10];
	make_default_waypoints(waypoints);
	make_defualt_trails(trails,waypoints);
	make_default_chairs(chairs,waypoints);
//	init_resort();
//	display_default_plot();
	int input_data[3];
	get_input_data(input_data);
	setup_route(waypoints,input_data);
	return(1);	
}

int main(void){
	setup();
	return(1);
}



