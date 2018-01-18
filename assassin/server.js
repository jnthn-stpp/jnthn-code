"use strict"
const http = require('http')
const fs = require('fs')
const path = require('path')
const url = require('url')
const mysql = require('mysql')
const port = 8000

var id = 3;
var apword = "shakennotstirred"

var con = mysql.createConnection({
	host: "localhost",
	user: "jnthn",
	password: "t!9TQGBM",
	database: "assassin",
	multipleStatements: true,
});

var allowedFiles = "/stats.html /style.css /login.html /death.html /register.html"

var fileExtension = function(url){
	var extname = path.extname(url.pathname)
	var contentType = ""
	switch(extname){
		case '.js':
			contentType = 'text/javascript'
			break;
		case '.css':
			contentType = 'text/css'
			break;
		case '.html':
			contentType = 'text/html'
			break;
	}
	return contentType;
};

var fileName = function(url){
	var pathname = url.pathname;
	if(allowedFiles.search(pathname) != -1 && pathname != "/"){
		return "." + pathname;
	}else{
		return "./index.html"
	}
}

var sendRequest = function(filePath, contentType, response, dynamic, inserts, raw){
	if(dynamic===undefined){
		dynamic = false
		inserts=[];
	}
	if(!raw){
		fs.readFile(filePath, 'utf8', function read(err, data){
			if(err){
				throw err;
			}
			if(dynamic){
				for(var i=0; i<inserts.length;i++){
					var re = new RegExp('\\{' + i + '\\}', 'g')
					data = data.replace(re, inserts[i]);
				}
			}
			response.writeHead(200, { 'Content-Type': contentType})
			response.end(data, 'utf-8')
		});
	}else{
		response.writeHead(200, { 'Content-Type': contentType})
		response.end(filePath, 'utf-8')
	}
}

var login = function(url, callback, response){
	var code = url.query["code"].replace(/\+/g, ' ');
	var inserts = [];
	var qs = 'SELECT Name, Target, Alive, Score, Influence, KillList FROM t2 WHERE Operation=\"'+ code + '\"; SELECT count(*) FROM t2 WHERE Alive=1;';

	inserts.push(code) //operation 0
	con.query(qs, function(err, result, fields){
		if (err) throw err;
		if(result[0][0] == null || result[0][0]["Alive"] == 0){
			callback("./death.html", "text/html", response)

		} else if(result[1][0]["count(*)"] <= 2){
			callback("./congrat.html", "text/html", response)
		}
		else {
			var ti = 1;
			if(id > 0){
				ti = id;
			}
			inserts.push(result[0][0]["Name"]) //agent 1
			inserts.push(result[0][0]["Target"]) //target 2
			inserts.push(result[0][0]["Score"]) //score 3
			inserts.push((100.0 * result[0][0]["Influence"] / ti).toFixed(1)) 
			//influ 4
			inserts.push(result[0][0]["KillList"]) //kills 5
			callback("./user.html", "text/html", response, true, inserts)
		}
	});
}

var register = function(url, id, callback, response){
	var user = url.query["user"]
	var op = url.query["op"]
	var inserts = [];

	inserts.push(op) //operation 0
	inserts.push(user) //agent 1	

	con.query("SELECT ID FROM t2 WHERE Alive=1; SELECT ID FROM t2 WHERE Name=\""+user+"\"; SELECT ID FROM t2 WHERE Operation=\""+op+"\";", function(err, result){
		if(result[0].length == 0 &&
			result[1].length==0 &&
			result[2].length==0){
			con.query("INSERT INTO t2(ID, Name, Operation, Alive, Score, Influence, KillList) VALUES("+id+',\"'+user+'\",\"'+op+'\",0,0,1,\"\");', function(err, result){
				if (err) throw err;
				callback("./confirm.html", "text/html", response, true, inserts);
			});
		} else {
			callback("./death.html", "text/html", response);
		}
	});
}

var admin = function(url, callback, response, pword){
	if(pword === undefined){
		pword = url.query["pword"]
	}
	var inserts = [];
	if(pword === apword){
		con.query("SELECT count(*) from t2;", function(err, result){
			if (err) throw err;
			inserts.push(result[0]["count(*)"])
			//total 0
			con.query("SELECT count(*) FROM t2 WHERE Alive=0;", function(err, result){
				if (err) throw err;
				inserts.push(result[0]["count(*)"])
				//dead, inactive 1
				callback("./admin.html", "text/html", response, true, inserts);
			});
		});
	} else {
		callback("./index.html", "text/html", response)
	}
}

var start = function(url, callback, response){
	con.query("UPDATE t2 SET Alive=1", function(err, result){
		if(err) throw err;
		admin(url, callback, response, apword)
	});
}

var end = function(url, callback, response){
	id = 0;
	con.query("DELETE FROM t2; DELETE FROM t2log", function(err, result){
		if(err) throw err;
		admin(url, callback, response, apword)
	});
}

var assign = function(url, callback, response){
	var off = parseInt(url.query['off']);
	var qs =`UPDATE t2
		SET Target = (
		SELECT Name FROM
		(SELECT * FROM t2) AS x
		WHERE (t2.ID+` + off + ")%"
		+ id + "= x.ID);"
	con.query(qs, function(err, result){
			if(err) throw err;
			admin(url, callback, response, apword)
		});
}

var die = function(url, callback, response){
	var code = url.query['code']
	var qs =`SELECT Name, Target, Influence, Alive
		FROM t2
		WHERE Operation=\"${code}\";`
	con.query(qs, function(err, result){
		if(err) throw err;
		var name = result[0]["Name"];
		var target = result[0]["Target"];
		var influ = result[0]["Influence"];
		var alive = result[0]["Alive"];

		if(alive == 1){
			qs = `UPDATE t2 SET
				Target=\"${target}\",
				Score=Score+1,
				Influence=Influence+${influ},
				KillList=CONCAT(KillList,\"${name}<br>\")
				WHERE Target=\"${name}\" AND Alive=1;

				UPDATE t2 SET
				Alive=0,
				Influence=0
				WHERE Name=\"${name}\";
			
				INSERT INTO t2log(Description, time)
				VALUES(\"${name} was killed\",
				(SELECT CURRENT_TIMESTAMP));`
				
			con.query(qs, function(err, result){
				if(err) throw err;
				callback("death.html", "text/html", response);
			})
		}else{
			callback("death.html", "text/html", response);
		}
	})
}

const killList = function(url, callback, response){
	var qs = 'SELECT Description FROM t2log; SELECT count(*) FROM t2 WHERE Alive=1;'	
	con.query(qs, function(err, result){
		if(err) throw err;
		var objstr = JSON.stringify(result);
		callback(objstr, "application/json", response, false, [], true);
	})
}

const setID = function(callback){

	var qs = 'SELECT MAX(Id) FROM t2'	
	con.query(qs, function(err, result){
		if(err) throw err;
		if(result[0]['MAX(Id)'] == null){
			id = 0
		}else{
			id = result[0]['MAX(Id)']
		}
		callback();
	})
}


const requestHandler = (request, response) => {
	var rurl = url.parse(request.url, true)

	switch(rurl.pathname){
		case '/login':
			login(rurl, sendRequest, response); 	
			break;
		case '/register':
			register(rurl, id, sendRequest, response);
			id++;
			break;
		case '/admin':
			admin(rurl, sendRequest, response);
			break;
		case '/start0546':
			start(rurl, sendRequest, response);
			break;
		case '/end0546':
			end(rurl, sendRequest, response);
			break;
		case '/assign0546':
			assign(rurl, sendRequest, response);
			break;
		case '/die':
			die(rurl, sendRequest, response);
			break;
		case '/killlist':
			killList(rurl, sendRequest, response);
			break;
		default:
			var filePath = fileName(rurl);
			var contentType = fileExtension(rurl);	
			sendRequest(filePath, contentType, response);
	}
}

const server = http.createServer(requestHandler)

setID( function(){
	server.listen(port, (err) => {
		if(err) {
			return console.log("something bad happened")
		}
		
		console.log(`server is listening on ${port}`)

	})
})
