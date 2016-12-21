program test
	var b:boolean;

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
end test.
