function wev() {
	this.onEvent = function(event,extra) {
		switch(event) {
			case 1:
				if(extra == 65) {
					e.kill();
					exec("../mod/server.js");
				}
				break;
			}
		}
}
i = new image("../mod/bwos.png");
s = new sprite(i);
s.addAnimation(0,0,1,1,0,0,new Array(1),1);

e = new entity(300,200,600,400);
e.setSprite(s);
e.setAnimation(0);
e.setAsFocus();

var serv = new wev();
registerMod("serv");