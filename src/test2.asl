program test
	type	t : integer;
		t1: t;
	var 	x,y:integer;
		s : string;
		b : boolean;
		p : t1;
		a : array [6] of integer;
	const	bool:boolean = true;
		int:integer = 145;
		str:string = "Ciao mondo";
		arr1: array[2] of integer = [1,2];
		arr:array[3] of array [3] of integer = [[1,2,3],[4,5,6],[7,8,9]];
		arr2:array[2] of array[2] of array[2] of integer = [[[1,2],[3,4]],[[5,6],[7,8]]];

	begin test
		x = 2;
		a = [1,2,3,4,5,6];
		a[0] = x;
	end test.
