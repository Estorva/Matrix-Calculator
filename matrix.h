#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

void Free_Row(void);
void Free_Column(void);
void Initialize_Matrix(matr*);
matr *Create_Matrix(void);
int Input_Matrix(matr*);
matr *Copy_Matrix(matr*);

#endif
