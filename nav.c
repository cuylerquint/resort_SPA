#include <stdio.h>
#include <stdlib.h>
#include "waypoint.h"
#include "trail.h"
#include "chair.h"
#include "resort.h"
#include "route_request.h"
#include "Astar.h"
#include "linked_list.h"
#include "path.h"
#include "tree.h"



int get_path_weight(Astar * self,linked_node * path);
int get_trail_or_chair_weight(Astar * self,int prev_id,int next_id);
void get_shortest(Astar * self, parent_point * parent_head);
void write_to_suggested_dat(FILE * st,FILE * sw, Trail * trail, int i);
int listLength(linked_node* item);
void display_list(linked_node * head);
linked_node * update_neighbor(Astar * self,linked_node ** open,linked_node ** current_neighbors, int g);
void update_open(linked_node ** open, linked_node ** current_neighbor);
void add_parent(parent_point **head, Waypoint  point);
void add_child(parent_point *head, Waypoint point);
int parents_path_len(parent_point * item);
int connects_to_branch(Astar * self,parent_point cur_parent, Waypoint new_point);


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
	this->set_trail_weight = &set_trail_weight;
	this->weight = this->set_trail_weight(this);
}

void init_Chair(Chair * this, int id ,int weight, Waypoint * top, Waypoint * bot)
{
	this->id = id;
	this->top = *top;
	this->bot = *bot;
	this->set_chair_weight = &set_chair_weight;
	this->weight = this->set_chair_weight(this);
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
	init_Waypoint(&waypoints[19],20,350,100,175,0);	
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
	
//	printf("test:%d",trails[0].id);
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

void display_suggestion(Astar * self,int suggested_route[], int size)
//need to firgure out how to combine with displaying chairs as well
{
	FILE *st,*sw;	
	st = fopen("suggested_trails.dat", "w+");	
	sw = fopen("suggested_waypoints.dat", "w+");	
	int stop_count = 1;
	for(int i = 0 ; i < size;i++)
	{
		printf("\nR id: %d, R + 1: %d",suggested_route[i],suggested_route[i+1]);
		for(int j = 0; j < 10;j++)
		{
			if(self->resort.chairs[j].bot.id == suggested_route[i] && self->resort.chairs[j].top.id == suggested_route[i + 1])
			{
				fprintf(sw, "%d\t%d\t%d\t%d\n\n",self->resort.chairs[j].bot.x,self->resort.chairs[j].bot.y,self->resort.chairs[j].bot.z,stop_count);
				fprintf(st, "\n\n%d\t%d\t%d",self->resort.chairs[j].bot.x,self->resort.chairs[j].bot.y,self->resort.chairs[j].bot.z);
				fprintf(st, "\n%d\t%d\t%d",self->resort.chairs[j].top.x,self->resort.chairs[j].top.y,self->resort.chairs[j].top.z);
			}	
		}

		for(int j = 0; j < 29;j++)
		{
			if(self->resort.trails[j].top.id == suggested_route[i] && self->resort.trails[j].bot.id == suggested_route[i + 1])
			{	
				fprintf(sw, "%d\t%d\t%d\t%d\n\n",self->resort.trails[j].top.x,self->resort.trails[j].top.y,self->resort.trails[j].top.z,stop_count);
				fprintf(st, "\n\n%d\t%d\t%d",self->resort.trails[j].top.x,self->resort.trails[j].top.y,self->resort.trails[j].top.z);
				fprintf(st, "\n%d\t%d\t%d",self->resort.trails[j].bot.x,self->resort.trails[j].bot.y,self->resort.trails[j].bot.z);
			}
		}
		stop_count++;
	}
	fprintf(sw, "%d\t%d\t%d\t%d\n\n",self->route.finish.x,self->route.finish.y,self->route.finish.z,--stop_count);
	fclose(st);
	fclose(sw);
	system("killall gnuplot_qt");
	system("gnuplot routed_resort.gp -p");
}

int list_len(linked_node* item)
{
  	linked_node* cur = item;
  	int size = 0;

  	while (cur != NULL)
  	{
  		++size;
    		cur = cur->next;
  	}
  	return size;
}

void list_append(linked_node** head, astar_node data)
{
	linked_node * new = (linked_node *) malloc(sizeof(linked_node));
	linked_node *last = *head;  /* used in step 5*/
        new->data  = data;
        new->next = NULL;
        if (*head == NULL)
        {
       		*head = new;
       		return;
        }  
        while (last->next != NULL)
        	last = last->next;
        last->next = new;
        return;    
}

void list_insert(linked_node ** head, astar_node * data)
{
	linked_node * insert = (linked_node *) malloc(sizeof(linked_node));
	insert->data = *data;
	if(*head == NULL)
	{
		*head = insert;
		insert->next = NULL;
	}
	else if((*head)->data.f > data->f)
	{
		insert->next = *head;
		*head = insert;
	}	
	else
	{
		//printf("Inserting %d into : ",data->waypoint.id);
		//display_list(*head);
		linked_node * temp, *prev;
		temp = *head;
		while(temp != NULL && temp->data.f <= data->f)
		{	
			prev = temp;
			temp = temp->next;
		}
		insert->next = temp;
		prev->next = insert;	
	}
	//printf("\n Result:");
	//display_list(*head);
}

void list_remove_head(linked_node ** head)
{
	if((*head)->next == NULL)
		*head = NULL; // temp fix for deleteing head	
	else
		(*head) = (*head)->next;

}	

void display_list(linked_node * head)
{
	linked_node * temp = head;
	printf("\nList: ");
	while(temp != NULL)
	{
		printf("ID:%d g:%d f:%d->",temp->data.waypoint.id,temp->data.g,temp->data.f);
		temp = temp->next;
	}
	printf("NULL\n\n");
}


astar_node * get_lowest_f(linked_node * node)
{
	
//	printf("\nopen:");
//	display_list(node);
	linked_node * smallest = node;  
	while( node != NULL) {
  		if( node->data.f < smallest->data.f ) {
       			smallest = node;
  		}
  		node = node->next;
	}
	return &smallest->data;
}

int h_cost( Waypoint * cur, Waypoint * goal)
{

 //	printf("\nTopx: %d  Topy: %d Topz: %d", cur->x, cur->y, cur->z);
 //	printf("\nBotx: %d  Boty: %d Botz: %d", goal->x, goal->y, goal->z);
 
 	int delta_x,delta_y, delta_z;
 	double  weight;
 	delta_x = (cur->x - goal->x);
 	delta_y = (cur->y - goal->y);
 	delta_z = (cur->z - goal->z);
 	delta_x = abs(delta_x)*abs(delta_x);delta_y = abs(delta_y)*abs(delta_y);delta_z = abs(delta_z)*abs(delta_z);
 	weight = abs(delta_x) + abs(delta_y) + abs(delta_z);
 	weight = sqrt(weight);
	return(weight);	
}

int equal_waypoints(Waypoint current, Waypoint finish)
{
	return(current.x == finish.x && current.y == finish.y && current.z == finish.z);

}

void set_temp_neighbors(Astar * self, linked_node ** temp_neighbors, astar_node * current)
{
	//loop all chairs with bot as current waypoint and add chair i top to temp neighbors
	//loop all trails with top as current waypoint with a skill prefeecne then trail bot to list
	//printf("\ncurrent waypoint : %d %d %d",current->waypoint.x,current->waypoint.y,current->waypoint.z);
	for(int i = 0; i < 10;i++)
	{
		//printf("\nchair index : %d %d %d",self->resort.chairs[i].bot.x,self->resort.chairs[i].bot.y,self->resort.chairs[i].bot.z);
		if(equal_waypoints(self->resort.chairs[i].bot,current->waypoint))
		{
			//add a chairs to neighbors
			printf("\nsetting chair path weight to %d",self->resort.chairs[i].weight);
			astar_node * temp_chair = malloc(sizeof(astar_node));	
			temp_chair->waypoint = self->resort.chairs[i].top;
			temp_chair->path_weight = self->resort.chairs[i].weight;
			temp_chair->g = 999999; // default
			printf("\ninserting chair top waypoint: %d",self->resort.chairs[i].top.id);	
			list_insert(temp_neighbors,temp_chair);	
		}	
	}

	for(int i = 0; i < 29;i++)
	{
	//	printf("\ntrail index : %d %d %d",self->resort.trails[i].top.x,self->resort.trails[i].top.y,self->resort.trails[i].top.z);
		if(equal_waypoints(self->resort.trails[i].top,current->waypoint))
		{
			//add a trials to neighbors with pref
			if(self->resort.trails[i].diff <= self->route.preference)
			{
				printf("\nsetting trail path weight to %d",self->resort.trails[i].weight);
				astar_node * temp_trail = malloc(sizeof(astar_node));
				temp_trail->waypoint = self->resort.trails[i].bot;
				temp_trail->path_weight = self->resort.trails[i].weight;
				temp_trail->g = 999999; // default
				printf("\ninserting trail bot waypoint: %d",self->resort.trails[i].bot.id);	
				list_insert(temp_neighbors,temp_trail);
			}
		}	
	}
}



int in_list(linked_node * head, astar_node * current_neighbor)
{
	linked_node * temp = head;
    	while (temp != NULL)
    	{
        	if (temp->data.waypoint.id == current_neighbor->waypoint.id)
        	{
            		printf("key found\n");
            		return 1;
        	}
        	temp = temp->next;
    	}
	return 0;
}

int parents_path_len(parent_point * item)
{
  	parent_point * cur = item;
  	int size = 0;

  	while (cur != NULL)
  	{
  		++size;
    		cur = cur->next;
  	}
  	return size;
}
	 

void path_dump(parent_point * cur_parent)
{
	while(cur_parent != NULL)
	{
		printf("\nBranch Start :%d",cur_parent->point.id);
		child_point * cur_child = cur_parent->path_head;
		if(cur_child == NULL)
		{
			printf("\n\tend");	
		}
		else
		{
			printf("\nsteps:");
			while(cur_child != NULL)
			{
				printf("\n\t->%d",cur_child->point.id);
				cur_child = cur_child->next;
			}
		}
		cur_parent = cur_parent->next;
	}
}
void add_parent(parent_point **head, Waypoint point) 
{
    // Insert new item at start.
	parent_point *new =(parent_point*) malloc(sizeof (*new));
	new->point = point;
	new->next = *head;
    	*head = new;
}

void add_child(parent_point *head, Waypoint point) 
{
    // Insert at start of list.

	child_point *new =(child_point*) malloc(sizeof (*new));
	new->point = point;
    	new->next = head->path_head;
    	head->path_head = new;
}

int adjacent_points(Astar * self ,Waypoint x, Waypoint y)
{
//	printf("\nID:%d x:%d y:%d z:%d",x.id,x.x,x.y,x.z);
//	printf("\nID:%d x:%d y:%d z:%d",y.id,y.x,y.y,y.z);
	for(int i = 0; i < 10;i++)
	{
//		printf("\n\nchair index top: %d %d %d",self->resort.chairs[i].top.x,self->resort.chairs[i].top.y,self->resort.chairs[i].top.z);
//		printf("\nchair index bot: %d %d %d",self->resort.chairs[i].bot.x,self->resort.chairs[i].bot.y,self->resort.chairs[i].bot.z);
		if(self->resort.chairs[i].bot.id == x.id && self->resort.chairs[i].top.id == y.id){
//			printf("\n\n****chair index top: %d %d %d",self->resort.chairs[i].top.x,self->resort.chairs[i].top.y,self->resort.chairs[i].top.z);
//			printf("\n****chair index bot: %d %d %d",self->resort.chairs[i].bot.x,self->resort.chairs[i].bot.y,self->resort.chairs[i].bot.z);

		
			return 1;
		}
	}

	for(int i = 0; i < 29;i++)
	{
//		printf("\n\ntrail index top: %d %d %d",self->resort.trails[i].top.x,self->resort.trails[i].top.y,self->resort.trails[i].top.z);
//		printf("\ntrail index bot: %d %d %d",self->resort.trails[i].bot.x,self->resort.trails[i].bot.y,self->resort.trails[i].bot.z);
		if(self->resort.trails[i].top.id == x.id && self->resort.trails[i].bot.id == y.id){
//			printf("\n\n****trail index top: %d %d %d",self->resort.trails[i].top.x,self->resort.trails[i].top.y,self->resort.trails[i].top.z);
///			printf("\n****trail index bot: %d %d %d",self->resort.trails[i].bot.x,self->resort.trails[i].bot.y,self->resort.trails[i].bot.z);
			return 1;
		}
	}			

	return 0;

}

int connects(Astar * self,parent_point * cur_parent, Waypoint new_point)
{
	child_point * cur_child = cur_parent->path_head;
	child_point * prev = cur_parent->path_head;
	if(cur_child == NULL)
	{
		printf("\n return based of parnet data");
		return adjacent_points(self,cur_parent->point,new_point);	
	}
	else
	{
	//	printf("\nsteps:");
	//	while(cur_child != NULL)
	//	{
	//		prev = cur_child;
	//		printf("\n\t->%d",cur_child->point.id);
	//		cur_child = cur_child->next;
	//	}
		printf("\n last child of parent :%d",prev->point.id);
		printf("\n return based of child  data");
		return adjacent_points(self,prev->point,new_point);
	}
    	printf ("\n last node of cur_parnet:%d", prev->point.id);		
	return 0;


}

int has_forward_connections(Astar * self,Waypoint current, linked_node * path)
{
	printf("\nhas forward connections");
//	if(current == NULL)
//		return 1;
	linked_node * temp = path;
	int hit_cur_child = 0;
	while(temp != NULL)
	{
		if(temp->data.waypoint.id == current.id)
			hit_cur_child = 1;
		if(hit_cur_child == 1 && adjacent_points(self,current,temp->data.waypoint))
			return 1;
		else
			temp = temp->next;
	}
	printf("\nend of has forward");
	return 0;
}

void remove_node(linked_node **head_ref, int key)
{
    	linked_node * temp = *head_ref, *prev;
    	while (temp != NULL && temp->data.waypoint.id != key)
    	{
        	prev = temp;
        	temp = temp->next;
    	}
    	if (temp == NULL) return;
    	prev->next = temp->next;
    	free(temp);
}

void remove_dead_ends(Astar * self, linked_node * path)
{
	linked_node * temp = path;
	linked_node * prev = path;
	while(temp != NULL)
	{
		printf("\ntemp ID:%d forwardC: %d",temp->data.waypoint.id, has_forward_connections(self,temp->data.waypoint,path));
		prev = temp;
		if(temp->data.waypoint.id != self->route.finish.id && has_forward_connections(self,temp->data.waypoint,path) == 0)
		{
			printf("\n removing ID: %d",temp->data.waypoint.id);
			remove_node(&path,temp->data.waypoint.id);
		}
		temp = temp->next;
	}
	printf("\nwith deadends removed");
	display_list(path);
}


void build_parent_up_to(Astar * self, parent_point * parent_head, linked_node * up_to, linked_node * path)
{
	printf("\n beginning  parent_form from build_up_to");
	path_dump(parent_head);

	linked_node * temp = path;
	linked_node * new_list = NULL;
	astar_node * start = malloc(sizeof(astar_node));
	start->waypoint = self->route.start;	
	list_append(&new_list,*start);
	while(temp != NULL)
	{
		if(temp->data.waypoint.id == up_to->data.waypoint.id)
		{
			list_append(&new_list,temp->data);
			break;
		}
		list_append(&new_list,temp->data);
		temp = temp->next;
	}

	printf("\n new_list up to limit");
	display_list(new_list);
	for(int i = 0;i < list_len(new_list);i++)
	{
		temp = new_list;	
		linked_node * prev = new_list;
		while(temp != NULL)
		{
	//		printf("\ntemp ID:%d forwardC: %d",temp->data.waypoint.id, has_forward_connections(self,temp->data.waypoint,new_list));
			prev = temp;
			if(temp->data.waypoint.id != up_to->data.waypoint.id && has_forward_connections(self,temp->data.waypoint,new_list) == 0)
			{
				printf("\n removing ID: %d from new",temp->data.waypoint.id);
				remove_node(&new_list,temp->data.waypoint.id);
			}
			temp = temp->next;
		}
	}
	
	printf("\n new_list final");
	display_list(new_list);
	temp = new_list;
	temp = temp->next;
	while(temp != NULL)
	{
		add_child(parent_head,temp->data.waypoint); 
		temp = temp->next;
	}
	printf("\n resulting parent_form from head_build");
	path_dump(parent_head);
	

}

void  show_path(Astar * self,linked_node * path)
{
	//make linked_list of linked_list
	//make first path, if temp->next does not connect to the last waypoint make new
	// top level node, 
	// ever new node traves all list to append it to right path
	// once done making all possible paths, nix ones that dont connect to des
	// then ones that do return one that has lowest cost
	printf("\npath guesses:");
	display_list(path);
	for(int i = 0;i < list_len(path);i++)
		remove_dead_ends(self,path);
	linked_node * temp = path;
	parent_point * parent_head = NULL;
	add_parent(&parent_head,self->route.start);
//	add_parent(&parent_head,temp->data.waypoint);
//	add_child(parent_head->next,temp->next->data.waypoint); 
	path_dump(parent_head);	
	while(temp != NULL)
	{
		printf("\n-----------------");
		parent_point * head_cp = parent_head;
		int cur_total_branchs = parents_path_len(head_cp);
		printf("\n Current bracnh total:%d",cur_total_branchs);
		printf("\n cur temp: %d",temp->data.waypoint.id);
		for(int i = 1; i <= cur_total_branchs;i++)
		{
			printf("\nI:%d_______________",i);
			printf("\nCur current LL:");
			path_dump(head_cp);	

			if(connects(self,head_cp,temp->data.waypoint))
			{
				printf("\n add child to cur branch");		
			
				add_child(head_cp,temp->data.waypoint); 
				head_cp = head_cp->next;
			//	continue;
			}
			else if(i == cur_total_branchs)//no connections found
			{
				printf("\n make a new parent node");					
				add_parent(&parent_head,self->route.start);
				build_parent_up_to(self,parent_head,temp,path);
			}
			else
			{
				head_cp = head_cp->next;
			}
		}
		//cannot break, mutlipe paths might reach destaion faster eg s:5 f:15
		//if(temp->data.waypoint.id == self->route.finish.id)
		//	break;
		//parent_head->next = head_cp;
		temp = temp->next;
		printf("\n resulting head_cp:");
		path_dump(head_cp);
	}
	printf("\nfinal  build");
	path_dump(parent_head);


	return get_shortest(self,parent_head);

	


}

void  get_shortest(Astar * self, parent_point * parent_head)
{
	parent_point * temp = parent_head;
	linked_node * shortest = malloc(sizeof(linked_node));;
	int low = 99999999;
	while(temp != NULL)
	{
		astar_node * start = malloc(sizeof(astar_node));
		start->waypoint = self->route.start;	
		linked_node * temp_path = NULL;
		printf("\nBranch Start");
		child_point * cur_child = temp->path_head;
		while(cur_child != NULL)
		{
			astar_node * temp_node = malloc(sizeof(astar_node));
			temp_node->waypoint = cur_child->point;	
			list_append(&temp_path,*temp_node);
			printf("\n\t->%d",cur_child->point.id);
			cur_child = cur_child->next;
		}
		list_append(&temp_path,*start);
		printf("\nnew formatted path:");
		display_list(temp_path);
		int temp_low = get_path_weight(self,temp_path);
		if(temp_low < low)
		{
			printf("\ntest");
			low = temp_low;
			printf("\ntest2");
			shortest = temp_path;
		}
		
		temp = temp->next;
	}	
	printf("\nshortest");
	display_list(shortest);
	int index = list_len(shortest), size = list_len(shortest);
	int route_suggestion[size];
	//int * route_suggestion = malloc(size_index * sizeof(*route_suggestion));
	while(shortest != NULL)
	{
		route_suggestion[index-1] = shortest->data.waypoint.id;	
		index--;
		shortest = shortest->next;
	}
	printf("\nr:%d",size);
	
	for(int i = 0; i < size; i++){
		printf("\nr:%d",route_suggestion[i]);
	}
	display_suggestion(self,route_suggestion,size);
//	route_suggestion[0] = 2;
//	route_suggestion[1] = 3;
//	route_suggestion[2] = 4;

	
}


int get_path_weight(Astar * self,linked_node * path)
{
	
	linked_node * temp = path;
	linked_node * prev = temp;
	int running = 0;
    	while (temp != NULL)
    	{
		printf("\n here");
        	prev = temp;
        	temp = temp->next;
		
		if(temp != NULL)
		{
			running += get_trail_or_chair_weight(self,prev->data.waypoint.id,temp->data.waypoint.id);
			
			printf("\n running:%d",running);
		}
		else
			break;
    	}
	
	return running;

}	

int get_trail_or_chair_weight(Astar * self,int prev_id,int next_id)
{
	for(int i = 0; i < 10;i++)
	{
//		printf("\n\nchair index top: %d %d %d",self->resort.chairs[i].top.x,self->resort.chairs[i].top.y,self->resort.chairs[i].top.z);
//		printf("\nchair index bot: %d %d %d",self->resort.chairs[i].bot.x,self->resort.chairs[i].bot.y,self->resort.chairs[i].bot.z);
		if(self->resort.chairs[i].bot.id == next_id && self->resort.chairs[i].top.id == prev_id){
//			printf("\n\n****chair index top: %d %d %d",self->resort.chairs[i].top.x,self->resort.chairs[i].top.y,self->resort.chairs[i].top.z);
//			printf("\n****chair index bot: %d %d %d",self->resort.chairs[i].bot.x,self->resort.chairs[i].bot.y,self->resort.chairs[i].bot.z);

		
			return self->resort.chairs[i].weight;
		}
	}

	for(int i = 0; i < 29;i++)
	{
//		printf("\n\ntrail index top: %d %d %d",self->resort.trails[i].top.x,self->resort.trails[i].top.y,self->resort.trails[i].top.z);
//		printf("\ntrail index bot: %d %d %d",self->resort.trails[i].bot.x,self->resort.trails[i].bot.y,self->resort.trails[i].bot.z);
		if(self->resort.trails[i].top.id == next_id && self->resort.trails[i].bot.id == prev_id){
//			printf("\n\n****trail index top: %d %d %d",self->resort.trails[i].top.x,self->resort.trails[i].top.y,self->resort.trails[i].top.z);
///			printf("\n****trail index bot: %d %d %d",self->resort.trails[i].bot.x,self->resort.trails[i].bot.y,self->resort.trails[i].bot.z);
			return self->resort.trails[i].weight;
		}
	}

	return 0;
}	
	//possible issue with wapoint 12
	//problem with waypoints 2 and 4, halfway thru a trail, does not connect

void find_path(Astar * self)
{
			
	linked_node * closed = NULL;
	linked_node * open = NULL;
	linked_node * temp_neighbors = NULL;
	linked_node * path = NULL;
	astar_node * start = malloc(sizeof(astar_node));
	
	start->waypoint = self->route.start;	
	start->f = h_cost(&start->waypoint,&self->route.finish);	
	start->g = 0;
	printf("\nopen insert start");
	list_insert(&open,start);


	printf("\nStart While");
	int branch = 1;
	while(list_len(open) != 0)
	{
		printf("\n---------Branch %d---------------",branch);  
		printf("\nfinding lowest f on open list:");
		display_list(open);  
		astar_node * current = get_lowest_f(open);	
		printf("\ncurrent lowest f:%d",current->waypoint.id);
		if(equal_waypoints(current->waypoint,self->route.finish))
		{
			//made path, reconsturt
			printf("\nFound Path");
			show_path(self,path);
			return;
		}


		//bug where lowest f is not at front of list, lowest f needs to be head for removal func	
		printf("\ninserting current into closed");
		printf("\n current to be added to close: %d",current->waypoint.id);
		list_insert(&closed,current);		
		printf("\nremoving curret from open");
		display_list(open);  
		list_remove_head(&open);
		printf("\n after removal");
		display_list(open);
	
		printf("\n current to get neightbors from: %d",current->waypoint.id);

		set_temp_neighbors(self,&temp_neighbors,current);
	
		printf("\ncurrent neihgebors:");
		display_list(temp_neighbors);


		int neighbors_len = list_len(temp_neighbors);
		printf("\nCurrent id: %d, current->g: %d",current->waypoint.id, current->g);
		for(int i = 1; i <= neighbors_len;i++)
		{
			printf("\nI:%d",i);
			if(in_list(closed,&temp_neighbors->data))
			{
				printf("\n in closed contiue");
				list_remove_head(&temp_neighbors);
				continue;
			}
			printf("\n current ->g %d +  path weight %d",current->g,temp_neighbors->data.path_weight);
			int tentative_G = (current->g + temp_neighbors->data.path_weight);
			printf("\nNeghib:%d tempG:%d",temp_neighbors->data.waypoint.id,tentative_G);
			if(in_list(open,&temp_neighbors->data) == 0)
			{
				//f gets updated after sorted insert making the lowest f not head
				printf("\ninserting temp into open");
				list_insert(&open,&temp_neighbors->data);	

			}
			else if(tentative_G >= temp_neighbors->data.g)
			{
				printf("\n not a better path continue");
				list_remove_head(&temp_neighbors);
				continue;
			}
			// make a new list, insert the new value after update, then set open to temp
			list_append(&path,temp_neighbors->data);
	//		list_remove_head(&temp_neighbors);
			linked_node * temp = update_neighbor(self,&open,&temp_neighbors,tentative_G);
			printf("\ntemp before update open list g:%d",temp->data.g);
			update_open(&open,&temp);
			list_remove_head(&temp_neighbors);
			branch++;
		}
	}
}

void update_open(linked_node ** open, linked_node ** current_neighbor)
{
	printf("\n updating open current state:");
	display_list(*open);
	linked_node * temp = *open;
	linked_node * new = NULL;	
    	while (temp != NULL)
    	{
        	if (temp->data.waypoint.id == (*current_neighbor)->data.waypoint.id)
        	{
            		printf("\nfound neighbor in open updating open, not insert old v");
        		temp = temp->next;
			continue;
        	}
		
		printf("\n current temp insert g:%d",temp->data.g);
		list_insert(&new,&temp->data);	
        	temp = temp->next;
    	}
	printf("\n current neight g:%d",(*current_neighbor)->data.g);
	list_insert(&new,&(*current_neighbor)->data);	
	*open = new;
	printf("\n updating open new final  state:");
	display_list(new);
	printf("\n updating open final  state:");
	display_list(*open);

}
linked_node * update_neighbor(Astar * self,linked_node ** open,linked_node ** current_neighbor, int g)
{
	linked_node * temp = *open;
    	while (temp != NULL)
    	{
        	if (temp->data.waypoint.id == (*current_neighbor)->data.waypoint.id)
        	{
            		printf("\nfound neighbor in open updating g");
			temp->data.g = g;
			temp->data.f = temp->data.g + h_cost(&temp->data.waypoint,&self->route.finish);
			printf("\nNeigbor %d  g:%d f:%d",temp->data.waypoint.id,temp->data.g,temp->data.f);
            		return temp;
        	}
        	temp = temp->next;
    	}
}
int main(void)
{
	system("killall gnuplot_qt");
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
	system("gnuplot resort.gp -p");
	int input_data[3];
//	get_input_data(input_data);
	input_data[0] = 5;
	input_data[1] = 16;
	input_data[2] = 3;
	init_Route(route,waypoints,input_data);
	init_Astar(astar,resort,route);
	find_path(astar);	
	return(1);	
}
