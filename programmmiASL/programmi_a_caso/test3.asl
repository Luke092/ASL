program test
	type	t : integer;
		t1: t;
	var	a : array [6] of integer;
		c : array [2] of integer;
	const 	b: array [2] of integer = [0,1];
	begin test
		a[5] = 20;
		a = [1,2,3,4,5,6];
		c = b;
	end test.
