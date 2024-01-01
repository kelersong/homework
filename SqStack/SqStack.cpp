/**
 * @Author: 程涛
 * @Create Time: 2023-10-09 19:47:22
 * @Modified by: Your name
 * @Modified time: 2023-10-09 21:24:36
 * @Description:  顺序栈的类方法具体实现
 */

#include "SqStack.h"
#include <iostream>

template<class ElemType> SqStack<ElemType>::SqStack(int size){
    //操作结果：创建一个顺序栈
    maxsize = size;
    base = (ElemType*)malloc(maxsize*sizeof(ElemType));                //分配存储空间
    if(base == NULL) exit(1);                                   //存储空间申请失败
    top = base;                                                        //初始情况 top和base相同
    
}

template<class ElemType> SqStack<ElemType>::~SqStack(){
    //操作结果：销毁栈
    free(base);                                                         //释放空间
    base = NULL;
    top = NULL;                                                         
    
}

template<class ElemType> void SqStack<ElemType>::Clear(){
    //操作结果：清空栈
    top = base;                                                        //清空栈中的所有元素
}

template<class ElemType> bool SqStack<ElemType>::Top(ElemType &e) const{
    //操作结果：将栈顶的元素返回给e
    if(Empty()) return false;                                          //栈为空，返回false
    else{
        e = *(top-1);                                                  //将栈顶元素赋值给e
        return true;
    }
}

template<class ElemType> int SqStack<ElemType>::Length() const{
    // 操作结果：返回栈的元素个数
    return (top-base)/sizeof(ElemType);
}

template<class ElemType> bool SqStack<ElemType>::Empty(){
    //操作结果 ：如果栈为空，则返回true
    return top == base;                                                //top与base相等则栈为空                               
}

template<class ElemType> bool SqStack<ElemType>::Push(const ElemType &e){
    //操作结果：在栈顶插入一个元素
    
}

