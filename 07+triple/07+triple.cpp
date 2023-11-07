/**
 * @Author: Your name
 * @Create Time: 2023-11-07 09:28:32
 * @Modified by: Your name
 * @Modified time: 2023-11-07 17:34:12
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
void AddTriple(const Triple &a,Triple &b);                                         //以a为模版，复制三元组生成b
int Is_Left(const Triple &a,const Triple &b);                                      //判断ab在矩阵中的位置，a在左返回1 在右返回-1 相同返回0
void initTriSparseMatrix(TriSparseMatrix &s);                              //重载版本
void CopyTriple(const Triple &a,Triple &b);


//主程序
int main(){
    using std::cout;
    using std::cin;
    using std::endl;
    cout << "input the row col n1 and n2 : \n";
    int row,col,n1,n2;
    cin >> row >>col >>n1 >>n2;                                                     //从键盘输入基本信息
    // 初始化矩阵
    TriSparseMatrix matrix_a,matrix_b;
    initTriSparseMatrix(matrix_a,row,col,n1);
    initTriSparseMatrix(matrix_b,row,col,n2);
    
    // 实现矩阵的加法
    TriSparseMatrix matrix_c;
    initTriSparseMatrix(matrix_c);
    AddTriMatrix(matrix_a,matrix_b,matrix_c);
    // 输出得到的矩阵
    ShowMatrix(matrix_c);
    system("pause");
    return 0;
}


//函数实现
void initTriSparseMatrix(TriSparseMatrix &s,int row,int col,int num){
    using std::cout;
    using std::cin;
    using std::endl;
    s.triElems = new Triple[s.num];                                       //分配空间
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
    using std::cout;
    using std::endl;
    // 操作结果：给定三元组列表输出其元素，以三元组对的形式
    for(int i = 0;i<s.num;i++){
        //循环遍历
        cout << "(" << s.triElems[i].row << "," <<s.triElems[i].col << ","  << s.triElems[i].value <<")" <<endl;
    }
}

void AddTriMatrix(const TriSparseMatrix &a, const TriSparseMatrix &b, TriSparseMatrix &c){
    // 操作结果 ：实现两个三元组矩阵的相加，结果为矩阵c
    c.row = a.row;
    c.col = a.col;
    c.num = 0;
    Triple* ptr_a = a.triElems;
    Triple* ptr_b = b.triElems;
    Triple* ptr_c = c.triElems;
    while((ptr_a-a.triElems < a.num) &&( ptr_b-b.triElems <b.num)){ 
        //判断先后
        if(Is_Left(*ptr_a,*ptr_b)>0){
            CopyTriple(*ptr_a,*ptr_c);
            c.num++;
            ptr_a++;
            ptr_c++;
            
        }
        if(Is_Left(*ptr_a,*ptr_b)<0){
            CopyTriple(*ptr_b,*ptr_c);
            c.num++;
            ptr_b++;
            ptr_c++;
            
        }
        if(Is_Left(*ptr_a,*ptr_b)==0){
            CopyTriple(*ptr_b,*ptr_c);
            AddTriple(*ptr_a,*ptr_c);
            c.num++;
            ptr_a++;
            ptr_b++;
            ptr_c++;
            
        }
    }
    if(ptr_a-a.triElems > a.num){
        //a走完l
        while(ptr_b-b.triElems < b.num){
            CopyTriple(*ptr_b,*ptr_c);
            ptr_b++;
            ptr_c++;
        }
    }
    
    if(ptr_b-b.triElems > b.num){
        //b走完l
        while(ptr_a-a.triElems < a.num){
            CopyTriple(*ptr_a,*ptr_c);
            ptr_a++;
            ptr_c++;
        }
    }

    
    
}

void AddTriple(const Triple &a, Triple &b){
    //操作结果 ：将a的值增加到
    b.row = a.row;
    b.col = a.col;
    b.value+=a.value;
    
    
    
    
}

int Is_Left(const Triple &a, const Triple &b){
    // 操作结果：a在左：返回1 a在右：返回-1 a和b位置相同 返回0
    
    if(a.row < b.row){
        return 1;
    }
    if(a.row > b.row){
        return -1;
    }
    if(a.row == b.row){
        if(a.col<b.col) return 1; 
        if(a.col==b.col) return 0; 
        if(a.col>b.col) return -1; 
    }
    return false;
}
void initTriSparseMatrix(TriSparseMatrix &s){
    //空矩阵
    
    s.triElems = new Triple[s.maxSize];
}

void CopyTriple(const Triple &a, Triple &b){
    b.col = a.col;
    b.row = a.row;
    b.value = a.value;
}