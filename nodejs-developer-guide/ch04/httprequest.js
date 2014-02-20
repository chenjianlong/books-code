/*
 * @file httprequest.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-21 
 */

var http = require('http');
var querystring = require('querystring');

var contents = querystring.stringify({
	name: 'byvoid',
	email: 'byvoid@byvoid.com',
	address: 'Zijing 2#, Tsinghua University',
});

var options = {
	host: 'www.byvoid.com',
	patch: '/application/node/post.php',
	method: 'POST',
	headers: {
		'Content-Type': 'application/x-www-form-urlencoded',
		'Content-Length': contents.length
	}
};

var req = http.request(options, function(res) {
	res.setEncoding('utf8');
	res.on('data', function(data) {
		console.log(data);
	});
});

req.write(contents);
req.end();
