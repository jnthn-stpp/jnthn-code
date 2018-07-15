#! /usr/bin/env nodejs
"use strict"
const http = require('http')
const sb_http = require('./sb_http')

var static_port = 8000


const static_server = http.createServer(sb_http.requestHandler)

static_server.listen(static_port, (err) => {
	if(err) {
		return console.log("something bad happened")
	}
	
	console.log(`server is listening on ${static_port}`)

})


