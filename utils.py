import math
import inits
from inits import *

def h_cost(cur,goal):
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
	print list

def get_lowest_f(list):
	low = list[0]
	print low.waypoint.id
	for node in list:
		if node.f < low.f:
			low = node
	return low

def build_path(list):
	print "non-built path:"
	for n in list:
		print n.id

def neighbors(current):  #  modify based off skill
	global trails
	global chairs
	neighbors = []
	for t in trails:
		if t.top_id == current.waypoint.id:
			neighbors.append(get_waypoint_with_id(t.bot_id))
	for c in chairs:
		if c.bot == current.waypoint:
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
	print "cur map", best_map
	if n not in best_map:
		best_map[n] = current.waypoint
	for key in best_map:
		if key == n:
			best_map[key] = current.waypoint
