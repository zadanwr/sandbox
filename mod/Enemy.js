function Enemy(x,y,w,h) {
	var self = this;
	this.w = w;
	this.h = h;
	this.cc = 0;
	this.health = 100;
	this.velocity = 15;
	this.pVelocity = 200;
	this.damage = -15;
	this.delay = 20
	this.image = new image("../mod/enemy.png");
	this.sprite = new sprite(this.image);
	this.sprite.addAnimation(0,0,1,1,0,0,new Array(1),1);
	this.entity = new entity(x,y,w,h);
	this.entity.setSprite(this.sprite);
	this.entity.setAnimation(0);
	this.entity.onCollide = function(who) {
	}
	this.entity.getParent = function() {
		return self;
	}
	this.onEvent = function(event,extra){
		if(this.health <= 0) return;
		if(event == EVENT.STEP) {
			this.cc++;
			if(this.cc == this.delay) {
				this.cc = 0;
				var vect = new Vector2(Entities[pID].entity.getPosition()[0]-this.entity.getPosition()[0],Entities[pID].entity.getPosition()[1]-this.entity.getPosition()[1]);
				if(Math.sqrt(vect.f*vect.f+vect.l*vect.l) < 800){
					vect.normalize();
					new Projectile(this.entity.getPosition()[0]+ (this.w+10)*vect.f + 11,this.entity.getPosition()[1]+ (this.h+10)*vect.l+11,this.damage,new velocity(vect.f*this.pVelocity,vect.l*this.pVelocity));
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
	this.image = new image("../mod/enemy.png");
	this.sprite = new sprite(this.image);
	this.sprite.addAnimation(0,0,1,1,0,0,new Array(1),1);
	this.entity = new entity(x,y,w,h);
	this.entity.setSprite(this.sprite);
	this.entity.setAnimation(0);
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
				var vect = new Vector2(Entities[pID].entity.getPosition()[0]-this.entity.getPosition()[0],Entities[pID].entity.getPosition()[1]-this.entity.getPosition()[1]);
				if(Math.sqrt(vect.f*vect.f+vect.l*vect.l) < 1000){
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

