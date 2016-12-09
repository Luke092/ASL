# Main
compiler: parser.o sintax_utility.o lex.o  functionHash.o print_utility.o symbtab.o CodeGen_Utility.o main.c
	cc -g -o asl_compiler lex.o sintax_utility.o parser.o functionHash.o print_utility.o symbtab.o CodeGen_Utility.o main.c

# utilities
sintax_utility.o: sintax_utility.c
	cc -g -c sintax_utility.c
	
functionHash.o: functionHash.c
	cc -g -c functionHash.c
	
print_utility.o: print_utility.c
	cc -g -c print_utility.c
	
CodeGen_Utility.o: CodeGen_Utility.c
	cc -g -c CodeGen_Utility.c

# symbtab
symbtab.o: symbtab.c
	cc -g -c symbtab.c

# Yacc compile
parser.o:   parser.c
	cc -g -c parser.c
	
parser.c:   parser.y
	bison -vd -o parser.c parser.y


# Insert lex compile commands
lex.o: lex.c parser.o
	cc -g -c lex.c
	
lex.c: sintaxAnalizer.lex
	flex -o lex.c sintaxAnalizer.lex


# Remove all files not needed
	
clear:
	rm *.o
	
