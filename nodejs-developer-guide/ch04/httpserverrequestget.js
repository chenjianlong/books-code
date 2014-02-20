/*
 * @file httpserverrequestget.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-20 
 */

var http = require('http');
var url = require('url');
var util = require('util');

http.createServer(function(req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end(util.inspect(url.parse(req.url, true)));
}).listen(3000);
