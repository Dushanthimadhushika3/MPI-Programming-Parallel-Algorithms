EXECS=Gather
MPICC?=mpicc

all: ${EXECS}
Gather: bcast.c
	${MPICC} -o Gather gather.cpp

clean:
	rm -f ${EXECS}
