#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUNTIMES 1.0  //用于测试重复解某个题的次数
#define MAXRESULT 1     //设定每个数独题目取得解的数目，有自己编的题目可能有多个解

typedef unsigned char intu; //定义新变量类型intu，实质为unsigned char ,占1字节，操作会省点时间


int place(intu (*array)[9],short int pos,intu num );
//核心程序，递归设置下一个位置的值
//pos为按横行排列依次的顺序，如pos(1,1)=0; pos(2,3)=9*(2-1)+(3-1)=11;
//当pos为-1时，是启动递归程序计算数独
int input(intu (*array)[9]);
//单字符模式输入数独，格式没有要求，会自动忽略所有非数字，数字数量大于81时自动结束

int print(intu (*array)[9]);
//打印数独数组

int copyArray(intu (*array)[9],intu (*copy)[9]);
//复制数组的副本

int isIllegal(intu (*array)[9],intu x,intu y,intu num );
//验证在(x,y)位置放置num是否可行，不可行则返回1，可行则返回0

static long countOfPlace=0;     //计数器，记录place函数执行次数
static long countOfPrint=0;     //记录print函数执行次数
static long countOfResult=0;    //记录已经计算出来的结果数
int main()
{
    clock_t start,stop;
    intu a[9][9];
    input(a);
    print(a);
    start=clock();//记录开始时间
    {

        int i;
        for(i=1; i<=RUNTIMES; i++)//重复多次执行数独计算，统计所耗时间的平均值
        {
            place(a,-1,0);
            //这才是核心！！pos=-1,启动计算数独数组a,num数值不影响
        }
    }
    stop=clock();//记录结束时间
    long totalTime=(stop-start)/CLOCKS_PER_SEC;
    printf("totalTime= %f second\n",totalTime/RUNTIMES);
    printf("CountOfPlace=%ld\n",countOfPlace);
    //getch();
    return 0;
}

int copyArray(intu (*array)[9],intu (*copy)[9])
{
    intu *a=(intu *)array,*c=(intu *)copy;
    int i;
    for(i=0; i<81; i++)
    {
        *c=*a;
        c++;
        a++;
    }
    return 0;
}

int input(intu (*array)[9])
{
    intu *a=(intu *)array;
    char c;//采用单字符模式输入，变量 c临时存储输入的字符
    int i;
    for(i=1; i<=81; i++)
    {
        do
        {
            scanf("%c",&c);
        }
        while(c<'0'|| c>'9');
    //如果输入的那个字符不是数字就把下一个赋值给c，直到c是数字
    //上面的循环的作用也就是跳过所有非数字，包括空格，回车等。

        *a=c-48;    //把数值写入到数组中
        a++;

    }
    return 0;
}
int print(intu (*array)[9])
{
    countOfPrint++;
    intu *a=(intu *)array;
    printf("\n");
    printf("PrintCount=%ld\n",countOfPrint);
    printf("ResultCount=%ld\n",countOfResult );
    int i;
    for(i=1; i<=81; i++)
    {
        printf("%2d",*a);
        a++;
        if(i%9==0) printf("\n");
    }
    return 0;
}
int isIllegal(intu (*array)[9],intu x,intu y,intu num )
{
    intu i,j;
    intu *a=(intu*)array;
    for(i=1; i<=9; i++)
    {
        for(j=1; j<=9; j++)
        {
            //循环i，j  ，得到的指针a指向(i,j)元素
            //当（x为i 或者 y为i 或者(i,j)在(x,y)所在的九宫格）并且(i,j)不是(x,y)点时，为直接影响放置元素合法性的位置
            if (!(x==i&&j==y) && (x==i || j==y|| ( (x-1)/3==(i-1)/3 && (y-1)/3==(j-1)/3 )))
            {
                //如果在以上区域已经存在该数字，则返回非法1
                if(*a==num) return 1;
            }
            a++;
        }
    }
    //不存在非法，返回合法0
    return 0;
}

int place(intu (*array)[9],short int pos,intu num )
/*  1.在pos位置放置num
    2.将pos移动到下一个空白，
      如果pos超界则表示已经求出结果
    3.没有超界就判断1-9在当前位置的合理性
        如果合理就调用place进行下一轮递归
*/

{
    countOfPlace++;         //函数运行次数计数器，调试用，可以不理睬
    intu copy[9][9];        //定义一个数组存储数独副本
    intu * c=(intu* )copy;  //一个指针指向副本数组起始元素，操作方便
    copyArray(array,copy);  //复制原始数组到副本数组里
    if(pos<0) countOfResult=0;  //pos为-1表示初始化，把解的数量设置为零
    if(pos>=0 ) *(c+pos)=num;   //pos>=0是合法的，在pos位置放置数字num
    if(countOfResult>=MAXRESULT) return 0;  //如果求得解的数量已经符合要求，那么不用继续执行了

    //下面的do while循环是使pos指向下一个为0的元素
    do
    {
        pos++;

        if(pos>80)      //pos最大值为80，若大于80则说明已经求得了一个结果
        {
            countOfResult++;    //结果数量计数器
            print(copy);        //打印结果
            return 0;
        }
    }
    while( *(c+pos));

    intu n,x,y;     //n表示在下个位置要放的数字
    for(n=1; n<=9; n++)
    {
        x=pos/9+1;  //求得pos对应的行号x,列号y
        y=pos%9+1;
        if(!isIllegal(copy,x,y,n))  //如果在下个位置可以放置数字n
            place(copy,pos,n);      //那么调用place函数放置n,并开始新一轮的递归
    }
    return -1;
}