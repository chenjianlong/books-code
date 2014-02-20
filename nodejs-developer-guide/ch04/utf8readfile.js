/*
 * @file readfile.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-20 
 */

var fs = require('fs');

fs.readFile('content.txt', 'utf-8', function(err, data) {
	if (err) {
		console.error(err);
	} else {
		console.log(data);
	}
});
