print("Welcome to deathmatch mod!\n");
exec("../scripts/global.js");

function Server() {
	this.state = 0;

	this.nuke = function() {
		for(i = 0;i< Entities.length;i++) Entities[i].entity.kill();
		Entities = new Array();
		this.onCreate();
	}

	this.onCreate = function() {
		Entities.push(new Player());
		Entities.push(new Wall(0,0,2000,100));
		Entities.push(new Wall(0,100,100,1500));
		Entities.push(new Wall(2100,0,100,1500));
		Entities.push(new Wall(0,1600,2000,100));
		Entities.push(new Wall(200,1400,50,200));
		Entities.push(new Wall(100,1200,1000,50));
		Entities.push(new Wall(1300,1200,700,50));
		Entities.push(new EnemyMelee(650,650,32,32));
		Entities.push(new Enemy(350,350,32,32));
		Entities.push(new Enemy(650,350,32,32));
		Entities.push(new Enemy(90,1240,64,64));
		Entities[0].entity.setAsFocus();

	}

	this.onEvent = function(event,extra) {
		switch(event) {
			case EVENT.STEP:
				for(i = 0;i<Entities.length;i++) Entities[i].onEvent(event,null);
				break;
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
				new Projectile(Entities[0].entity.getPosition()[0]+ 50*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 50*extra[5]+11,50,new velocity(extra[4]*200,extra[5]*200));
				break;
		}
	}
}


function Player() {
	var self = this;
	this.vX = 0.0;
	this.vY = 0.0;
	this.health = 50;

	print(Entities.indexOf(this) + "\n");
	this.entity = new entity(100,1568,32,32);
	this.entity.parent = this;
	this.entity.onCollide = function(who) {
		self.onCollide(who);
	}
	this.entity.getParent = function() {
		return self;
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
		if(self.health <= 0) {
			serv.nuke();
		}
	}

}



exec("../mod/Projectile.js");
exec("../mod/Enemy.js");

var serv = new Server();
registerMod("serv");
serv.onCreate();
