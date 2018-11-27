#include "iostream"
using namespace std;

class CRow
{ //数独的一行
  private:
    unsigned short __row[9];

  public:
    CRow(int Rownumber);
    void SwitchRow(int switchNumber);
    void PrintRow();

    CRow(int Rownumber)
    {
        __row[0] = 6;
        
    }

    void PrintRow()
    {
        for (int i = 0; i < 9; i++)
        {
            cout << __row[i] << " ";
        }
        cout << endl;
    }
};

int main(int argc, char *argv[])
{
    int sudokuNumber = 0;
    cin >> sudokuNumber;
}