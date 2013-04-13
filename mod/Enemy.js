function Enemy(x,y,w,h) {
	var self = this;
	this.w = w;
	this.h = h;
	this.cc = 0;
	this.health = 100;
	this.velocity = 15;
	this.entity = new entity(x,y,w,h);
	this.entity.onCollide = function(who) {
	}
	this.entity.getParent = function() {
		return self;
	}
	this.onEvent = function(event,extra){
		if(this.health <= 0) return;
		if(event == EVENT.STEP) {
			this.cc++;
			if(this.cc == 20) {
				this.cc = 0;
				var vect = new Vector2(Entities[0].entity.getPosition()[0]-this.entity.getPosition()[0],Entities[0].entity.getPosition()[1]-this.entity.getPosition()[1]);
				if(Math.sqrt(vect.f*vect.f+vect.l*vect.l) < 500){
					vect.normalize();
					new Projectile(this.entity.getPosition()[0]+ (this.w+10)*vect.f + 11,this.entity.getPosition()[1]+ (this.h+10)*vect.l+11,50,new velocity(vect.f*200,vect.l*200));
					this.entity.setVelocity(vect.f*this.velocity,vect.l*this.velocity);
				}

			}

		}
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

function EnemyMelee(x,y,w,h) {
	var self = this;
	this.w = w;
	this.h = h;
	this.cc = 0;
	this.health = 100;
	this.velocity = 160;
	this.entity = new entity(x,y,w,h);
	this.entity.onCollide = function(who) {
		var mess = new message(MESSAGE.HEALTH);
		mess.health = -.75;
		if(who.getParent().type == "player")who.getParent().onMessage(mess);
	}
	this.entity.getParent = function() {
		return self;
	}
	this.onEvent = function(event,extra){
		if(this.health <= 0) return;
		if(event == EVENT.STEP) {
			this.cc++;
			if(this.cc == 20) {
				this.cc = 0;
				var vect = new Vector2(Entities[0].entity.getPosition()[0]-this.entity.getPosition()[0],Entities[0].entity.getPosition()[1]-this.entity.getPosition()[1]);
				if(Math.sqrt(vect.f*vect.f+vect.l*vect.l) < 600){
					vect.normalize();
					this.entity.setVelocity(vect.f*this.velocity,vect.l*this.velocity);
				}
			}
		}
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

