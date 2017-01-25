program test
	var x,y,z:integer;
begin test
	for x = 0 to 6 do
		for y = x * 2 to x * x do
			z = y + x;
		end;
	end;
	for z = 0 to 10 do
		x = z;
	end;
end test.
