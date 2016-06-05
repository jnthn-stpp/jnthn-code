function updateHex(val, element){
    var len = val.length;
    var hex = "";
    for(var i = 0; i < len; i++){
	hex += val.charCodeAt(i).toString(16);
    }
    document.getElementById(element).value = hex;
//    console.log("hello" + hex + "\n");
};
