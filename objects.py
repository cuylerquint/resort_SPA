class waypoint:

	def __init__(self,id, x, y,z, weight):
		self.id = id
		self.x = x
		self.y = y
		self.z = z
		self.weight = weight

class chair:

	def __init__(self,id,weight,top,bot):
		self.id = id
		self.weight = weight
		self.top = top
		self.bot = bot

class trail:

	def __init__(self,id,weight,top_id,bot_id):
		self.id = id
		self.weight = weight
		self.top_id = top_id
		self.bot_id = bot_id

class astar_node:

	def __init__(self,waypoint):
		self.waypoint = waypoint

class astar:

	def __init__(self,resort, route):
		self.resort = resort
		self.route = route

class resort:

	def __init__(self,waypoints,chairs,trails):
		self.waypoints = waypoints
		self.chairs = chairs
		self.trails = trails

class route:

	def __init__(self,start,finish,pref):
		self.start = start
		self.finish = finish
		self.pref = pref
