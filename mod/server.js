print("Welcome to deathmatch mod!\n");
exec("../scripts/global.js");

function Server() {
	this.state = 0;

	this.onCreate = function() {
		Entities.push(new Player());
		Entities.push(new Wall(0,0,100,500));
		Entities.push(new Wall(450,400,500,100));
		Entities[0].entity.setAsFocus();
	}

	this.onEvent = function(event,extra) {
		//print("Key " + extra + "\n");
		switch(event) {
			case EVENT.KEYDOWN:
				switch(extra) {
					case 111:
					case 113:
					case 114:
					case 116:
						Entities[0].move(extra);
						break;
				}
				break;
			case EVENT.KEYUP:
				switch(extra) {
					case 111:
					case 113:
					case 114:
					case 116:
						Entities[0].stop(extra);
						break;
				}
				break;
		}
	}
}


function Player() {
	this.vX = 0.0;
	this.vY = 0.0;
	this.health = 50;
	print("Player created\n");
	this.entity = new entity(512,512,120,120);
	this.move = function(code) {
		if(code == 111) this.vY = 100.0;
		if(code == 116) this.vY = -100.0;
		if(code == 114) this.vX = 100.0;
		if(code == 113) this.vX = -100.0;
		this.entity.setVelocity(this.vX,this.vY);
	}
	this.stop = function(code) {
		if(code == 111) this.vY = 0;
		if(code == 116) this.vY = 0;
		if(code == 114) this.vX = 0;
		if(code == 113) this.vX = 0;
		this.entity.setVelocity(this.vX,this.vY);
	}
	this.onCollide = function(who) {
		print("IDGAF\n");
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

function Projectile(x,y,dmg,vel) {
	this.velocity = vel;
	this.damage = dmg;
	this.x = x;
	this.y = y;
	print("Player created\n");
	this.entity = new entity(x,y,10,10);
	this.entity.setVelocity(vel.x,vel.y);
	this.onCollide = function(who) {
		//print("IDGAF\n");

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

function Wall(x,y,w,h) {
	this.vX = 0;
	this.vY = 0;
	print("Player created\n");
	this.entity = new entity(x,y,w,h);
	
	this.onCollide = function(who) {
		print("WALL DGAF\n");
	}
	this.onEvent = function(event,extra) {
		switch(event) {
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
		}
	}

}

var serv = new Server();
registerMod("serv");
serv.onCreate();
