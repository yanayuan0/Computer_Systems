/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

/*
 * A program that calls the sum function you will
 * implement in sum.s in x86_64
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* computes the sum of the values 1-n
 * n: an int value
 * returns: the sum of values from 1-n, or -1 if n is not positive
 */
long int sum(long int n);


int main() {

  long int res, n;

  printf("This program computes the sum of 1-N\n");
  printf("Enter an value for n: ");
  scanf("%ld", &n);
  res = sum(n);
  if(res == -1) {
    printf("ERROR: sum passed a non-positive value %ld\n", n);
    printf("try running again and pass a positive value\n");
  } else { 
    printf("The sum of 1 to %ld is %ld\n", n, res);
  }

  return 0;
}
