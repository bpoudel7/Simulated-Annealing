all: rhc

rhc: eval1.o RandHillClimbV3.o
	g++ eval1.o RandHillClimbV3.o -o rhc

RandHillClimbV3.o: RandHillClimbV3.c
	g++ -Wall -c RandHillClimbV3.c

clean:
	rm RandHillClimbV3.o rhc	 	

