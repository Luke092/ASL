program test
	var b:boolean;
	    a: array [10] of array[100] of string;

begin test
	b = if true then
			false 
		elsif 1==2 then
			false
		elsif 4 <= 5 then
			true
		else 
			true
		end;
	output b;
	input b;
	output a;
	input a;
end test.
