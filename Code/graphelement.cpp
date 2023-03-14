#include "graphelement.h"
//#include "diagramitem.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
#include"idpool.h"

//int GraphElement::maxid = 0;



GraphElement::GraphElement()
{
//    Id = ++maxid;
     this->setId();
     this->setsId();
}
void GraphElement::setId(){
    for(int i=0;i<200;i++){
        if(k1[i]==0){
            this->Id=i+1;
            k1[i]=1;
            break;
            //为0的时候表示ID未被占用，为1的时候表示已经被占用
        }
    }
}


int GraphElement::GetID(){
    return this->Id;

}

QString GraphElement::getIdNum(int num)
{
    if(num == 0)
        return "0x0";

    QString res;
    QString hex[16] = {"0", "1", "2", "3", "4", "5", "6", "7",
                      "8", "9", "a", "b", "c", "d", "e", "f"};

    unsigned int num2 = num;//无论正负，全部转换成无符号整型
    while(num2)
    {
        res = hex[num2 % 16] + res;//取余即是最低位
        num2 /= 16;
    }
    return "0x"+res;
}//得到ID的16进制表示的字符串
void GraphElement::deleteID()
{
   k1[this->Id-1]=0;
   return ;
}
int GraphElement::CStringHexToInt(QString str)
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
    return nRet;
}//利用ID字符串转成int值
bool GraphElement::isRepeat(QString str){
    int nRet=CStringHexToInt(str);
    if(k1[nRet-1]==1){
            return true;
        }else return false;
}
bool GraphElement::changesId(QString str){
    if(isRepeat(str)){
        return false;
        //用户输入的ID已经分配 0x111 8987
    }
    else if(!str.startsWith("0x")){
        return false;
    }//未以0x开头，命名不规范
    k1[this->GetID()-1]=0;
    this->sId=str;
    this->Id=CStringHexToInt(str);
    k1[this->GetID()-1]=1;
    return true;
}
int GraphElement::chagearrowID(int oldid){
    k1[oldid-1]=1;
    return true;
}
