#include "iostream"
#include "algorithm"
#include "fstream"
#include "string.h"
#include "string"
using namespace std;
ofstream outFile("sudoku.txt");

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

class Grid
{
  public:
    unsigned short __grid[9][9];
    Grid(){};
};

class Sudoku
{
  public:
    Grid __sudoku[9][9];
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
            outFile << __trow[i] << " ";
        }
        else
        {
            outFile << __trow[i];
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
                outFile << endl;
            }
            for (int k = 0; k < 3; k++)
            {
                crow.TranslateAndPrintRow(TranslateArray1[k]);
                outFile << endl;
            }
            for (int k = 0; k < 3; k++)
            {
                if (k != 2)
                {
                    crow.TranslateAndPrintRow(TranslateArray2[k]);
                    outFile << endl;
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
                outFile << endl;
                outFile << endl;
            }
        }
        crow.NextRow();
    }

    cout << "Already Generate right sudoku in sudoku.txt" << endl;
    return true;
}

bool SovleSudoku(char filename[])
{
    int sudokuInput;
    ifstream readFile("E:\\Documents\\SoftwareEngineering\\in.txt");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            readFile >> sudokuInput;
            cout << sudokuInput << " ";
        }
        cout << endl;
    }
    readFile.close();
    return true;
}

int main(int argc, char *argv[])
{
    outFile.clear();

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

    outFile.close();
    return 0;
}