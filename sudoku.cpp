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
    CRow() //构造函数将第一行设置为6 1 2 3 4 5 7 8 9
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
    void NextRow();                             //对__row[] 进行一次排列
    void TranslateAndPrintRow(int transNumber); //将__row[] 平移transNumber格 //结果赋值给__trow[] 并输出到文件
  private:
    unsigned short __row[9];  //初始行，平移的模板
    unsigned short __trow[9]; //平移后的行
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
    fp = fopen("sudoku.txt", "w"); //打开sudoku.txt

    //判断输入合法性
    for (int i = 0; csudokuNumber[i] != '\0'; i++)
    {
        if (csudokuNumber[i] < '0' || csudokuNumber[i] > '9') //非数字
        {
            cout << "Please enter right number" << endl;
            return false;
        }
    }

    int sudokuNumber = atoi(csudokuNumber);
    if (sudokuNumber > 1000000 || sudokuNumber <= 0) //不合法数字
    {
        cout << "Please input number between 0 and 1,000,000" << endl;
        return false;
    }

    int count = sudokuNumber;           //记录还未生成的数独个数
    int TranslateArray1[3] = {1, 4, 7}; //四五六行平移的格数
    int TranslateArray2[3] = {2, 5, 8}; //七八九行平移的格数
    int TranslateArray3[3] = {0, 3, 6}; //一二三行平移的格数
    CRow crow;

    for (int i = 0; i <= sudokuNumber / 36; i++) //每个全排列的行可以生成36个不同的数独
    {                                            //故需要循环sudokuNumber/36次
        int Times = 0;                           //Times用来判断对应全排列的行需要生成多少个不同的数独
        if (i < sudokuNumber / 36)               //除了最后一次循环未sudokuNumber%36次，别的循环都为36次
        {
            Times = 36;
        }
        else
        {
            Times = sudokuNumber % 36;
        }
        for (int j = 0; j < Times; j++)
        {
            count--;                    //未生成数独个数-1
            for (int k = 0; k < 3; k++) //生成一二三行
            {
                crow.TranslateAndPrintRow(TranslateArray3[k]);
                fputc('\n', fp);
            }
            for (int k = 0; k < 3; k++) //生成四五六行
            {
                crow.TranslateAndPrintRow(TranslateArray1[k]);
                fputc('\n', fp);
            }
            for (int k = 0; k < 3; k++) //生成七八九行
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

            //变换 四五六 、 六七八行
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

void PrintSudoku(int sudoku[][9])
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

int search(int sudoku[][9], int order, int number)
{
    //sudoku[][9]为递归的数组
    //order为当前要设置的格子在数独中的顺序
    //number为要对当前格子填下的数字

    //递归函数
    int csudoku[9][9]; //辅助数组，递归操作改变的是这个辅助数组，使得回溯时不需要再变动原数组，只需要将这个数组释放
    int *csudokuPoint = (int *)csudoku;
    int x = order / 9; //根据顺序转化为坐标
    int y = order % 9;
    for (int i = 0; i < 9; i++) //将递归的数组赋值给辅助数组
    {
        for (int j = 0; j < 9; j++)
        {
            csudoku[i][j] = sudoku[i][j];
        }
    }

    if (order < 0)      //初始化，开始递归
        searchFlag = 0; //结束标志，0未结束，1结束

    if (order >= 0) //将number赋值到csudoku中的对应位置
    {
        csudoku[x][y] = number;
    }
    if (searchFlag) //判断是否结束递归
    {
        return 0;
    }

    //搜索下一个为0的格子的顺序，即目标格
    while (*(csudokuPoint + order) != 0)
    {
        order++;
        if (order > 80)//如果顺序大于80，则表示所有格子都已经填满，设置searchFlag为1，打印结果
        {
            searchFlag = 1;
            PrintSudoku(csudoku);
            return 0;
        }
    }

    for (int i = 1; i <= 9; i++)//对目标格填1~9
    {
        x = order / 9;//根据order获得目标格坐标
        y = order % 9;
        if (isOK(csudoku, x, y, i))//判断当前填法是否合法
        {
            search(csudoku, order, i);//如果合法，则递归目标格子
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