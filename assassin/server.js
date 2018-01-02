"use strict"
const http = require('http')
const fs = require('fs')
const path = require('path')
const url = require('url')
const port = 8000

const requestHandler= (request, response) => {
	
	var stuff = "";
	var rurl = url.parse(request.url)
	var method = request.method
	var pathname = rurl.pathname
	console.log(request.url)

	var filePath = ""
	var contentType = ""
	var extname = path.extname(pathname)

	var logging = false
	var codephrase = ""
	var agent = ""
	var target = ""

	switch(extname){
		case '.js':
			contentType = 'text/javascript'
			if(pathname == '/index.js'){
				filePath = "./index.js"
			}
			if(pathname == '/login.js'){
				filePath = "./login.js"
			}

			break;
		case '.css':
			contentType = 'text/css'
			if(pathname == '/style.css'){
				filePath = "./style.css"
			}
			break;
		case '.html':
			contentType = 'text/html'
			if(pathname == '/login.html'){
				filePath = "./login.html"
			}
			break;
	}
	
	switch(pathname){
		case '/login':
				codephrase = rurl.query.substr(5).replace('+', ' ')	
				console.log(codephrase)
				logging = true
				target = codephrase
				agent=codephrase
				contentType = 'text/html'
				filePath = "./user.html"
			break;
	}
	if(filePath == ""){
		filePath = "./index.html"
		contentType = "text/html"
	}
	var fileString = ""
	fs.readFile(filePath, 'utf8', function read(err, data){
		if(err){
			throw err;
		}
		fileString = data
		if(logging){
			console.log("logging!")
			console.log(agent)
			fileString = fileString.replace("{operation}", codephrase);
			fileString = fileString.replace("{agent}", agent);
			fileString = fileString.replace("{target}", target);
		}
		response.writeHead(200, { 'Content-Type': contentType})
		response.end(fileString, 'utf-8')
	});
}

const server = http.createServer(requestHandler)

server.listen(port, (err) => {
	if(err) {
		return console.log("something bad happened")
	}
	
	console.log(`server is listening on ${port}`)

})
