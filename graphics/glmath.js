function loadShader(gl, type, source){
	const s = gl.createShader(type);
	gl.shaderSource(s, source);
	gl.compileShader(s);

	if(!gl.getShaderParameter(s, gl.COMPILE_STATUS)){
		console.log("Shader didn't compile: "
		+ gl.getShaderInfoLog(s));
		gl.deleteShader(s);
		return null;
	}

	return s;
}
function initShaderProgram(gl, vss, fss){
	const vs = loadShader(gl, gl.VERTEX_SHADER, vss);
	const fs = loadShader(gl, gl.FRAGMENT_SHADER, fss);
	
	const sp = gl.createProgram();
	gl.attachShader(sp, vs);
	gl.attachShader(sp, fs);
	gl.linkProgram(sp);

	if(!gl.getProgramParameter(sp, gl.LINK_STATUS)){
		console.log("Shader Program not linked: " 
		+ gl.getProgramInfoLog(sp));
		return null;
	}
	return sp
}


const m4 = {
	ident : function(){
		return [
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		];
	},
	trans : function(tx, ty, tz){
		return [
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		tx, ty, tz, 1
		];
	},
	scale : function(sx, sy, sz){
		return [
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1
		];
	},
	rotz : function(theta){
		var c = Math.cos(theta)
		var s = Math.sin(theta)
		return [
		c, s, 0, 0,
		-s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		];
	},
	rotx : function(theta){
		var c = Math.cos(theta)
		var s = Math.sin(theta)
		return [
		1, 0, 0, 0,
		0, c, s, 0,
		0, -s, c, 0,
		0, 0, 0, 1
		];
	},
	roty : function(theta){
		var c = Math.cos(theta)
		var s = Math.sin(theta)
		return [
		c, 0, -s, 0,
		0, 1, 0, 0,
		s, 0, c, 0,
		0, 0, 0, 1
		];
	},

	mult : function(a, b){
		var r = new Float32Array(16);	
		for(var i=0; i<16; i++){
			var t = 0;
			for(var j=0; j<4; j++){
				t += a[(i%4)+4*j]*
				b[4*Math.floor(i/4)+j]
			}
			r[i] = t
		}
		return r;
	},
}

function ident3(){
	return [1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0];
}
