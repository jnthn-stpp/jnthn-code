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
				var codephrase = rurl.query.substr(5)	
				console.log(codephrase)
			break;
	}
	if(filePath == ""){
		filePath = "./index.html"
		contentType = "text/html"
	}
	fs.readFile(filePath, 'utf8', function (err,data) {
		if(err) {
			return console.log(err)
		}
		response.writeHead(200, { 'Content-Type': contentType})
		response.end(data, 'utf-8')
	});
}

const server = http.createServer(requestHandler)

server.listen(port, (err) => {
	if(err) {
		return console.log("something bad happened")
	}
	
	console.log(`server is listening on ${port}`)

})
