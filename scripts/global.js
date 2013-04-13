var EVENT = {
	KEYDOWN:0,
	KEYUP:1,
	MOUSEDOWN:2,
	MOUSEUP:3,
	COLLIDE:4,
	MESSAGE:5,
	STEP:6
}

var MESSAGE = {
	HEALTH:0	
}

var Entities = new Array();


function EntitP(pos,sz,obj) {
	this.X = pos.f;
	this.Y = pos.l;
	this.W = sz.f;
	this.H = sz.l;
}

function Vector2(first,last) {
	this.f = first;
	this.l = last;
	this.normalize = function() {
		var c = Math.sqrt(this.f*this.f+this.l*this.l);
		if(c == 0) return;
		this.f/=c;
		this.l/=c;
	}
}

function velocity(x,y) {
	this.x = x;
	this.y = y;
}

function message(type) {
	this.type = type;
}

function Entity(x,y,w,h) {
	var self = this;
	this.entity = new entity(x,y,w,h);
	this.entity.parent = this;
	this.entity.onCollide = function(who) {
		self.onCollide(who);
	}
	this.entity.getParent = function() {
		return self;
	}
	this.onCollide = function(who) {
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


exec("../scripts/Wall.js");
