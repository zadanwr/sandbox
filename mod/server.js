print("Welcome to deathmatch mod!\n");
exec("../scripts/global.js");

function Server() {
	this.state = 0;

	this.onCreate = function() {
		Entities.push(new Vector2(200,200),new Vector2(20,20),new Player());
	}

	this.onEvent = function(event,extra) {
		print("Key " + extra + "\n");
		switch(event) {
			case EVENT.KEYDOWN:
				if(extra == 49) print("Open console\n");
				break;
		}
	}
}


function Player() {
	print("Player created\n");
}

var serv = new Server();
registerMod("serv");
serv.onCreate();
