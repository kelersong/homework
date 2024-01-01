#include "sqlist.h"
#include <iostream>
using namespace std;

template<class ElemType>
 SqList<ElemType>::~SqList()
{
    std::cout<<"inite"<<endl;

}

template<class ElemType>
SqList<ElemType>::SqList(int size)
{
    

}

int main()
{
    SqList<int> mylist(10);
    system("pause");
    return 0;
}



