/**
 * @Author: Your name
 * @Create Time: 2023-11-07 09:28:32
 * @Modified by: Your name
 * @Modified time: 2023-11-07 09:49:54
 * @Description:  ������Ԫ��ʵ��ϡ�����ļӷ�
 */

/*
˼·
1��������Ԫ��ṹ��
2��������Ԫ��˳���ṹ��
3��ʵ����Ԫ��ļӷ�
*/

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
    int maxSize;                                                  //����Ԫ������
    int row,col,num;                                              //������к��У�����Ԫ����
    
};
