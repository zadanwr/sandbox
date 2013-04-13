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
					case 25:
					case 40:
					case 38:
					case 39:
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
					case 25:
					case 40:
					case 38:
					case 39:
						Entities[0].stop(extra);
						break;
					case 65:
						new Projectile(512,512,50,new velocity(200,0));
				}
				break;
			case EVENT.MOUSEDOWN:
				print(extra[0] + " " + extra[1] + "\n");
				new Projectile(Entities[0].entity.getPosition()[0]+ 50*extra[4],Entities[0].entity.getPosition()[1]+ 50*extra[5],50,new velocity(extra[4]*200,extra[5]*200));
				break;
		}
	}
}


function Player() {
	this.vX = 0.0;
	this.vY = 0.0;
	this.health = 50;
	print("Player created\n");

	print(Entities.indexOf(this) + "\n");
	this.entity = new entity(512,512,32,32);
	this.entity.parent = this;
	this.entity.onCollide = function(who) {
		this.parent.onCollide(who);
	}
	this.move = function(code) {
		if(code == 111 || code == 25) this.vY = 100.0;
		if(code == 116 || code == 39) this.vY = -100.0;
		if(code == 114 || code == 40) this.vX = 100.0;
		if(code == 113 || code == 38) this.vX = -100.0;
		this.entity.setVelocity(this.vX,this.vY);
	}
	this.stop = function(code) {
		if(code == 111 || code == 25) this.vY = 0;
		if(code == 116 || code == 39) this.vY = 0;
		if(code == 114 || code == 40) this.vX = 0;
		if(code == 113 || code == 38) this.vX = 0;
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
	print("Projectile created\n");
	this.entity = new entity(x,y,10,10);
	this.entity.setVelocity(vel.x,vel.y);
	this.onCollide = function(who) {
		//print("IDGAF\n");
		var mess = new message(MESSAGE.HEALTH);
		mess.health = -10;
		who.onMessage(mess);
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
	print("Wall created\n");
	this.entity = new entity(x,y,w,h);
	print(Entities.indexOf(this) + "\n");
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
