program test

	var	x,y:integer;
		b:boolean;
	const	a: array [10] of integer = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1];

begin test
	x = a[2];
	y = x * (2 + 5) / 8;
	b = (true and false) or true;
	b = 5 == 8;
	b = "hello" != "world";
end test.
