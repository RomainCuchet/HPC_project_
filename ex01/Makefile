CC      := mpicc
CFLAGS  := -std=c99 -O3 -march=native -Wall -Wextra -pedantic -fopenmp
DEPFLAGS:= -MMD -MP

SRC := main.c mpi_sum.c omp_sum.c utils.c
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:.o=.d)

all: benchmark

benchmark: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c header.h
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -f benchmark $(OBJ) $(DEP)

.PHONY: all clean

-include $(DEP)
