/* 
 * Reads input file and writes one integer to standard output stream
 * Computes value of an expression built from array arguments using numbers from in. 
 * First number in input file is used as the integer n.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 1000

typedef int (*fptr_t)(int, int);

int sum(int x, int y) {
   return x + y;
}

int diff(int x, int y) {
   return x - y; 
}

int prod(int x, int y) {
   return x * y;;
}

int quot(int x, int y) {
   return x / y;
}

int rem(int x, int y) {
   return x % y;
}

int apply(fptr_t fp, int x, int y) {
   return fp(x, y);
}

int compute(fptr_t fcn[5], int* A, int* idx, int n) {
   int temp1 = A[0];
   for(int i = 0; i < n; i++) {
      temp1 = apply(fcn[idx[i]], temp1, A[i+1]);
   }

   return temp1;
}

int main(int argc, char* argv[]) {
   fptr_t select[5] = {sum, diff, prod, quot, rem};

   FILE *in;		// handle for input file
   FILE *out;		// handle for output file 		
   int* opcode; 	// array holding all the op-codes
   int* operand;	// array holding all the operands
   int n;
   int arr[MAX_LENGTH];
   
   in = fopen(argv[1], "r"); 

   if (in == NULL) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(1);
   }
   else {
      fscanf(in, "%d", &n);
      printf("n: %d\n", n);
      opcode = calloc(n, sizeof(int));
      operand = calloc(n+1, sizeof(int));
   }
   
   for (int i = 0; i < n; i++) {
       fscanf(in, "%d", &arr[i]);
       opcode[i] = arr[i];
   }

   for(int i = 0; i < n + 1; i++) {
      fscanf(in, "%d", &arr[i]);
      operand[i] = arr[i];
   }

   int value = compute(select, operand, opcode, n);

   if((out = fopen("out", "w")) == NULL) {
      printf("Unable to write to file out\n");
      exit(EXIT_FAILURE);
   }
   else {
      fprintf(out, "%d\n", value);
   }

   free(opcode);
   free(operand);
   opcode = NULL;
   operand = NULL;

   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}
