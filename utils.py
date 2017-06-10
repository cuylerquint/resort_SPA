import math

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
