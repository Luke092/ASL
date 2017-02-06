program test
	var x,y:integer;
begin test
	if x > y then
		x = x + 1;
		y = x + 2;
	elsif x == y then
		x = y - 1;
		y = y + 1;
	end;

	while x == y do
		x = x + 1;
	end;

	repeat
		y = y + 2;
	until y > x;

	for x = 0 to 6 do
		y = x * 2;
	end;
end test.
