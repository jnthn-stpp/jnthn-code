var main = function(){
    var irrCanvas = document.getElementById("irr-canvas");
    var irrCtx = irrCanvas.getContext("2d");
    
    irr(irrCtx);

    window.requestAnimationFrame(main);
};
