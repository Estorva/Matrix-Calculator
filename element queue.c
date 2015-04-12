/*
 *Here's code for the modification of the element queue.
 *You see, I didn't really design a matrix structure. I used a queue instead.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix typedef.h"
#include "element queue.h"

void Add_Element(matr *matrix, float new_elmt, int new_acc)
{
	/*
	 *To add an element to the matrix(queue).
	 */
	elnd *new_nd = (elnd*)malloc(sizeof(elnd));
	if(!new_nd)
	{
		printf("Failed to allocate memory!!");
		exit(1);
	}
	new_nd->next = NULL;
	new_nd->elmt = new_elmt;
	new_nd->acc = new_acc;
	if(!matrix->elmt_h->next)
		matrix->elmt_h->next = new_nd;
		
	matrix->elmt_e->next = new_nd;
	matrix->elmt_e = new_nd;
	return;
}

void Show_Element(matr *matrix)
{
	/*
	 *To show a matrix. To list all the elments in the queue
	 */
	if(matrix->_Stop_Output)
	{
		return;
	}
	
	elnd *tmp = matrix->elmt_h->next;
	int row_c = 1, i;
	
	while(tmp)
	{
		printf("Row %d>", row_c);
		for(i = 0; i < matrix->col_n; i++)
		{
			printf("%*.*f ", matrix->len, tmp->acc, tmp->elmt);
			tmp = tmp->next;
		}
		putchar('\n');
		row_c++;
	}
	
	row_c = 1;
	return;
}

elnd *Jump_Row(elnd* curn, int n)
{
	/*
	 *curn: the current node.
	 *n: numbers of elements (nodes) to jump. Can be the column number of a matrix.
	 *To jump to the next row in the column.
	 *You see, there is no pointer inside a element node pointing to that of the next row. (only next column)
	 */
	elnd *tmp = (elnd*)curn;
	int i;
	for(i = 0; i < n; i++)
	{
		tmp = tmp->next;
		if(!tmp)
			return NULL;
	}
	return tmp;
}

