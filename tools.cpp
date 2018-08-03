#include "tools.h"
#include <stdlib.h>

using namespace std;
//const int SIZE_CHAR = 32; //生成32 + 1位C Style字符串
//const char CCH[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
//int main()
//{
//    srand((unsigned)time(NULL));
//   char ch[SIZE_CHAR + 1] = {0};
//   for (int i = 0; i < SIZE_CHAR; ++i)
//   {
//         //int x = rand() % (sizeof(CCH) - 1); //这个方法不好, 因为许多随机数发生器的低位比特并不随机,

////RAND MAX 在ANSI 里#define 在<stdlib.h>

////RAND MAX 是个常数, 它告诉你C 库函数rand() 的固定范围。

////不可以设RAND MAX 为其它的值, 也没有办法要求rand() 返回其它范围的值。

//       int x = rand() / (RAND_MAX / (sizeof(CCH) - 1));

//         ch[i] = CCH[x];
//   }
//   cout <<ch <<"\n";
//    return 0;
//}
