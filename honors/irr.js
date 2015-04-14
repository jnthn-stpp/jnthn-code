var time = 0;
var per = 2;

var irrAction = function(){
    var field = document.getElementById("irr-field");
    per = field.value;
}
var irr = function(ctx){
    //called every loop
    time += 1;
    
    ctx.clearRect(0, 0, 300, 300);
    ctx.fillStyle = "green";
    var apt = 50;
    var locx = 150 + 100 * Math.cos((2*Math.PI/ (60 * per))* time);
    var locy = 150 + 100 * Math.sin((2*Math.PI/ (60 * per))* time);
    ctx.fillRect(locy - apt, locx - apt, 100, 100);

}
