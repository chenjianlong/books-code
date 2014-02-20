/*
 * @file eventerror.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-20 
 */

var events = require('events');

var emitter = new events.EventEmitter();

emitter.emit('error');
