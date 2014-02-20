/*
 * @file event.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-19 
 */

var EventEmitter = require('events').EventEmitter;
var event = new EventEmitter();

event.on('some_event',function() {
	console.log('some_event occured.');
});

setTimeout(function() {
	event.emit('some_event');
}, 1000);

