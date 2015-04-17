var divisor = new BigNumber(0);
var ans = new BigNumber(0);
var dividend = new BigNumber(0);
var length = new BigNumber(1);
var steps = 0;
var divs = 1;

var rootTwo = function(x){
    if(x === 0){
	return new BigNumber(2);
    } else {
	var ret = new BigNumber(2);
	return ret.plus(new BigNumber(1).div(rootTwo(x-1)));
    }
};

var setup = function(){
    divisor = new BigNumber(document.getElementById("divisor").value);
    if(document.getElementById("numType").value === "root2"){
	dividend = rootTwo(100).minus(new BigNumber(1));
    } else {
	dividend = new BigNumber(document.getElementById("dividend").value);
    }  
    ans = dividend;
    length = divisor.plus(dividend);
    steps = 0;
    divs = 1;
};

var step = function(){
    if(divisor.gt(ans)){
	ans = ans.plus(dividend);
	divs += 1;
	return;
    }
    ans = ans.minus(divisor);

    steps += 1;
};

var irr = function(ctx){
    //called every loop
    
    ctx.clearRect(0, 0, 650, 300);
    

    ctx.font = "24px sans-serif";
    ctx.fillStyle = "black";
    ctx.fillText("Length", 2, 25, 96);
    ctx.fillText("Measure", 2, 50, 96);
    ctx.fillText("Remainder", 2, 100, 96);
 
    ctx.fillStyle = "rgb(124, 124, 124)";
    ctx.fillRect(100, 2, 500, 24);
    ctx.fillRect(100, 27, 500, 24);
    ctx.fillRect(100, 75, 500, 48);

    ctx.fillStyle = "green";
    ctx.fillRect(100, 2,(dividend.times(new BigNumber(500)).div(length).toNumber()),24);
    ctx.fillStyle = "red";
    ctx.fillRect(100, 27, (divisor.times(new BigNumber(500)).div(length).toNumber()), 24);
    ctx.fillStyle = "blue";
    ctx.fillRect(100, 75, (ans.times(new BigNumber(500)).div(length).toNumber()), 48);
    
    ctx.font = "24px Serif";
    ctx.fillStyle = "white";
    ctx.fillText(dividend.toFormat(8), 100, 25);
    ctx.fillText(divisor.toFormat(8), 100, 50);
    ctx.font = "48px Serif";
    ctx.fillText(ans.toFormat(8), 100, 120);

    ctx.fillStyle = "black";
    ctx.font = "24px Serif";
    ctx.fillText(steps, 150, 200);
    ctx.fillText("Measures", 12, 200);
    ctx.fillText(divs, 150, 240);
    ctx.fillText("Lengths", 12,  240);

    var frac = (steps > divs)? steps : divs;
    frac = Math.floor(Math.log(frac)/Math.log(10));
    ctx.beginPath();
    ctx.moveTo(140, 210);
    ctx.lineTo(175 + 16 * frac, 210);
    ctx.stroke();
};

running = false;

var stop = function(){
    running = false;
}

var run = function(){
    running = true;
    runFun();    
};

var runFun = function(){
    var canvas = document.getElementById("irr-canvas");
    var ctx = canvas.getContext("2d");

    if(!(ans.equals(new BigNumber(0)))){
	step();
	irr(ctx);
    } else { running = false; }
    
    if(running){
	window.requestAnimationFrame(runFun);
    }
};
