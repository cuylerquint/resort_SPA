import math
import inits
from inits import *

def h_cost(cur,goal):   # add in trail weights, so black are faster
	delta_x = (cur.x - goal.x)
	delta_y = (cur.y - goal.y)
	delta_z = (cur.z - goal.z)
	delta_x = abs(delta_x)*abs(delta_x)
	delta_y = abs(delta_y)*abs(delta_y)
	delta_z = abs(delta_z)*abs(delta_z)
	weight = abs(delta_x) + abs(delta_y) + abs(delta_z)
	weight = math.sqrt(weight)
	return weight


def display_list(list):
	for n in list:
		print n.waypoint.id

def print_map(map):
	for key in map:
		print key.id,":",map[key].id

def get_lowest_f(list):
	low = list[0]
	print low.waypoint.id
	for node in list:
		if node.f < low.f:
			low = node
	return low


def build_map(map):
	print_map(map) #  write gp data before poping map
	start_key = inits.route.start
	print "start: " ,start_key
	#for key in map:
	current = start_key
	path = []
	while current != inits.route.finish and current != None:
		path.append(current)
	#	print "------------"
		#print_map(map)
		#print "current: " , current.id
		next = fetch_next_dict_step(current,map)
		#print "next: ", next.id, " "
		#print next.id
		map.pop(current)
		current = next
	path.append(inits.route.finish)
	write_gp_data(path)
	for i in path:
		print i.id

def write_gp_data(path):
	global trails
	global chairs
	w_file = open("suggested_waypoints.dat","w")
	t_file = open("suggested_trails.dat","w")
	count = 1
	for i in range(0,len(path)):
		if i != len(path) - 1:
			for c in chairs:
				if c.bot == path[i] and c.top == path[i+1]:
					line = str(path[i].x) + "\t" +str(path[i].y) + "\t" + str(path[i].z) +"\t" + str(count) + "\n\n"
					w_file.write(line)
					line = str(c.bot.x) + "\t" +str(c.bot.y) + "\t" + str(c.bot.z) +"\t\n\n"
					t_file.write(line)
					line = str(c.top.x) + "\t" +str(c.top.y) + "\t" + str(c.top.z) +"\t\n\n"
					t_file.write(line)
			for t in trails:
				if t.top_id == path[i].id and t.bot_id == path[i+1].id:
					top = get_waypoint_with_id(t.top_id)
					bot = get_waypoint_with_id(t.bot_id)
					line = str(path[i].x) + "\t" +str(path[i].y) + "\t" + str(path[i].z) +"\t" + str(count) + "\n\n"
					w_file.write(line)
					line = str(top.x) + "\t" +str(top.y) + "\t" + str(top.z) +"\t\n\n"
					t_file.write(line)
					line = str(bot.x) + "\t" +str(bot.y) + "\t" + str(bot.z) +"\t\n\n"
					t_file.write(line)
		count += 1
	count -=1
	line = str(inits.route.finish.x) + "\t" +str(inits.route.finish.y) + "\t" + str(inits.route.finish.z) +"\t" + str(count) + "\n\n"
	w_file.write(line)


def fetch_next_dict_step(current,map):
	for key in map:
		if key == current:
			return map[current]

def build_path(path):
	print "non-built path:"
	#remove_dead_ends(path)
	for n in path:
		print "neighbors of : " , n.id



def neighbors(current,pref_level):
	global trails
	global chairs
	neighbors = []
	for t in trails:
		if t.top_id == current.id and t.weight <= pref_level:
			neighbors.append(get_waypoint_with_id(t.bot_id))
	for c in chairs:
		if c.bot == current:
			neighbors.append(c.top)
	return neighbors

def get_waypoint_with_id(id):
	global waypoints
	for w in waypoints:
		if w.id == id:
			return w

def get_astar_with_id(id,astar_nodes):
	for a in astar_nodes:
		if a.waypoint.id == id:
			return a


def get_neighbor_g(neighbor, astar_nodes):
	for a in astar_nodes:
		if a.waypoint == neighbor:
			return a.g

def update_best_map(best_map,current,n):
	print "cur map", print_map(best_map)
	if current.waypoint not in best_map:
		print "making a new key"
		#best_map[n] = current.waypoint
		best_map[current.waypoint] = n
	for key in best_map:
		if key == current.waypoint:
			print "updating key" ,key.id, " to" , n.id
			best_map[key] = n
