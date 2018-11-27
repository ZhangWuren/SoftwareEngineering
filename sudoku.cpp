#include "iostream"

using namespace std;

class CRaw{ //数独的一行
    private:
    unsigned short __raw[9];
    public:
    CRaw();
    void SwitchRaw(int switchNumber);

};

int main(int argc, char *argv[])
{
    int sudokuNumber = 0;
    cin >> sudokuNumber;
}