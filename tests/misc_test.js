if (false)
    debug.assert(1, 0);
else
    good = 1;

debug.assert(good, 1);

good = 0;

if (false)
    debug.assert(1, 0);
else if (1 == 0)
    debug.assert(1, 0);
else
    good = 1;

debug.assert(good, 1);

good = 0;

if (false)
    debug.assert(1, 0);
else if (1 == 1)
    good = 1;
else
    debug.assert(1, 0);

debug.assert(good, 1);

good = 0;

if (true)
    good = 1;
else if (1 == 1)
    debug.assert(1, 0);
else
    debug.assert(1, 0);

debug.assert(good, 1);

/* Run various API functions */
console.log('--------------');
meminfo();
console.log('--------------');
describe(describe);
describe(3);
console.log('--------------');
debug.dump_env();
console.log('--------------');
debug.assert_exception(function() { compile(function() { }); });
console.log(-1.1);

debug.assert_exception(function() { var x = 3 5; });
debug.assert_exception(function() { debug.assert_cond(true, 1); });
debug.assert_exception(function() { debug.assert_exception(true); });
debug.assert_exception(function() { debug.dump_env(3); });
debug.assert_exception(function() { describe(1, 3) });
debug.assert_exception(function() { compile(1, 3) });
debug.assert_exception(function() { var x = 3, 3; });
good = 0;
try {
    console.log(arguments[0]);
} catch (exp) {
    console.log(exp);
    good = 1;
}
debug.assert(good, 1);
