/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

/* 
 *  This function reads in a txt file in which a number of floats are
 *  listed and they are stored in a dynamic array. The program then 
 *  conduct mathematical operations on the data and print out minimum,
 *  maximum, mean, median, and standard deviation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readfile.h"

// N: start size for first dynamically allocated array of values
#define N             20
// MAXFILENAME: max length of input file name string + 1 (includes '\0')
#define MAXFILENAME   256
// you can add your own constants (using #define) here if needed/desired

// function prototypes
float *get_values(int *size, int *capacity, char *filename);
void sort(float *arr, int n);
void swap(float *array, int left, int right);
void printresults(int size, int capacity, float *sortedvals);
void printArr(int size, float *arr);

/**********************************************************************/
int main(int argc, char *argv[]) {

  // add other local variables you will need here
  char filename[MAXFILENAME];
  float *vals=NULL; /////
  int size, capacity;

  // this code checks command line args to make sure program was run
  // with filename argument.  If not, calls exit to quit the program
  
  if (argc != 2) {
    printf ("usage: %s filename\n", argv[0]);
    exit(1);
  }

  // this copies the filename command line argument into the 
  // string variable filename
  strncpy(filename, argv[1], MAXFILENAME-1);

  capacity = N;

  // call get_values function:
  vals = get_values(&size, &capacity, filename);

  // implement the rest of main
  sort(vals, size);

  // print out results
  printresults(size, capacity, vals);

  free(vals);

  return 0;
}


/**********************************************************************/
/* This function reads in values from the input file into a dynamically
 * allocated array of floats that it returns.  It uses a doubling 
 * algorithm to increase the size of the array as it needs more space
 * for the values read in from the file.
 * 
 *   size: set to the number of data values read in from the file
 *   capacity: set to the total number of bprintArr(int size, float *arr)uckets in the returned array
 *   filename: the name of the file to open
 *
 *   returns: the base address of the array of values read in 
 *            or NULL on error20n comment.  You should write 
 *         similarly detailed comments for every function you write.
 */
float *get_values(int *size, int *capacity, char *filename){

  // TODO: add more local variables here:
  float *values=NULL; ////
  float *newvalues=NULL; /////
  float floatdata;
  int position;
  int ret;
  int newsize;
  values = (float*)malloc((*capacity) * sizeof(float));
  if (values == NULL) {
    printf("Error: no memory assigned");
  }

  if (open_file(filename)) {
    printf("ERROR: can't open %s\n", filename);  // step 1: open the file
    return NULL;
  }

  position = 0;
  newsize = 0;
  ret = read_float(&floatdata); 
  while (ret != -1){
    if (newsize+1 > *capacity){
      *capacity = (*capacity) * 2;
      newvalues = (float *)malloc((*capacity) * sizeof(float));
      if (newvalues == NULL) {
        printf("Error: no memory assigned");
      }
      for (int i=0; i<newsize; i++){ /////
        newvalues[i] = values[i];
      }
      free(values);
      values = newvalues;
      newvalues=NULL;
    }
    values[position] = floatdata;
    position++;
    ret = read_float(&floatdata);
    newsize++;

  }
 
  close_file(); // close the file
  *size = newsize;
  return values;   // return the values array
}


/************************************************************************/
/*
 * This function bubble sorts the array with n elements from
 * smallest to largest.
 *    arr - float* - the array to be sorted
 *    n - int - the size of the array
 */
void sort(float *arr, int n){
    int i, j;
    int swapped;
    for (i=0; i<n-1; i++){
        swapped = 0;
        for (j=0; j<n-i-1; j++){
            if (arr[j] > arr[j+1]){
                swap(arr, j, j+1);
                swapped = 1;
            }
        }
        if (swapped == 0){
            break;
        }
    }
}

/* This helper function swaps the two floats at position left 
 * and right in the array.
 *   left and right - int - position index
 *   array - float* - array of floats
 */
void swap(float *array, int left, int right){ 
  float holder = array[left];
  array[left] = array[right];
  array[right] = holder;
}


/************************************************************************/
/* This function conducts mathematical operations on the elements of the array
 * and print out minimum, maximum, mean, median, standard deviation respectively.
 * 
 *   size: set to the number of data values read in from the file
 *   capacity: set to the total number of bprintArr(int size, float *arr)uckets in the returned array
 *   sortedvals: the array of the data that is already sorted from the smallest to
 *   the largest.
 *
 */
void printresults(int size, int capacity, float *sortedvals){
  float min, max, mean, median, stddev, constant;
  double insidesqrt;
  float sum=0;
  float stddevsum=0;
  int med, unusedcap;

  min = sortedvals[0];
  max = sortedvals[size-1];

  for (int i=0; i<size; i++){
    sum = sum + sortedvals[i];
  }
  mean = sum/size;

  med = size/2;
  median = sortedvals[med];

  for (int i=0; i<size; i++){
    stddevsum += pow((sortedvals[i]-mean), 2);

  }

  constant = pow((size-1), -1);
  insidesqrt = (constant * stddevsum);
  stddev = sqrt(insidesqrt);

  unusedcap = capacity - size;

  printf("Results:\n-------\n");
  printf("num values: %-20d\n", size);
  printf("       min: %-20.3f\n", min);
  printf("       max: %-20.3f\n", max);
  printf("      mean: %-20.3f\n", mean);
  printf("    median: %-20.3f\n", median);
  printf("   std dev: %-20.3f\n", stddev);
  printf("unused array capacity: %d\n", unusedcap);

}