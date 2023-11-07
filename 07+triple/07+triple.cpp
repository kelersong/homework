/**
 * @Author: Your name
 * @Create Time: 2023-11-07 09:28:32
 * @Modified by: Your name
 * @Modified time: 2023-11-07 13:30:05
 * @Description:  利用三元组实现稀疏矩阵的加法
 */

/*
思路
1、定义三元组结构体
2、定义三元组顺序表结构体
3、实现三元组的加法
*/
#include <iostream>
//定义三元组结构体
#define ElemType int
struct Triple{
    // 数据成员
    int row,col;                                                 //行和列
    ElemType value;                                              //值
};

//定义三元组顺序表
struct TriSparseMatrix{
    //数据成员
    Triple *triElems;                                             //存放三元组顺序表
    int maxSize = 1024;                                           //矩阵的最大非零元个数
    int row,col,num;                                              //矩阵的行和列，非零元个数
    
};


void initTriSparseMatrix(TriSparseMatrix &s,int row,int col,int num);               //三元组矩阵列表的初始化
void ShowMatrix(const TriSparseMatrix &s);                                          //输出三元组列表
void AddTriMatrix(const TriSparseMatrix &a,const TriSparseMatrix &b, TriSparseMatrix &c);       //矩阵的加法

//主程序
int main(){
    using std::cout;
    using std::cin;
    using std::endl;
    cout << "input the row col n1 and n2";
    int row,col,n1,n2;
    cin >> row >>col >>n1 >>n2;                                                     //从键盘输入基本信息
    // 初始化矩阵
    TriSparseMatrix matrix_a,matrix_b;
    initTriSparseMatrix(matrix_a,row,col,n1);
    initTriSparseMatrix(matrix_b,row,col,n2);
    // 实现矩阵的加法
    TriSparseMatrix matrix_c;
    AddTriMatrix(matrix_a,matrix_b,matrix_c);
    // 输出得到的矩阵
    ShowMatrix(matrix_c);
    return 0;
}


//函数实现
void initTriSparseMatrix(TriSparseMatrix &s,int row,int col,int num){
    using std::cout;
    using std::cin;
    using std::endl;
    s.triElems = new Triple[s.maxSize];                                       //分配空间
    s.col = col;
    s.row = row;
    s.num = num;
    cout << "input the element" <<endl;
    for(int i=0;i<num;i++){
        //初始化每一个三元组
        cin >> s.triElems[i].row;                                             //初始化行
        cin >> s.triElems[i].col;                                             //初始化列号
        cin >> s.triElems[i].value;                                           //初始化值
    }
    
    
    
}

void ShowMatrix(const TriSparseMatrix &s){
    // 操作结果：给定三元组列表输出其元素，以三元组对的形式
}

void AddTriMatrix(const TriSparseMatrix &a, const TriSparseMatrix &b, TriSparseMatrix &c){
    // 操作结果 ：实现两个三元组矩阵的相加，结果为矩阵c
}