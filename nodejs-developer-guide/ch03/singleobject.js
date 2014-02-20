/*
 * @file singleobject.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-19 
 */

function Hello() {
	var name;

	this.setName = function(thyName) {
		name = thyName;
	};

	this.sayHello = function() {
		console.log('Hello ' + name);
	};
};

exports.Hello = Hello;
