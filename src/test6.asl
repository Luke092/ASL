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
end test.
