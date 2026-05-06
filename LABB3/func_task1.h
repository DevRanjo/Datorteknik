#ifndef FUNC_TASK1_H
#define FUNC_TASK1_H

char* two_d_alloc(int N, int M, int byte_size);
void two_d_dealloc(char* ptr);

//row major
void two_d_store(char* ptr, int row_indx, int col_indx, int byte_size, int value, int total_columns);
int two_d_fetch(char* ptr, int row_indx, int col_indx, int byte_size, int total_columns);

//column major
void column_two_d_store(char* ptr, int row_indx, int col_indx, int byte_size, int value, int total_rows);
int column_two_d_fetch(char* ptr, int row_indx, int col_indx, int byte_size, int total_rows);

void mem_dump(char* arr, int total_bytes, int word_size);

#endif
