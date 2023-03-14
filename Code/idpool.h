#ifndef IDPOOL_H
#define IDPOOL_H
#include<QString>
static int k1[200]={0};//图形的ID池
static int k2[200]={0};//流程图的ID池
static int CStringHexToInt(QString str) //输入十六进制的ID字符串，如Ox6、Oxa这样
{
    int nRet = 0;
    int count = 1;
    for (int i = str.length() - 1; i >= 0; --i)
    {
        int nNum = 0;
        char chTest;
        chTest = str.at(i).unicode();
        if (chTest >= '0' && chTest <= '9')
        {
            char a='0';
            nNum = chTest - a;
        }
        else if (chTest >= 'A' && chTest <= 'F')
        {
            nNum = chTest - 'A' + 10;
        }
        else if (chTest >= 'a' && chTest <= 'f')
        {
            nNum = chTest - 'a' + 10;
        }
        nRet += nNum * count;
        count *= 16;
    }
    return nRet;//返回由十六进制ID字符串转化来的int型十进制ID；
}//利用ID字符串转成int值

static bool isRepeat(QString str){
    int nRet=CStringHexToInt(str);
    if(k1[nRet-1]==1){   //检测该id在id池当中是否已被占用，为1是已被占用，为0时未被占用
            return true;
        }else return false;
}
static bool isNorm(QString str){
    if(str.startsWith("0x")){   //检测该id命名是否规范
            return true;
        }else return false;
}
#endif // IDPOOL_H
