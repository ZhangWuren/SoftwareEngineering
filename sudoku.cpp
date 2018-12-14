#include "iostream"
#include "algorithm"
#include "fstream"
#include "string.h"
#include "string"
#include "time.h"
using namespace std;
FILE *fp;
FILE *fpOutput;
int searchFlag = 0;

class CRow
{ //数独的一行
  public:
    CRow()
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
    };
    void NextRow();
    void TranslateAndPrintRow(int transNumber);

  private:
    unsigned short __row[9];
    unsigned short __trow[9];
};

void CRow::NextRow()
{
    next_permutation(__row + 1, __row + 9);
}

void CRow::TranslateAndPrintRow(int transNumber)
{
    char rowString[19];
    for (int i = 0; i < 9; i++)
    {
        __trow[(i + transNumber) % 9] = __row[i];
    }
    for (int i = 0, j = 0; i < 9; i++)
    {
        if (i != 8)
        {
            rowString[j] = __trow[i] + '0';
            rowString[j + 1] = ' ';
            j += 2;
        }
        else
        {
            rowString[j] = __trow[i] + '0';
            rowString[j + 1] = '\0';
        }
    }
    fputs(rowString, fp);
}

bool isOK(int (*sudoku)[9], int x, int y, int number)
{
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[x][i] == number)
            return false;
    }
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[i][y] == number)
            return false;
    }
    for (int i = (x / 3) * 3; i < (x / 3 + 1) * 3; i++)
    {
        for (int j = (y / 3) * 3; j < (y / 3 + 1) * 3; j++)
        {
            if (sudoku[i][j] == number)
                return false;
        }
    }
    return true;
}

bool GenerateSudoku(char *csudokuNumber)
{
    fp = fopen("sudoku.txt", "w");
    for (int i = 0; csudokuNumber[i] != '\0'; i++)
    {
        if (csudokuNumber[i] < '0' || csudokuNumber[i] > '9')
        {
            cout << "Please enter right number" << endl;
            return false;
        }
    }

    int sudokuNumber = atoi(csudokuNumber);

    if (sudokuNumber > 1000000 || sudokuNumber <= 0)
    {
        cout << "Please input number between 0 and 1,000,000" << endl;
        return false;
    }

    int count = 0;
    int TranslateArray1[3] = {1, 4, 7};
    int TranslateArray2[3] = {2, 5, 8};
    int TranslateArray3[3] = {0, 3, 6};
    CRow crow;

    count = sudokuNumber;
    for (int i = 0; i <= sudokuNumber / 36; i++)
    {
        int Times = 0;
        if (i < sudokuNumber / 36)
        {
            Times = 36;
        }
        else
        {
            Times = sudokuNumber % 36;
        }
        for (int j = 0; j < Times; j++)
        {
            count--;
            for (int k = 0; k < 3; k++)
            {
                crow.TranslateAndPrintRow(TranslateArray3[k]);
                fputc('\n', fp);
            }
            for (int k = 0; k < 3; k++)
            {
                crow.TranslateAndPrintRow(TranslateArray1[k]);
                fputc('\n', fp);
            }
            for (int k = 0; k < 3; k++)
            {
                if (k != 2)
                {
                    crow.TranslateAndPrintRow(TranslateArray2[k]);
                    fputc('\n', fp);
                }
                else
                {
                    crow.TranslateAndPrintRow(TranslateArray2[k]);
                }
            }
            if (j % 6 == 5)
            {
                next_permutation(TranslateArray1, TranslateArray1 + 3);
            }
            next_permutation(TranslateArray2, TranslateArray2 + 3);

            if (count != 0)
            {
                fputc('\n', fp);
                fputc('\n', fp);
            }
        }
        crow.NextRow();
    }

    cout << "Already Generate right sudoku in sudoku.txt" << endl;
    return true;
}

void PrintSokudu(int sudoku[][9])
{
    for (int k = 0; k < 9; k++)
    {
        char rowString[19];
        for (int i = 0, j = 0; i < 9; i++)
        {
            if (i != 8)
            {
                rowString[j] = sudoku[k][i] + '0';
                rowString[j + 1] = ' ';
                j += 2;
            }
            else
            {
                rowString[j] = sudoku[k][i] + '0';
                rowString[j + 1] = '\0';
            }
        }
        fputs(rowString, fpOutput);
        if (k != 8)
        {
            fputc('\n', fpOutput);
        }
    }
}

bool search(int (*sudoku)[9], int order, int number)
{
    int copy[9][9];
    int *copyPoint = (int *)copy;
    int x = order / 9;
    int y = order % 9;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            copy[i][j] = sudoku[i][j];
        }
    }

    if (order < 0)
        searchFlag = 0;

    if (order >= 0)
    {
        copy[x][y] = number;
    }
    if (searchFlag)
    {
        return 0;
    }

    while (*(copyPoint + order))
    {
        order++;

        if (order > 80)
        {
            searchFlag = 1;
            PrintSokudu(copy);
            return 0;
        }
    }

    for (int i = 1; i <= 9; i++)
    {
        x = order / 9;
        y = order % 9;
        if (isOK(copy, x, y, i))
        {
            search(copy, order, i);
        }
    }
    return -1;
}

bool SovleSudoku(char filename[])
{
    int inputSudoku[81];
    int inputSudokuArr[9][9];
    FILE *fpInput;
    fpInput = fopen(filename, "r");

    char ch;
    for (int i = 0; i < 81;)
    {
        ch = fgetc(fpInput);
        if (ch >= '0' && ch <= '9')
        {
            inputSudoku[i] = ch - '0';
            i++;
        }
    }

    for (int i = 0, k = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            inputSudokuArr[i][j] = inputSudoku[k];
            k++;
        }
    }
    search(inputSudokuArr, -1, 0);
    while (1)
    {
        char ch;
        for (int i = 0; i < 81;)
        {
            ch = fgetc(fpInput);
            if (ch == -1)
                break;
            if (ch >= '0' && ch <= '9')
            {
                inputSudoku[i] = ch - '0';
                i++;
            }
        }

        if (ch == -1)
        {
            break;
        }

        for (int i = 0, k = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                inputSudokuArr[i][j] = inputSudoku[k];
                k++;
            }
        }
        fputc('\n', fpOutput);
        fputc('\n', fpOutput);
        search(inputSudokuArr, -1, 0);
    }

    fclose(fpInput);
    return true;
}

int main(int argc, char *argv[])
{
    clock_t startT, finishT;
    double totalTime;
    startT = clock();
    fpOutput = fopen("sudoku.txt", "w");

    cout << argv[1] << endl;
    if (!strcmp(argv[1], "-c"))
    {
        GenerateSudoku(argv[2]);
    }
    else
    {
        if (!strcmp(argv[1], "-s"))
        {
            SovleSudoku(argv[2]);
        }
        else
        {
            cout << "Please enter right parameter" << endl;
        }
    }

    fclose(fp);
    fclose(fpOutput);
    finishT = clock();
    totalTime = (double)(finishT - startT) / CLOCKS_PER_SEC;
    cout << "The total time is " << totalTime << "s!" << endl;
    return 0;
}