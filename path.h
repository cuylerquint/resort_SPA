#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct child_point {
	Waypoint point;
    	struct child_point *next;
} child_point;;

typedef struct parent_point {
	Waypoint point;
	child_point *path_head;
    	struct parent_point *next;
} parent_point;
