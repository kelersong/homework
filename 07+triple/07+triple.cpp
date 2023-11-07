/**
 * @Author: Your name
 * @Create Time: 2023-11-07 09:28:32
 * @Modified by: Your name
 * @Modified time: 2023-11-07 13:30:05
 * @Description:  ������Ԫ��ʵ��ϡ�����ļӷ�
 */

/*
˼·
1��������Ԫ��ṹ��
2��������Ԫ��˳���ṹ��
3��ʵ����Ԫ��ļӷ�
*/
#include <iostream>
//������Ԫ��ṹ��
#define ElemType int
struct Triple{
    // ���ݳ�Ա
    int row,col;                                                 //�к���
    ElemType value;                                              //ֵ
};

//������Ԫ��˳���
struct TriSparseMatrix{
    //���ݳ�Ա
    Triple *triElems;                                             //�����Ԫ��˳���
    int maxSize = 1024;                                           //�����������Ԫ����
    int row,col,num;                                              //������к��У�����Ԫ����
    
};


void initTriSparseMatrix(TriSparseMatrix &s,int row,int col,int num);               //��Ԫ������б�ĳ�ʼ��
void ShowMatrix(const TriSparseMatrix &s);                                          //�����Ԫ���б�
void AddTriMatrix(const TriSparseMatrix &a,const TriSparseMatrix &b, TriSparseMatrix &c);       //����ļӷ�

//������
int main(){
    using std::cout;
    using std::cin;
    using std::endl;
    cout << "input the row col n1 and n2";
    int row,col,n1,n2;
    cin >> row >>col >>n1 >>n2;                                                     //�Ӽ������������Ϣ
    // ��ʼ������
    TriSparseMatrix matrix_a,matrix_b;
    initTriSparseMatrix(matrix_a,row,col,n1);
    initTriSparseMatrix(matrix_b,row,col,n2);
    // ʵ�־���ļӷ�
    TriSparseMatrix matrix_c;
    AddTriMatrix(matrix_a,matrix_b,matrix_c);
    // ����õ��ľ���
    ShowMatrix(matrix_c);
    return 0;
}


//����ʵ��
void initTriSparseMatrix(TriSparseMatrix &s,int row,int col,int num){
    using std::cout;
    using std::cin;
    using std::endl;
    s.triElems = new Triple[s.maxSize];                                       //����ռ�
    s.col = col;
    s.row = row;
    s.num = num;
    cout << "input the element" <<endl;
    for(int i=0;i<num;i++){
        //��ʼ��ÿһ����Ԫ��
        cin >> s.triElems[i].row;                                             //��ʼ����
        cin >> s.triElems[i].col;                                             //��ʼ���к�
        cin >> s.triElems[i].value;                                           //��ʼ��ֵ
    }
    
    
    
}

void ShowMatrix(const TriSparseMatrix &s){
    // ���������������Ԫ���б������Ԫ�أ�����Ԫ��Ե���ʽ
}

void AddTriMatrix(const TriSparseMatrix &a, const TriSparseMatrix &b, TriSparseMatrix &c){
    // ������� ��ʵ��������Ԫ��������ӣ����Ϊ����c
}