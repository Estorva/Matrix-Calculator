#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix typedef.h"
#include "matrix.h"
#include "element queue.h"
#include "matrix queue.h"

int main(void)
{
	int N_Matr, i, j, k;
	/*
	 *N_Matr: Number of the matrices
	 */
	char COM, *tok, *SEP = " ", dummy[10];
	
	mali *M;
	M = (mali*)New_Mali();
	
	
	printf("Please enter a command.\n");
	printf("Now available: A, D, \n");
	printf("A for additive, D for determinant\n");
	
	/*
	 *Here comes the first part: Input.
	 *First we have to intput a char, so that we will know what action we should take.
	 *Additive calculation: multiple matrices are possible, but they must be the same size.
	 *Determinant: only one matrix is possible. And it must be a suare matrix.
	 */
	
	
	printf("Now we are inputing all the elements of the matrices.\n");
	printf("When a matrix is finished, type a X in the new row to continue typing matrices.\n");
	printf("If you have done finishing all the matrices, type a Y.\n");
	printf("The column number is defined when you have finished the first row.\n");
	printf("The row number is defined at the moment you typed a Y or Z.\n\n");
	
	Add_Matrix(M);
	/*
	 *Input the elements of the matrices.
	 */
	Show_Mali(M);
	/*
	 *Repeat the input.
	 */
	
	/*
	switch(COM)
	{
		case 'A':
			printf("How many matrices do you want to calculate?\n");
			scanf(" %d", &N_Matr);
			break;
		case 'D':
			
	}*/
	printf("\n\n\nSum:\n");
	Show_Element((matr*)Matrix_Add(M));
	
	printf("\n\nProduct:\n");
	Show_Element((matr*)Matrix_Mult(M));
		
	return 0;
}

/*
This program contains three parts:
1.Input
2.Calculation
3.Output

This program is basicly the re-written previous version.
*/
