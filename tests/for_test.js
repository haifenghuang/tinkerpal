var i;

for (i = 0; i < 20; i+=2)
	console.log(i);
debug.assert(i, 20);

for (i = 0; i < 20; i++)
{
    if (i == 5)
	break;
}

debug.assert(i, 5);

var x, y, z = 0;

for (x = 0; x < 10; x++)
{
    for (y = 0; y < 10; y++)
    {
	if (y == 5)
	    break;

	z++;
    }
}

debug.assert(z, 50);

var i, a = [4, 5, 6], sum = 0;
for (i in a) 
    sum += a[i];
debug.assert(sum, 15);
for (i in a) 
    sum += a[i];
debug.assert(sum, 30);
for (i in a)
{
    if (i == 1)
	break;
    sum += a[i];
}
debug.assert(sum, 34);

var a = { a : 1, b : 1 };
a.prototype = { c : 2 };
var b = [];
for (i in a)
    b.push(i);

debug.assert(b[2], "c");

var i, j;

for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
        console.log("(" + i + ", " + j + ")");

var count = 5;
for (;--count;);
debug.assert(count, 0);
var count = 5;
for (;;) if (count-- == 3) break;
debug.assert(count, 2);
debug.assert_exception(function() {
    for (var 3 = 4; ;) {}
});
debug.assert_exception(function() {
    for (3 = 4; ;) {}
});

var a = [ 0, 1, 2 ], b;
function f() { return a; }
for (b in f())
    debug.assert(a[b], b);

var a = [[ 0, 1, 2 ]], b;
for (c in a[0])
    debug.assert(a[0][c], c);
