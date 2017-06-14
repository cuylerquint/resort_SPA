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
	print "map:"
	start_key = inits.route.start.id
	print "start_key" ,start_key
	#for key in map:



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
	if n not in best_map:
		print "making a new key"
		best_map[n] = current.waypoint
	for key in best_map:
		if key == n:
			print "updating key" ,key.id, " to" , current.waypoint.id
			best_map[key] = current.waypoint
