
function Server() {
	this.state = 0;
	this.onCreate = function() {


	}

	this.onEvent = function(event) {
		switch(event.type) {
			case EVENT.KEYDOWN:
				if(event.code = '`') print("Open console\n");
				break;
		}
	}
}



