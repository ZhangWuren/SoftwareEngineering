#ifndef SUDOKUGEN_H
#define SUDOKUGEN_H

#include "algorithm"
#include "stdlib.h"

class CRow
{ //数独的一行
public:
	unsigned short __row[9];  //初始行，平移的模板
	unsigned short __trow[9]; //平移后的行
	CRow(int number)                    //构造函数将第一行设置为6 1 2 3 4 5 7 8 9
	{
		__row[0] = 6;
		__trow[0] = 6;
		for (int i = 1; i < 9; i++)
		{
			if (i < 6)
			{
				__row[i] = i;
				__trow[i] = i;
			}
			else
			{
				__row[i] = i + 1;
				__trow[i] = i + 1;
			}
		}

		for (int i = 0; i < number; i++)
		{
			std::next_permutation(__row + 1, __row + 9);
		}
	};
	void TranslateRow(int transNumber); //将__row[] 平移transNumber格 //结果赋值给__trow[] 并输出到文件
};

void CRow::TranslateRow(int transNumber)
{
	for (int i = 0; i < 9; i++)
	{
		__trow[(i + transNumber) % 9] = __row[i];
	}
}

int *generateBlank(int order)
{
	order = order % 3;

	int blank1[36] = { 0, 1, 11, 18, 3, 12, 21, 22, 8, 15, 16, 24, 29, 37, 38, 45, 32, 39, 41, 48, 33, 42, 44, 51, 63, 72, 73, 74, 59, 66, 67, 75, 62, 69, 70, 80 };
	int blank2[36] = { 10, 18, 19, 20, 13, 14, 22, 23, 8, 16, 24, 26, 27, 36, 45, 47, 30, 31, 39, 40, 44, 51, 52, 53, 54, 55, 56, 63, 67, 68, 75, 76, 77, 60, 61, 79 };
	int blank3[36] = { 0, 1, 19, 20, 12, 13, 14, 21, 6, 7, 25, 26, 29, 36, 37, 38, 31, 32, 48, 49, 42, 43, 44, 51, 56, 63, 65, 72, 67, 68, 77, 57, 60, 61, 70, 80 };

	switch (order)
	{
	case 0:
		return blank1;
	case 1:
		return blank2;
	case 2:
		return blank3;
	}
}

bool isOK(int(*sudoku)[9], int x, int y, int number)
{
	for (int i = 0; i < 9; i++)
	{
		if (sudoku[x][i] == number && i!=y)
			return false;
	}
	for (int i = 0; i < 9; i++)
	{
		if (sudoku[i][y] == number && i!=x)
			return false;
	}
	for (int i = (x / 3) * 3; i < (x / 3 + 1) * 3; i++)
	{
		for (int j = (y / 3) * 3; j < (y / 3 + 1) * 3; j++)
		{
			if (sudoku[i][j] == number && (i!=x&&j!=y))
				return false;
		}
	}
	return true;
}

int * generateSudoku(int number)
{
	CRow crow(number);
	int sudoku[81];
	int count = 0;
	int transNumber[9] = { 0,3,6,1,4,7,2,5,8 };
	for (int i = 0; i < 9; i++)
	{
		crow.TranslateRow(transNumber[i]);
		for (int j = 0; j < 9; j++)
		{
			sudoku[count] = crow.__trow[j];
			count++;
		}
	}
	return sudoku;
}

#endif SUDOKUGEN_H