#include "iostream"
#include "cstdio"
using namespace std;

class CRow
{ //数独的一行
  private:
    unsigned short __row[9];
    unsigned short __select[8];

  public:
    CRow(int Rownumber)
    {
        __row[0] = 6;
        for (int i = 0; i < 8; i++)
        {
            if (i < 5)
            {
                __select[i] = i + 1;
            }
            else
            {
                __select[i] = i + 2;
            }
        }
    };

    void PrintRow()
    {
        for (int i = 0; i < 9; i++)
        {
            cout << __row[i] << " ";
        }
        cout << endl;
    };
};

int main(int argc, char *argv[])
{
    int sudokuNumber = 0;
    cin >> sudokuNumber;
    CRow row(1);
    return 0;
}