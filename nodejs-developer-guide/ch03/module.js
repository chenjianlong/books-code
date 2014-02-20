/*
 * @file module.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-19 
 */

var name;

exports.setName = function(thyName) {
	name = thyName;
};

exports.sayHello = function() {
	console.log('Hello ' + name);
};
