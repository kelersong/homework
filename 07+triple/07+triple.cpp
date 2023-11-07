/**
 * @Author: Your name
 * @Create Time: 2023-11-07 09:28:32
 * @Modified by: Your name
 * @Modified time: 2023-11-07 17:34:12
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
void AddTriple(const Triple &a,Triple &b);                                         //��aΪģ�棬������Ԫ������b
int Is_Left(const Triple &a,const Triple &b);                                      //�ж�ab�ھ����е�λ�ã�a���󷵻�1 ���ҷ���-1 ��ͬ����0
void initTriSparseMatrix(TriSparseMatrix &s);                              //���ذ汾
void CopyTriple(const Triple &a,Triple &b);


//������
int main(){
    using std::cout;
    using std::cin;
    using std::endl;
    cout << "input the row col n1 and n2 : \n";
    int row,col,n1,n2;
    cin >> row >>col >>n1 >>n2;                                                     //�Ӽ������������Ϣ
    // ��ʼ������
    TriSparseMatrix matrix_a,matrix_b;
    initTriSparseMatrix(matrix_a,row,col,n1);
    initTriSparseMatrix(matrix_b,row,col,n2);
    
    // ʵ�־���ļӷ�
    TriSparseMatrix matrix_c;
    initTriSparseMatrix(matrix_c);
    AddTriMatrix(matrix_a,matrix_b,matrix_c);
    // ����õ��ľ���
    ShowMatrix(matrix_c);
    system("pause");
    return 0;
}


//����ʵ��
void initTriSparseMatrix(TriSparseMatrix &s,int row,int col,int num){
    using std::cout;
    using std::cin;
    using std::endl;
    s.triElems = new Triple[s.num];                                       //����ռ�
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
    using std::cout;
    using std::endl;
    // ���������������Ԫ���б������Ԫ�أ�����Ԫ��Ե���ʽ
    for(int i = 0;i<s.num;i++){
        //ѭ������
        cout << "(" << s.triElems[i].row << "," <<s.triElems[i].col << ","  << s.triElems[i].value <<")" <<endl;
    }
}

void AddTriMatrix(const TriSparseMatrix &a, const TriSparseMatrix &b, TriSparseMatrix &c){
    // ������� ��ʵ��������Ԫ��������ӣ����Ϊ����c
    c.row = a.row;
    c.col = a.col;
    c.num = 0;
    Triple* ptr_a = a.triElems;
    Triple* ptr_b = b.triElems;
    Triple* ptr_c = c.triElems;
    while((ptr_a-a.triElems < a.num) &&( ptr_b-b.triElems <b.num)){ 
        //�ж��Ⱥ�
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
        //a����l
        while(ptr_b-b.triElems < b.num){
            CopyTriple(*ptr_b,*ptr_c);
            ptr_b++;
            ptr_c++;
        }
    }
    
    if(ptr_b-b.triElems > b.num){
        //b����l
        while(ptr_a-a.triElems < a.num){
            CopyTriple(*ptr_a,*ptr_c);
            ptr_a++;
            ptr_c++;
        }
    }

    
    
}

void AddTriple(const Triple &a, Triple &b){
    //������� ����a��ֵ���ӵ�
    b.row = a.row;
    b.col = a.col;
    b.value+=a.value;
    
    
    
    
}

int Is_Left(const Triple &a, const Triple &b){
    // ���������a���󣺷���1 a���ң�����-1 a��bλ����ͬ ����0
    
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
    //�վ���
    
    s.triElems = new Triple[s.maxSize];
}

void CopyTriple(const Triple &a, Triple &b){
    b.col = a.col;
    b.row = a.row;
    b.value = a.value;
}