function Projectile(x,y,dmg,vel) {
	var self = this;
	this.velocity = vel;
	this.damage = dmg;
	this.x = x;
	this.y = y;
	this.entity = new entity(x,y,10,10);
	this.entity.setVelocity(vel.x,vel.y);
	this.entity.onCollide = function(who) {
		var mess = new message(MESSAGE.HEALTH);
		mess.health = self.damage;
		who.getParent().onMessage(mess);
		self.entity.kill();
	}
	this.entity.getParent = function() {
		return self;
	}
	this.onEvent = function(event,extra) {
		switch(event) {
			case EVENT.KEYDOWN:
				this.move(extra);
				break;
			case EVENT.KEYUP:
				this.stop(extra);
				break;
			case EVENT.COLLIDE:
				this.onCollide(extra);
				break;
			case EVENT.MESSAGE:
				this.onMessage(extra);
				break;
		}
	}
	this.onMessage = function(message) {
		switch(message.type) {
			case MESSAGE.HEALTH:
				this.health += message.health;
				break;
		}
	}

}