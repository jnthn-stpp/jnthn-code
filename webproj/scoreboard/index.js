var ctx = null;
var init = function(){
	ctx = document.getElementById("board").getContext("2d")
	
	var width = window.innerWidth;
	var height = window.innerHeight;

	ctx.canvas.width  = width;
	ctx.canvas.height  = height;

	console.log(`Width: ${width} Height: ${height}`);
}
