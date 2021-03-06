var x = { a : "a", b : "b" };
var y = { };
var proto = { c : "c", d : "d" };
x.prototype = proto;
y.prototype = proto;

console.log(x);
console.log(y);
console.log(x.c);
console.log(y.d);

proto.prototype = { do_something : function() { return 2; } };
debug.assert(x.do_something(), 2);
proto.prototype = { do_something : function() { return 3; } };
debug.assert(x.do_something(), 3);

var conc1 = { prop : 3 }, conc2 = { prop : 4 };
var proto2 = { get_prop : function() { console.log(this.prop); return this.prop; } };
conc1.prototype = proto2;
conc2.prototype = proto2;
debug.assert(conc1.get_prop(), 3);
debug.assert(conc2.get_prop(), 4);
conc1.prototype.get_prop2 = function() { return this.prop + 1; };
debug.assert(conc1.get_prop2(), 4);
debug.assert(conc2.get_prop2(), 5);

function construct(age)
{
    this.papa = "Dad";
    this.mama = "Mom";
    this.age = age;
    this.kuku = function() { return 17; };
}

console.log("=====6====");
construct.prototype = { babi : "babi", testit : function() { console.log("kuku"); } };
console.log("=====7====");
var bla = new construct(15);
console.log("=====8====");
var gugu = new construct(17);
console.log("=====9====");

debug.assert(bla.papa, "Dad");
console.log("=====10====");
debug.assert(bla.kuku(), 17);
console.log("=====11====");
debug.assert(bla.age, 15);
console.log("=====12====");
debug.assert(gugu.age, 17);
console.log("=====13====");
debug.assert(gugu.mama, "Mom");
console.log("=====14====");
debug.assert((new construct(33)).age, 33);
console.log("=====15====");
console.log(construct);
console.log("=====16====");
console.log(bla);
console.log("=====17====");
bla.testit();
debug.assert(bla.babi, "babi");
console.log("=====18====");
function cons() { this.kuku = 3; }
var x = new cons;
debug.assert(x.kuku, 3);

var y = { mumu : "pup" };
var x = { prototype : y };
debug.assert(x.prototype.mumu, "pup");
