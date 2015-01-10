var num_draws = 0;
var num_flips = 0;

var c = {
    pixelDraw: function(x, y, c) { num_draws++; },
    flip: function() { num_flips++; },
    height: 200,
    width: 320
};
var g = new Graphics(c);

g.stringDraw(0, 0, "Hello!", 1);
console.log("draws " + num_draws);
c.flip();
debug.assert(num_flips, 1);
g.circleDraw(0, 0, 5, 1);
console.log("draws " + num_draws);
g.circleFill(0, 0, 5, 1);
console.log("draws " + num_draws);
g.lineDraw(0, 0, 5, 1, 1);
console.log("draws " + num_draws);
g.rectDraw(0, 0, 5, 1, 1);
console.log("draws " + num_draws);
g.rectFill(0, 0, 5, 1, 1);
console.log("draws " + num_draws);
g.roundRectDraw(0, 0, 5, 1, 1, 1);
console.log("draws " + num_draws);
g.lineDraw(0, 0, 0, 0, 1);
console.log("draws " + num_draws);

debug.assert_exception(function() { var g = new Graphics()});
debug.assert_exception(function() { var g = new Graphics({})});
/* Test invalid params */
debug.assert_exception(function() { var s = g.stringDraw; s(); } );
debug.assert_exception(function() { var s = g.stringDraw; s(1, 1, "", 1); } );
debug.assert_exception(function() { var s = g.circleDraw; s(); } );
debug.assert_exception(function() { var s = g.circleDraw; s(0, 0, 5, 1); } );
debug.assert_exception(function() { var s = g.circleFill; s(); } );
debug.assert_exception(function() { var s = g.circleFill; s(0, 0, 5, 1); } );
debug.assert_exception(function() { var s = g.lineDraw; s(); } );
debug.assert_exception(function() { var s = g.lineDraw; s(0, 0, 5, 1, 1); } );
debug.assert_exception(function() { var s = g.roundRectDraw; s(); } );
debug.assert_exception(function() { var s = g.roundRectDraw; s(0, 0, 5, 1, 1, 1); } );
debug.assert_exception(function() { var s = g.rectDraw; s(); } );
debug.assert_exception(function() { var s = g.rectDraw; s(0, 0, 5, 1, 1); } );
debug.assert_exception(function() { var s = g.rectFill; s(); } );
debug.assert_exception(function() { var s = g.rectFill; s(0, 0, 5, 1, 1); } );

/* Test canvas operations */
var d = new DummyCanvas();
d.flip();
d.fill(1);
d.pixelDraw(1, 1, 1);