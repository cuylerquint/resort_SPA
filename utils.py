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
	display_list(list)

def neighbors(current):
	global trails
	global chairs
	neighbors = []
	for t in trails:
		if t.top_id == current.waypoint.id:
			neighbors.append(get_waypoint_with_id(t.bot_id))
	for c in chairs:
		if c.bot == current.waypoint:
			neighbors.append(c.top)

	print "neighbors of :" , current.waypoint.id
	for n in neighbors:
		print n.id

	return neighbors

def get_waypoint_with_id(id):
	global waypoints
	for w in waypoints:
		if w.id == id:
			return w
