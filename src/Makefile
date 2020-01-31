## Makefile for Bloom Filter test
## nmt 2018

CC = gcc
CFLAGS = -Wall 
MATHLIB = -lm

all:	kmeans.o kmeans_test

kmeans.o: kmeans.c
	$(CC) $(CFLAGS) -c kmeans.c $(MATHLIB)

kmeans_test: kmeans.o kmeans.h kmeans_cfg.h
	$(CC) $(CFLAGS) -o kmeans_test kmeans.o main.c $(MATHLIB)

clean:
	rm *.o kmeans_test
