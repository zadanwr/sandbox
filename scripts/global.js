var EVENT = {
	KEYDOWN:0,
	KEYUP:1,
	MOUSEDOWN:2,
	MOUSEUP:3,
	COLLIDE:4,
	MESSAGE:5
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
}
