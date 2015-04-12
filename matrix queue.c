/*
 *Here's code for the modification of the matrix queue.
 *You see, it is possible that you have to input several matrices.
 *So I created a queue to save these matrices.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix typedef.h"
#include "matrix.h"
#include "element queue.h"

static void Initialize_Mali(mali* new)
{
	new->mh = (matr*)malloc(sizeof(matr));
	new->mh->nextm = NULL;
	new->me = new->mh;
	return;
}

mali *New_Mali()
{
	mali *new = (mali*)malloc(sizeof(mali));
	Initialize_Mali(new);
	return new;
}

void Show_Mali(mali* mast)
{
	int matr_c = 1;
	matr *tmp = mast->mh->nextm;
	while(tmp)
	{
		printf("\nMatrix %d:\n", matr_c++);
		Show_Element(tmp);
		tmp = tmp->nextm;
	}
	
	return;
}

void Add_Matrix(mali* mast)
{
	/*
	 *To add a matrix to the list(queue).
	 */
	matr *new = (matr*)Create_Matrix();
	int matr_c = 1;
	
	if(!mast->mh->nextm)
		mast->mh->nextm = new;
	mast->me->nextm = new;
	mast->me = new;
	
	printf("Matrix %d:\n", matr_c++);
	
	while(Input_Matrix(new))
	{
		new->nextm = (matr*)malloc(sizeof(matr));
		new = new->nextm;
		mast->me->nextm = new;
		mast->me = new;
		Initialize_Matrix(new);
		
		printf("Matrix %d:\n", matr_c++);
	}
	
	return;
}

matr *Matrix_Add(mali* malist)
{
	/*
	 *To calculate the summation of several matrices.
	 *The idea is to add every element of the matrices in the mali to a new matrix.
	 *So we have a pointer that will run over the new matrix over and over.
	 */
	
	matr *tmpm = malist->mh->nextm;
	
	if(!tmpm->nextm || !tmpm)
	{
		/*
		 *If there is only one matrix (the next one doesn't exist), then exit the function.
		 */
		printf("Too few matrices to add!");
		return (matr*)Create_Halt_Matrix();
	}
	
	if(tmpm->row_n != tmpm->nextm->row_n || tmpm->col_n != tmpm->nextm->col_n)
	{
		/*
		 *You should know that matrices with different size can't add.
		 *This is the first check. When the next matrix is in different size,
		 *then we are gonna send a special matrix that tells the output function not to print anything.
		 *That's the "halt matrix". The "halt" value of it would be 1;
		 */
		printf("These matrices can't be added due to the difference of their size!!");
		return (matr*)Create_Halt_Matrix();
	}
	
	elnd *tmpe = tmpm->elmt_h->next;
	
	matr *new = (matr*)Create_Matrix();
	new->row_n = tmpm->row_n;
	new->col_n = tmpm->col_n;
	new->len = tmpm->len;
	
	while(tmpe)
	{
		Add_Element(new, tmpe->elmt, tmpe->acc);
		tmpe = tmpe->next;
	}
	/*
	 *Copy the first (non-dummy) matrix in the list.
	 */
	
	elnd *sume = new->elmt_h->next;
	tmpm = tmpm->nextm;
	tmpe = tmpm->elmt_h->next;
	
	while(tmpm)
	{
		if(tmpm->nextm && (tmpm->row_n != tmpm->nextm->row_n || tmpm->col_n != tmpm->nextm->col_n))
		{
			/*
			 *Check the size of the next matrix for the second time.
			 */
			printf("These matrices can't be added due to the difference of their size!!");
			return (matr*)Create_Halt_Matrix();
		}
		
		while(tmpe)
		{
			sume->elmt += tmpe->elmt;
			if(sume->acc < tmpe->acc)
				sume->acc = tmpe->acc;
			/*
			 *Get the biggest accurency.
			 */
			sume = sume->next;
			tmpe = tmpe->next;
		}
		
		if(new->len < tmpm->len)
			new->len = tmpm->len;
		/*
		 *Get the biggest length.
		 */
		
		sume = new->elmt_h->next;
		
		tmpm = tmpm->nextm;
		if(!tmpm)
			break;
		/*
		 *In case that the next matrix doesn't exist.
		 */
		
		tmpe = tmpm->elmt_h->next;
	}
	
	return new;
}

matr *Matrix_Mult(mali *malist)
{
	/*
	 *To calculate the product of matrices.
	 *Take the chain "ABCEF" for example, we create a new matrix Z where AB = Z.
	 *Then we calculate ZC, and create another matrix Y = ZC.
	 */
	
	matr *new = (matr*)Create_Matrix(), *ml = malist->mh->nextm, *mr = ml->nextm;
	float sum = 0.0;
	int row_c = 0, col_c = 0, col_c_f, len_t, acc_t, acc_g = 0, acc_gg = 0;
	
	if(!ml || !mr)
	{
		/*
		 *If there is only one matrix (the next one doesn't exist), then exit the function.
		 */
		printf("Too few matrices to multiply!");
		return (matr*)Create_Halt_Matrix();
	}
	
	if(ml->col_n != mr->row_n)
	{
		/*
		 *Suppose we have two matrices A = [a_ij]_m*n and B = [b_ij]_p*q
		 *We can multiply both of them when n = p, and the output would be a m*q matrix.
		 *This is the first check. When the next matrix is in different size,
		 *then we are gonna send a special matrix that tells the output function not to print anything.
		 *That's the "halt matrix". The "halt" value of it would be 1;
		 */
		printf("These matrices can't be multiplied due to the difference of their size!!");
		return (matr*)Create_Halt_Matrix();
	}
	
	elnd *tmpnl, *tmpnj, *tmpnr ,*tmpnn;
	/*
	 *tmpnl: the node of the left matrix.
	 *tmpnr: the node of the right matrix.
	 *For the first time calculating the product, we have AB = Z where Z would be the new matrix.
	 */
	
	while(1)
	{
		col_c = 0;
		row_c = 0;
		
		if(ml->col_n != mr->row_n)
		{
			/*
			 *Check the size of the matrices.
			 */
			printf("These matrices can't be multiplied due to the difference of their size!!\n");
			printf("LCOL: %d, RROW: %d\n", ml->col_n, mr->row_n);
			return (matr*)Create_Halt_Matrix();
		}
		
		tmpnl = tmpnj = ml->elmt_h->next;
		tmpnr = tmpnn = mr->elmt_h->next;
		
		while(tmpnl)
		{
			while(tmpnr)
			{
				sum += tmpnl->elmt * tmpnr->elmt;
				acc_t = tmpnl->acc + tmpnr->acc;
				if(acc_g < acc_t)
					acc_gg = acc_g = acc_t;
				tmpnl = tmpnl->next;
				tmpnr = (elnd*)Jump_Row(tmpnr, mr->col_n);
			}
			
			Add_Element(new, sum, acc_g);
			tmpnn = tmpnn->next;
			
			sum = 0.0;
			acc_g = 0;
			
			col_c++;
			
			if(col_c == mr->col_n)
			{
				col_c_f = col_c;
				col_c = 0;
				row_c++;
				
				tmpnn = mr->elmt_h->next;
				if(!Jump_Row(tmpnj, ml->col_n))
					break;
				tmpnj = (elnd*)Jump_Row(tmpnj, ml->col_n);
			}
			
			tmpnl = tmpnj;
			tmpnr = tmpnn;
		}
		/*Done AB = Z, next ZC = Y, then YD = X, then YE = W*/
		len_t = (ml->len >= mr->len) ? ml->len : mr->len;
		
		new->col_n = col_c_f;
		new->row_n = row_c;
		new->len = (len_t >= acc_gg) ? len_t : acc_gg;
		
		ml = (matr*)Copy_Matrix(new);
		mr = mr->nextm;
		if(!mr)
			break;
		
		Initialize_Matrix(new);
	}
	
	return new;
}

/*
 *the keyword "static" means that the function can only be referenced by the member from the same file.
 */
 
 /*
Determinant caluclation:
case 'D':
			printf("\nNow calculating its determinant value......");
			for(dt=0;dt<10*DL;dt++);
			
			for(k=0;k<R-1;k++)                                 //Determinant Calculation
			{
				for(i=k+1;i<R;i++)
				{
					if(Mtrx[0][k][k]==0)
					{
						DETER=0;
						break;
					}
					
					T=Mtrx[0][i][k];
					
					for(j=0;j<C;j++)
					Mtrx[0][i][j]-=Mtrx[0][k][j]*(T/Mtrx[0][k][k]);
				}
				
			}
			
			for(i=0;i<R;i++)
			DETER*=Mtrx[0][i][i];
			
			printf("\nThe determinant value is %.*f\nMake sure that you have written that result down!", 2*ACC_RST[0], DETER);//Output
	

*/
