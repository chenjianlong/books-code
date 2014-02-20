/*
 * @file httpget.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-21 
 */

var http = require('http');

http.get({host: 'www.byvoid.com'}, function(res) {
	res.setEncoding('utf8');
	res.on('data', function(data) {
		console.log(data);
	});
});
