/*
 * @file loadmodule.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-19 
 */

var hello1 = require('./module');
hello1.setName('BYVoid');

var hello2 = require('./module');
hello2.setName('BYVoid2');

hello1.sayHello();
