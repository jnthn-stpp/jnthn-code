var num = new BigNumber(0);
var ans = new BigNumber(0);
var div = new BigNumber(1);
var steps = 0;

var rootTwo = function(x){
    if(x === 0){
	return new BigNumber(2);
    } else {
	var ret = new BigNumber(2);
	return ret.plus(new BigNumber(1).div(rootTwo(x-1)));
    }
};

var irrAction = function(){
    var field = document.getElementById("irr-field");
    num = rootTwo(field.value).minus(new BigNumber(1));
};

var step = function(){
    if(div.gt(ans)){
	ans = ans.plus(num);
    }
    
    ans = ans.minus(div);

    steps += 1;
    
    
};

var irr = function(ctx){
    //called every loop
    
    ctx.clearRect(0, 0, 300, 300);
    ctx.fillStyle = "green";

    ctx.font = "48px Serif";
    ctx.fillText(num.toFormat(8), 5, 50);
    ctx.fillStyle = "red";
    ctx.fillText(ans.toFormat(8), 5, 100);
    ctx.fillStyle = "blue";
    ctx.fillText(steps, 5, 150);
};

var run = function(){

    var canvas = document.getElementById("irr-canvas");
    var ctx = canvas.getContext("2d");
    
    if(!(ans.equals(new BigNumber(0)))){
	step();
	irr(ctx);
    }
    window.requestAnimationFrame(run);
    
};
