/*
 * @file utilinspect.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-20 
 */

var util = require('util');

function Person() {
	this.name = 'byvoid';

	this.toString = function() {
		return this.name;
	};
}

var obj = new Person();

console.log(util.inspect(obj));
console.log(util.inspect(obj, true));
