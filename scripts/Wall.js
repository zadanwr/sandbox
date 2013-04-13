var Wall = Entity;

Wall.prototype.test = function() {
}
Wall.prototype.onCollide = function(who) {
	print("SMACK\n");
}
Wall.prototype.test = function() {
	print("test\n");
}