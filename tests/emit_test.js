var a = {};

/* Test single listener */
var good = 0;
a.on('test1', function() { good++; });
a.emit('test1');
debug.assert(good, 1);
a.removeAllListeners('test1');
a.emit('test1');
debug.assert(good, 1);

/* Test multiple listeners */
var good = 0, good2 = 0;
a.on('test2', function() { good++; });
a.on('test2', function() { good2+=10; });
a.emit('test2');
debug.assert(good, 1);
debug.assert(good2, 10);
a.removeAllListeners('test2');
a.emit('test2');
debug.assert(good, 1);
debug.assert(good2, 10);
