function Trigger(x,y,w,h) {
	var self = this;
	this.type = "trigger";
	this.w = w;
	this.h = h;
	this.cc = 0;
	this.health = 100;
	this.velocity = 15;
	this.pVelocity = 200;
	this.damage = -15;
	this.delay = 20
	this.entity = new entity(x,y,w,h);
	this.entity.onCollide = function(who) {
		self.onCollide(who);
	}
	this.entity.getParent = function() {
		return self;
	}
	this.onEvent = function(event,extra){
	}
	this.onMessage = function(message) {
		switch(message.type) {
			case MESSAGE.HEALTH:
				this.health += message.health;
				break;
		}
		if(this.health <= 0) {
			//serv.nuke();
			this.entity.kill();
		}
	}
}
