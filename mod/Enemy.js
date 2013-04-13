Enemy = function(x,y,w,h) {
	self = this;
	self.health = 100;
	this.entity = new entity(x,y,w,h);
	this.entity.onCollide = function(who) {
		self.onCollide(who);
	}
	this.entity.getParent = function() {
		return self;
	}
	self.onMessage = function(message) {
		print("HI" + "\n");
		switch(message.type) {
			case MESSAGE.HEALTH:
				this.health += message.health;
				break;
		}
		if(self.health <= 0) {
			//serv.nuke();
			self.entity.kill();
		}
	}
}
Enemy.prototype = new Entity;
