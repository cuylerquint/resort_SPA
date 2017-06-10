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
	print "bitch"
	closed = []
	open = []
	temp_neighbors = []
	start = astar_node(inits.route.start)
	start.f = h_cost(start.waypoint, inits.route.finish)
	start.g = 0
	open.append(start)
	branch = 1
	while(len(open) != 0):
		print "-------------Branch " + str(branch)
		print "getting lowest f in open"
		display_list(open)
		current = get_lowest_f(open)
		print "current lowest:" + str(current.waypoint.id)
		if(current.waypoint.id == inits.route.finish.waypoint.id):
			print "path found"
			build_path(path)


init()
nav()
run_astar()
