from objects import *
import os

waypoints = []
trails = []
chairs = []

def init_waypoints():
	w1 = waypoint(1,0,500,0,0)
	w2 = waypoint(2,0,400,100,0)
	w3 = waypoint(3,100,400,100,0)
	w4 = waypoint(4,100,400,0,0)
	w5 = waypoint(5,0,300,200,0)
	w6 = waypoint(6,200,300,200,0)
	w7 = waypoint(7,200,300,0,0)
	w8 = waypoint(8,0,200,300,0)
	w9 = waypoint(9,300,200,300,0)
	w10 = waypoint(10,300,200,0,0)
	w11 = waypoint(11,0,100,400,0)
	w12 = waypoint(12,400,100,400,0)
	w13 = waypoint(13,400,100,0,0)
	w14 = waypoint(14,0,0,500,0)
	w15 = waypoint(15,250,0,500,0)
	w16 = waypoint(16,500,0,500,0)
	w17 = waypoint(17,500,0,250,0)
	w18 = waypoint(18,500,0,0,0)
	w19 = waypoint(19,175,100,250,0)
	w20 = waypoint(20,350,100,175,0)

	global waypoints
	waypoints.append(w1)
	waypoints.append(w2)
	waypoints.append(w3)
	waypoints.append(w4)
	waypoints.append(w5)
	waypoints.append(w6)
	waypoints.append(w7)
	waypoints.append(w8)
	waypoints.append(w9)
	waypoints.append(w10)
	waypoints.append(w11)
	waypoints.append(w12)
	waypoints.append(w13)
	waypoints.append(w14)
	waypoints.append(w15)
	waypoints.append(w16)
	waypoints.append(w17)
	waypoints.append(w18)
	waypoints.append(w19)
	waypoints.append(w20)


def init_trails():
	#green list,id,diff,top_id,bot_id
	global waypoints
	t1 = trail(1,1,1,5)
	t2 = trail(2,1,5,8)
	t3 = trail(3,1,8,11)
	t4 = trail(4,1,11,14)
	t5 = trail(5,1,8,12)
	t6 = trail(6,1,11,15)
	t7 = trail(7,1,7,20)
	t8 = trail(8,1,20,16)
	t9 = trail(9,1,20,17)

	#blue list,id,diff,top_id,bot_id
	t10 = trail(10,2,1,3)
	t11 = trail(11,2,3,8)
	t12 = trail(12,2,3,6)
	t13 = trail(13,2,3,10)
	t14 = trail(14,2,19,14)
	t15 = trail(15,2,6,19)
	t16 = trail(16,2,6,9)
	t17 = trail(17,2,6,20)
	t18 = trail(18,2,20,18)
	t19 = trail(19,2,9,12)
	t20 = trail(20,2,12,16)

	#black
	t21 = trail(21,3,1,7)
	t22 = trail(22,3,7,10)
	t23 = trail(23,3,10,13)
	t24 = trail(24,3,13,18)
	t25 = trail(25,3,10,12)
	t26 = trail(26,3,13,17)
	t27 = trail(27,3,5,19)
	t28 = trail(28,3,19,16)
	t29 = trail(29,3,19,15)


	global trails
	trails.append(t1)
	trails.append(t2)
	trails.append(t3)
	trails.append(t4)
	trails.append(t5)
	trails.append(t6)
	trails.append(t7)
	trails.append(t8)
	trails.append(t9)
	trails.append(t10)
	trails.append(t11)
	trails.append(t12)
	trails.append(t13)
	trails.append(t14)
	trails.append(t15)
	trails.append(t16)
	trails.append(t17)
	trails.append(t18)
	trails.append(t19)
	trails.append(t20)
	trails.append(t21)
	trails.append(t22)
	trails.append(t23)
	trails.append(t24)
	trails.append(t25)
	trails.append(t26)
	trails.append(t27)
	trails.append(t28)
	trails.append(t29)


def init_chairs():
	global waypoints
	global chairs
	c1 = chair(1,7,waypoints[4],waypoints[14])
	c2 = chair(2,3,waypoints[1],waypoints[11])
	c3 = chair(3,9,waypoints[2],waypoints[13])
	c4 = chair(4,9,waypoints[2],waypoints[17])
	c5 = chair(5,3,waypoints[5],waypoints[15])
	c6 = chair(6,6,waypoints[0],waypoints[18])
	c7 = chair(7,6,waypoints[0],waypoints[19])
	c8 = chair(8,3,waypoints[3],waypoints[11])
	c9 = chair(9,7,waypoints[6],waypoints[16])
	chairs.append(c1)
	chairs.append(c2)
	chairs.append(c3)
	chairs.append(c4)
	chairs.append(c5)
	chairs.append(c6)
	chairs.append(c7)
	chairs.append(c8)
	chairs.append(c9)




def init_resort():
	global waypoints
	global trails
	global chairs
	global r1
	r1 = resort(waypoints,chairs,trails)


def init_route(input):
	global route
	global r1
	print input[0]
	for wp in r1.waypoints:
		print wp.id
		if wp.id == int(input[0]):
			start = wp
		if wp.id == int(input[1]):
			finish = wp

	route = route(start,finish,input[2])

def get_input():
	os.system("killall gnuplot_qt")
	os.system("gnuplot resort.gp -p")
	start = raw_input("Start waypoint: ")
	finish = raw_input("Finih waypoint: ")
	diff = raw_input("skill pref (1,2,3): ")
	input = [start,finish,diff]
	return input


def init():
	init_waypoints()
	init_trails()
	init_chairs()
	init_resort()
	input = get_input()
	init_route(input)
