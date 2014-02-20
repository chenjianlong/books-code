/*
 * @file readfilesync.js
 * @author Jianlong Chen <jianlong99@gmail.com>
 * @date 2014-02-19 
 */

var fs = require('fs');
var data = fs.readFileSync('file.txt', 'utf-8');
console.log(data);
console.log('end.');
