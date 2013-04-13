print("Welcome to deathmatch mod!\n");
exec("../scripts/global.js");

gun_timeout = 0;

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
		Entities.push(new Wall(2000,0,100,1600));
		Entities.push(new Wall(0,1600,2100,100));
		Entities.push(new Wall(200,1400,50,200));
		Entities.push(new Wall(100,1220,1000,50));
		Entities.push(new Wall(1200,1220,700,50));
		Entities.push(new Wall(1200,1270,50,400));


		Entities.push(new EnemyMelee(650,650,32,32));
		Entities.push(new EnemyMelee(1260,1300,20,20));
		Entities[Entities.length-1].health = 20;
		Entities.push(new EnemyMelee(1260,1320,20,20));
		Entities[Entities.length-1].health = 20;
		Entities.push(new EnemyMelee(1260,1340,20,20));
		Entities[Entities.length-1].health = 20;
		Entities.push(new EnemyMelee(1260,1360,20,20));
		Entities[Entities.length-1].health = 20;
		Entities.push(new EnemyMelee(1260,1380,20,20));
		Entities[Entities.length-1].health = 20;
		Entities.push(new EnemyMelee(1260,1400,20,20));
		Entities[Entities.length-1].health = 20;
		Entities.push(new EnemyMelee(1290,1340,20,20));
		Entities.push(new EnemyMelee(1290,1360,20,20));
		Entities.push(new Enemy(350,350,32,32));
		Entities.push(new Enemy(650,350,32,32));
		Entities.push(new Enemy(90,90,64,64));
		Entities[Entities.length-1].health = 1000;
		Entities[Entities.length-1].pVelocity = 300;
		Entities[Entities.length-1].damage = -.1;
		Entities[Entities.length-1].delay = 10;
		Entities.push(new Trigger(300,1500,100,100));

		Entities[Entities.length-1].onCollide = function(who) {
			this.entity.kill();
			print(this.entity,"\n");
			Entities.push(new Enemy(350,1550,32,32));
			this.onCollide = function(who){}
		}

		
		Entities.push(new Wall(1100,1220,100,50));
		Entities.push(new Trigger(1100,1270,10,10));
		Entities[Entities.length-1].door = Entities[Entities.length-2];
		Entities[Entities.length-1].onCollide = function(who) {
			if(who.type == "player") {
				print(this.door.type,"\n");
				this.entity.kill();
				this.door.entity.kill();
			}
		}
		Entities[0].entity.setAsFocus();

	}

	this.onEvent = function(event,extra) {
		switch(event) {
			case EVENT.STEP:
				gun_timeout--;
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
				if(extra[6]==1)new Projectile(Entities[0].entity.getPosition()[0]+ 35*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 35*extra[5]+11,-5,new velocity(extra[4]*200,extra[5]*200));
				if(extra[6]==3 && gun_timeout < 0) {
					gun_timeout = 500;
					new Projectile(Entities[0].entity.getPosition()[0]+ 130*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 130*extra[5]+11,-15,new velocity(extra[4]*400,extra[5]*400));
					new Projectile(Entities[0].entity.getPosition()[0]+ 110*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 110*extra[5]+11,-15,new velocity(extra[4]*400,extra[5]*400));
					new Projectile(Entities[0].entity.getPosition()[0]+ 90*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 90*extra[5]+11,-15,new velocity(extra[4]*400,extra[5]*400));
					new Projectile(Entities[0].entity.getPosition()[0]+ 70*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 70*extra[5]+11,-15,new velocity(extra[4]*400,extra[5]*400));
					new Projectile(Entities[0].entity.getPosition()[0]+ 50*extra[4] + 11,Entities[0].entity.getPosition()[1]+ 50*extra[5]+11,-15,new velocity(extra[4]*400,extra[5]*400));
				}
				break;
		}
	}
}


function Player() {
	var self = this;
	this.vX = 0.0;
	this.vY = 0.0;
	this.health = 50;
	this.type = "player";

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
		if(who.getParent().type == "trigger") who.getParent().onCollide(self);
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
exec("../mod/Trigger.js");

var serv = new Server();
registerMod("serv");
serv.onCreate();
