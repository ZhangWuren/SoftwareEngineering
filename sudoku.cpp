#include "iostream"
#include "algorithm"
#include "fstream"
using namespace std;

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
        cout << __trow[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    int sudokuNumber = 0;
    int TranslateArray1[3] = {1, 4, 7};
    int TranslateArray2[3] = {2, 5, 8};
    CRow crow;

    cin >> sudokuNumber;
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
            crow.TranslateAndPrintRow(0);
            crow.TranslateAndPrintRow(3);
            crow.TranslateAndPrintRow(6);
            crow.TranslateAndPrintRow(TranslateArray1[0]);
            crow.TranslateAndPrintRow(TranslateArray1[1]);
            crow.TranslateAndPrintRow(TranslateArray1[2]);
            crow.TranslateAndPrintRow(TranslateArray2[0]);
            crow.TranslateAndPrintRow(TranslateArray2[1]);
            crow.TranslateAndPrintRow(TranslateArray2[2]);
            if (j % 6 == 5)
            {
                next_permutation(TranslateArray1, TranslateArray1 + 3);
            }
            next_permutation(TranslateArray2, TranslateArray2 + 3);
            cout << endl;
        }
        crow.NextRow();
    }

    return 0;
}