#include "iostream"
#include "algorithm"
#include "string.h"
#include "string"
#include "time.h"
using namespace std;
FILE *fp;
char mould[36][9][9];

class CRow
{
  public:
    char __row[9];
    char __trow[9];
    CRow()
    {
        __row[0] = 'a';
        __row[1] = 'b';
        __row[2] = 'c';
        __row[3] = 'd';
        __row[4] = 'e';
        __row[5] = 'f';
        __row[6] = 'g';
        __row[7] = 'h';
        __row[8] = 'i';
    }
    void TranslateRow(const int transNumber);
};

void CRow::TranslateRow(const int transNumber)
{
    for (int i = 0; i < 9; i++)
    {
        __trow[(i + transNumber) % 9] = __row[i];
    }
}

void initializeArr()
{
    unsigned short order[9] = {0, 3, 6, 1, 4, 7, 2, 5, 8};
    CRow row;
    for (int k = 0; k < 36; k++)
    {
        for (int i = 0; i < 9; i++)
        {
            row.TranslateRow(order[i]);
            for (int j = 0; j < 9; j++)
            {
                mould[k][i][j] = row.__trow[j];
            }
        }
        if (k % 6 == 5)
        {
            next_permutation(order + 3, order + 5);
        }
        next_permutation(order + 6, order + 8);
    }
    cout << "initialize successfully" << endl;
}

bool GenerateSudoku(const char *csudokuNumber)
{
    initializeArr();

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

    char sudokuResult[9][9];
    char sudokurow[9] = {'6', '1', '2', '3', '4', '5', '7', '8', '9'};

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
            for (int p = 0; p < 9; p++)
            {
                for (int q = 0; q < 9; q++)
                {
                    switch (mould[j][p][q])
                    {
                    case 'a':
                        sudokuResult[p][q] = sudokurow[0];
                        break;
                    case 'b':
                        sudokuResult[p][q] = sudokurow[1];
                        break;
                    case 'c':
                        sudokuResult[p][q] = sudokurow[2];
                        break;
                    case 'd':
                        sudokuResult[p][q] = sudokurow[3];
                        break;
                    case 'e':
                        sudokuResult[p][q] = sudokurow[4];
                        break;
                    case 'f':
                        sudokuResult[p][q] = sudokurow[5];
                        break;
                    case 'g':
                        sudokuResult[p][q] = sudokurow[6];
                        break;
                    case 'h':
                        sudokuResult[p][q] = sudokurow[7];
                        break;
                    case 'i':
                        sudokuResult[p][q] = sudokurow[8];
                        break;
                    }
                    if (q != 8)
                    {
                        fputc(sudokuResult[p][q],fp);
                        fputc(' ',fp);
                    }
                    else
                    {
                       fputc(sudokuResult[p][q],fp);
                       fputc('\n',fp);
                    }
                }
            }
            fputc('\n',fp);
        }
        next_permutation(sudokurow, sudokurow + 9);
    }
    cout << "Already generta right sudokus in sudoku.txt" << endl;

    return true;
}

bool SovleSudoku(const char *filename)
{
}

int main(int argc, char const *argv[])
{
    clock_t startT, finishT;
    double totalTime;
    startT = clock();

    fp = fopen("sudoku.txt", "w");
    // cout << argv[1] << endl;
    // if (!strcmp(argv[1], "-c"))
    // {
    //     GenerateSudoku(argv[2]);
    // }
    // else
    // {
    //     if (!strcmp(argv[1], "-s"))
    //     {
    //         SovleSudoku(argv[2]);
    //     }
    //     else
    //     {
    //         cout << "Please enter right parameter" << endl;
    //     }
    // }

    GenerateSudoku("100");

    fclose(fp);
    finishT = clock();
    totalTime = (double)(finishT - startT) / CLOCKS_PER_SEC;
    cout << "The total time is " << totalTime << "s!" << endl;
    return 0;
    return 0;
}
