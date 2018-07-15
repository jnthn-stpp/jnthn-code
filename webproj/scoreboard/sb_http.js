const http = require('http')
const url = require('url')
const path = require('path')
const fs = require('fs')

module.exports = {
	allowedFiles : "/index.html /style.css /index.js",
	fileExtension : function(url){
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
	},

	fileName : function(url){
		var pathname = url.pathname;
		if(module.exports.allowedFiles.search(pathname) != -1 && pathname != "/"){
			console.log(pathname);
			return "." + pathname;
		}else{
			return "./index.html"
		}
	},

	sendRequest : function(filePath, contentType, response){
		fs.readFile(filePath, 'utf8', function read(err, data){
			if(err){
				throw err;
			}
			response.writeHead(200, { 'Content-Type': contentType})
			response.end(data, 'utf-8')
		});
	},

	requestHandler : function(request, response){
		var rurl = url.parse(request.url, true)

		var filePath = module.exports.fileName(rurl);
		var contentType = module.exports.fileExtension(rurl);	
		module.exports.sendRequest(filePath, contentType, response);
	},

};
