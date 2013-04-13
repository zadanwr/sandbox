print("Welcome to deathmatch mod!\n");
exec("../scripts/global.js");

function Server() {
	this.state = 0;

	this.onCreate = function() {
		Entities.push(new Vector2(200,200),new Vector2(20,20),new Player());
	}

	this.onEvent = function(event) {
		switch(event.type) {
			case EVENT.KEYDOWN:
				if(event.code = '`') print("Open console\n");
				break;
		}
	}
}


function Player() {
	print("Player created");
}

