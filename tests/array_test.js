var a = [];
var b = [ 1 ];
var c = [ 1, 2 ];

var x = c[0];
a[0] = 99;
a[1] = 3;
a[2] = 4;
c[100] = "hello world";
debug.dump(a);
debug.assert(c[0], 1);
debug.assert(a[1], 3);
debug.assert(a[2], 4);
debug.dump(a.length);
debug.assert(a.length, 3);
debug.assert(b.length, 1);
debug.dump(c);
debug.assert(c.length, 101);
a.push(7);
debug.assert(a[3],7);
a.push(8, "hello world");
debug.assert(a[5],"hello world");
debug.dump(a);
a.pop();
debug.dump(a);
debug.assert(a.length, 5);
a.forEach(function(v) { debug.dump(v); });
a.forEach(function(v, k, o) { debug.dump(v + "[" + k + "]" + " @ " + o); });

var tt = [];
debug.dump([].prototype);
debug.dump([].forEach);
debug.dump([].forEach.call);
[].forEach.call(a, function (args) { tt.push(args); });
debug.dump("a should be equal to tt");
debug.dump(a);
debug.dump(tt);

var qq = ["god", "jesus", "budha" ];
debug.assert(qq.indexOf("god"), 0);
debug.assert(qq.indexOf("shiva"), -1);
debug.assert(qq.indexOf("budha"), 2);
debug.dump(qq.indexOf("budha"));

var gugu = [ "ka", "ja", "gugu", 1, 2, 3];
debug.assert(gugu.join("--"), "ka--ja--gugu--1--2--3");
debug.assert(gugu.join(), "ka,ja,gugu,1,2,3");
debug.assert(gugu.join(""), "kajagugu123");
debug.assert([].join("--"), "");

var new_arr = [1, 2, 3].map(function(x) { return x + 1; });
debug.dump(new_arr);
debug.assert([1, 2, 3].map(function(x) { return x + 1; })[2], 4);
debug.assert([1, 2, 3].map(function(x) { return x + 1; }).length, 3);
debug.assert([].map(function(x) { return x + 1; }).length, 0);
mapped_obj = [1, 2, 3].map(function(x, k) { return this[k] + 1; }, [ 5, 6, 7]);
debug.dump(mapped_obj);
debug.assert(mapped_obj[1], 7);
var a = new Array("a");
debug.assert(a[0], "a");
var ll = new Array(15);
debug.assert(ll.length, 15);
var lklk = new Array(1, 2, 3, "hello");
debug.assert(lklk[0], 1);
debug.assert(lklk[3], "hello");
var jh = Array(1, 2);
debug.assert(jh[1], 2);
var in_array_test = [ "a", "b", "c" ];
debug.assert_cond(1 in in_array_test);
debug.assert_cond(!(8 in in_array_test));
