#ifndef MATRIX_TYPEDEF_H_INCLUDED
#define MATRIX_TYPEDEF_H_INCLUDED

struct Element_Node {
	int acc;
	float elmt;
	struct Element_Node *next;
	/*
	 *elmt: the data of this node(element)
	 *acc: the accurancy of this data. Used for output
	 *This is basically queue.
	 */
};
typedef struct Element_Node elnd;

struct Matrix_Data {
	elnd *elmt_h, *elmt_e;
	int row_n, col_n, len, _Stop_Output, _Input_One_Only;
	struct Matrix_Data *nextm;
	/*
	 *elmt_h: the head of the element(queue)
	 *elmt_e: the end ...
	 *cur_el: the current element
	 *acc: accurancy of the matrix elements. When outputting, in order to keep it look neat, we would need to save space
	 *for the most accurant element. like:
	 *   3  1.7
	 *0.23 3.33
	 *len: the longest length of the elements
	 *halt: to tell the print function to halt.
	 *nextm: next matrix
	 */
};
typedef struct Matrix_Data matr;

struct Matrix_List {
	matr *mh, *me;
	/*
	 *mh: head of the list (queue)
	 *me: end of the list (queue)
	 */
};
typedef struct Matrix_List mali;

#endif
