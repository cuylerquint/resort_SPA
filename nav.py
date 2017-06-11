import os
import inits
from inits import *
import utils
from utils import *

def nav():
	global waypoints
	global trails
	global chairs
	r1 = inits.r1
	route = inits.route
	for wp in r1.waypoints:
		print wp.id
	for t in r1.trails:
		print t.id

	for c in r1.chairs:
		print "-----"
		print c.top.id
		print c.bot.id
	print "your start:" + str(route.start.id)
	print "your finininh:" + str(route.finish.id)
	print "your diff:" + str(route.pref)

def run_astar():
	global route
	closed = []
	open = []
	path = []
	astar_nodes = []
	start = astar_node(inits.route.start)
	start.f = h_cost(start.waypoint, inits.route.finish)
	start.g = 0
	open.append(start)
	astar_nodes.append(start)
	branch = 1
	best_map = {}
	while(len(open) != 0):
		print "-------------Branch " + str(branch)
		print "getting lowest f in open"
		display_list(open)
		current = get_lowest_f(open)
		print "current lowest:" + str(current.waypoint.id)
		if(current.waypoint.id == inits.route.finish.id):
			path.append(current.waypoint)
			print "path found"
			build_path(path)
			break
		open.remove(current)
		closed.append(current)
		for n in neighbors(current):
			if all(n.id != a.waypoint.id for a in astar_nodes): # new astar node for this neigbor
				print "new astar node:" , n.id
				temp_astar_node = astar_node(n)
				astar_nodes.append(temp_astar_node)
				temp_astar_node.g = 999999999999  # default
			if n in closed:
				continue
			tentative_g = current.g + h_cost(current.waypoint,n)
			neighbor_astar_node = get_astar_with_id(n.id,astar_nodes)
			print "neighbor_astar_node:", neighbor_astar_node
			print "astar_nodes:",astar_nodes
			print "open:",open
			if neighbor_astar_node not in open:
				print "adding to open"
				open.append(neighbor_astar_node)
			if tentative_g >= neighbor_astar_node.g:
				continue # not a better route
			if current.waypoint not in path:
				path.append(current.waypoint)
			update_best_map(best_map,current,n)
			neighbor_astar_node.g = tentative_g
			neighbor_astar_node.f = neighbor_astar_node.g + h_cost(n,inits.route.finish)
		branch += 1




init()
nav()
run_astar()
