program p
	var x,y : integer;

	proc sum(a:integer, b:integer, out c:integer)
	begin sum
		c = a + b;
	end sum;

begin p
	x = 6;
	sum(x,5,y);
	output x;
	output y;
end p.
