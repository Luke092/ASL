all: compiler vm
	cp src/exe.py .
	
compiler:
	make -C src
	cp src/asl_compiler .

vm:
	make -C ../ASLRE/Compilers
	cp ../ASLRE/Compilers/virtual_machine .

clear:
	rm asl_compiler
	rm exe.py
	rm virtual_machine
