typedef struct {
	Waypoint waypoints[WAYPOINTS_SIZE];
	Chair chairs[CHAIRS_SIZE];
	Trail trails[TRAILS_SIZE];
}Resort;




void init_resort(Waypoint * waypoints, Chair * chairs, Trail * trails);
