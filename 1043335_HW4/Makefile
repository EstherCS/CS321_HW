main:
	yacc -d 1043335.y 
	flex 1043335.l 
	g++ lex.yy.c y.tab.c -lfl

run :
	./a.out <design_01.isc 

clean:
	rm a.out

all: clean main run

start: main run


