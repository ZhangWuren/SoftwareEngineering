#include "iostream"
#include "algorithm"
#include "fstream"
#include "string.h"
using namespace std;
ofstream OutFile("sudoku.txt");

class CRow
{ //数独的一行
  private:
    unsigned short __row[9];
    unsigned short __trow[9];

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
};

void CRow::NextRow()
{
    next_permutation(__row + 1, __row + 9);
}

void CRow::TranslateAndPrintRow(int transNumber)
{
    for (int i = 0; i < 9; i++)
    {
        __trow[(i + transNumber) % 9] = __row[i];
    }
    for (int i = 0; i < 9; i++)
    {
        if (i != 8)
        {
            OutFile << __trow[i] << " ";
        }
        else
        {
            OutFile << __trow[i];
        }
    }
}

bool GenerateSudoku(char *csudokuNumber)
{
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
                OutFile << endl;
            }
            for (int k = 0; k < 3; k++)
            {
                crow.TranslateAndPrintRow(TranslateArray1[k]);
                OutFile << endl;
            }
            for (int k = 0; k < 3; k++)
            {
                if (k != 2)
                {
                    crow.TranslateAndPrintRow(TranslateArray2[k]);
                    OutFile << endl;
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
                OutFile << endl;
                OutFile << endl;
            }
        }
        crow.NextRow();
    }

    cout << "Already Generate right sudoku in sudoku.txt" << endl;
    return true;
}

bool SovleSudoku(char *filename)
{

}

int main(int argc, char *argv[])
{
    OutFile.clear();

    if (strcmp(argv[2], "-c"))
    {
        GenerateSudoku(argv[2]);
    }
    else
    {
        if(strcmp(argv[2], "-s"))
        {
            SovleSudoku(argv[2]);
        }
        else
        {
            cout<<"Please enter right parameter"<<endl;
        }
    }

    OutFile.close();
    return 0;
}