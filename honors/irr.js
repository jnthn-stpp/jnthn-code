var ans = new BigNumber(0);

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
    ans = rootTwo(field.value).minus(new BigNumber(1));
};
var irr = function(ctx){
    //called every loop
    
    ctx.clearRect(0, 0, 300, 300);
    ctx.fillStyle = "green";

    ctx.font = "48px, Serif";
    ctx.fillText(ans.toFormat(50), 10, 10);
};
