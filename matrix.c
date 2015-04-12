/*
Here's the code for the modification of a single matrix.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix typedef.h"
#include "matrix.h"
#include "element queue.h"


void Free_Row()
{
	return;
}

void Free_Col()
{
	return;
}

void Initialize_Matrix(matr *matrix)
{
	/*
	 *To remove all the nodes in the matrix.
	 */
	if(matrix->elmt_h->next)
	{
		elnd *tmp = matrix->elmt_h->next, *tmp2 = tmp->next;
		
		while(tmp2)
		{
			free(tmp);
			tmp = tmp2;
			tmp2 = tmp2->next;
		}
	}
	
	/*
	 *To reset all the properties.
	 */
	matrix->row_n = matrix->col_n = matrix->len = matrix->_Stop_Output = 0;
	
	matrix->elmt_h = matrix->elmt_e = (elnd*)malloc(sizeof(elnd));
	matrix->elmt_h->next = matrix->elmt_e->next = NULL;
	matrix->nextm = NULL;
	/*
	 *The dummy node used for queue
	 */
	return;
}

matr *Create_Matrix()
{
	matr *new = (matr*)malloc(sizeof(matr));
	if(!new)
	{
		printf("Failed to allocate memory!!\n");
		exit(1);
	}
	
	Initialize_Matrix(new);
	
	return new;
}

matr *Create_Halt_Matrix()
{
	matr *haltm = (matr*)Create_Matrix();
	haltm->_Stop_Output = 1;
	return haltm;
}

int Input_Matrix(matr *matrix)
{
	int acc_tmp = 0, row_c = 0, col_c = 0, dot_p, bar_boo, i;
	float mult = 1.0, sum_tmp = 0.0;
	char raw_row[100], *tok, *SEP = " ";
	/*
	 *row_c: row count.
	 *col_c: colmun count.
	 *dot_p: the position of the dot.
	 *bar_boo: whether the number is minus or not (having a minus sign, aka a bar)
	 *acc_tmp: acc_tmp: temporary accurancy data. Used in the input process.
	 *sum_tmp: temporary summation. Used int he input process.
	 *mult: the multiplying number;
	 */
	
	matrix->col_n = -1;
	
	while(1)
	{
		printf("Row %d>", row_c + 1);
		gets(raw_row);
		
		if(!strcmp(raw_row, "Z"))
		{
			matrix->row_n = row_c;
			return 0;
		}
		if(!strcmp(raw_row, "Y"))
		{
			matrix->row_n = row_c;
			return 1;
		}
		/*
		 *The return value stands for the action after finishing a matrix.
		 *0: End the whole matrix input.
		 *1: Input the next matrix.
		 */
		
		tok = strtok(raw_row, SEP);
		
		while(tok != NULL)
		{
			bar_boo = 0;/*False*/
			dot_p = strlen(tok);
			/*
			 *Suppose we have a tok = "-3" whose strlen() would return 2
			 *the bar would be tok[0]
			 */
			if(tok[0] == '-')
			bar_boo = 1;/*Found the bar, true that it is minus*/
			
			for(i = 1; i < strlen(tok);i++)
			{
				if(tok[i] == '.')
				{
					dot_p = i;
					acc_tmp = strlen(tok) - dot_p - 1;
				}
				/*
				 *We are looking for '.' in the tok string.
				 *take "-4.33" for example, its bar_boo = 1 and dot_p = 2
				 *the dot would never be tok[0]
				 **/
			}
			
			if(matrix->len < strlen(tok))
				matrix->len = strlen(tok);
			
			for(i = (dot_p - 1); i >= bar_boo; i--)
			{
				sum_tmp += (float)(tok[i] - 48) * mult;
				mult *= 10;
			}
			
			mult = 1.0;
			
			for(i = dot_p + 1; i < strlen(tok); i++)
			{
				mult /= 10;
				sum_tmp += (tok[i] - 48) * mult;
			}
			if(bar_boo)
				sum_tmp *= -1;
			
			Add_Element(matrix, sum_tmp, acc_tmp);
			
			acc_tmp = 0;
			sum_tmp = 0.0;
			mult = 1.0;
			col_c++;
			
			if(col_c >= matrix->col_n && matrix->col_n != -1)
			{
				col_c = matrix->col_n;
				break;
				/*
				 *Reject what's coming next.
				 */
			}
			
			tok = strtok(NULL, SEP);
		}
		
		if(matrix->col_n == -1)
			matrix->col_n = col_c;
		/*
		 *Record the column number.
		 */
		else if(col_c < matrix->col_n)
		{
			while(col_c != matrix->col_n)
			{
				Add_Element(matrix, 0.0, 0);
				col_c++;
				/*
				 *Fill the rest with 0.
				 */
			}
		}
		
		col_c = 0;
		row_c++;
		
		if(matrix->_Input_One_Only)
			return 0;
	}
	
	return 0;
	/*
	 *Though we would never return this value.
	 */
}

matr *Copy_Matrix(matr *matrix)
{
	/*
	 *To copy the entire matrix. The elements, the property.
	 */
	matr *new = (matr*)Create_Matrix();
	elnd *tmp = matrix->elmt_h->next;
	
	while(tmp)
	{
		Add_Element(new, tmp->elmt, tmp->acc);
		tmp = tmp->next;
	}
	
	new->row_n = matrix->row_n;
	new->col_n = matrix->col_n;
	new->len = matrix->len;
	new->nextm = matrix->nextm;
	
	return new;
}





