program test
	type	t:integer;
		t1:string;
	var 	a,b:integer;

	proc beta()
		var x:integer;
		proc gamma()
			var x:integer;
		begin gamma
			x = x + 3;
		end gamma;
		func alfa() : boolean
		begin alfa
			true
		end alfa;
	begin beta
		x = 2 + 3;
	end beta;
	func alfa() : integer
		const x:integer = 8;
	begin alfa
		(x + 15) * 2
	end alfa;

	begin test
		a = alfa();
		b = a * 2;
	end test.
