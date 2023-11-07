/**
 * @Author: Your name
 * @Create Time: 2023-11-07 09:28:32
 * @Modified by: Your name
 * @Modified time: 2023-11-07 09:49:54
 * @Description:  利用三元组实现稀疏矩阵的加法
 */

/*
思路
1、定义三元组结构体
2、定义三元组顺序表结构体
3、实现三元组的加法
*/

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
    int maxSize;                                                  //非零元最大个数
    int row,col,num;                                              //矩阵的行和列，非零元个数
    
};
