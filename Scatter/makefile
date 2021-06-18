EXECS=Scatter
MPICC?=mpicc

all: ${EXECS}
Scatter: bcast.c
	${MPICC} -o Scatter scatter.cpp

clean:
	rm -f ${EXECS}
