/**
 * @Author: 程涛
 * @Create Time: 2023-10-10 14:20:10
 * @Modified by: Your name
 * @Modified time: 2023-10-10 19:54:11
 * @Description:变形题（线性表）
输入一个整数n，再输入n个整数，按照输入的顺序建立单链表，并遍历所建立的单链表，输出这些数据。
输入格式:
假定输入的测试数据有两组，每组测试输入一个整数n，再输入n个整数。
输出格式:
（1）对于每组测试，按照输入次序输出链表中各结点数据域的值（数据之间留一个空格）。
（2）对任意一个链表，删除数据值相同的结点。（时间复杂度O(n)）
（3）检查两个链表是否为有序链表，若无序，则按递增顺序排序。
（4）将两个递增链表合并为一个递减链表，合并过程中删除值相同的结点。
输入样例:
5 1 2 3 4 5
7 9 3 2 4 7 8 6
（1）输出样例:
5 4 3 2 1
6 8 7 4 2 3 9
（2）输出样例：
5 4 3 2 1
6 8 7 4 2 3 9
（3）输出样例：
1 2 3 4 5
2 3 4 6 7 8 9
（4）输出样例：
9 8 7 6 5 4 3 2 1
 */


#include "..\homework_by_node\linklist.cpp"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(){
    //1、载入数据
    void Load_Data(SimpleLinkList<double> &link);                            //声明载入数据函数
    SimpleLinkList<double> link_1;                                           //定义一个链表对象
    SimpleLinkList<double> link_2;
    Load_Data(link_1);                                                       // 载入数据
    Load_Data(link_2); 

    //2、遍历数据
    void show(const double &e);                                              //定义一个遍历操作函数
    link_1.Traverse(show);                                                   //遍历输出
    cout << endl;
    link_2.Traverse(show);
    cout <<endl;

    //3、排序
    
    link_1.Sort();
    link_2.Sort();
    cout<< "sort over" <<endl;
    link_1.Traverse(show);                                                   //遍历输出
    cout << endl;
    link_2.Traverse(show);
    cout <<endl;

    //4、删除重复元素
    link_1.Delete_repeat_new();
    link_2.Delete_repeat_new();
    cout<< "delete over" <<endl;
    link_1.Traverse(show);                                                   //遍历输出
    cout << endl;
    link_2.Traverse(show);
    cout <<endl;

    //5、将两个递增链表合成一个递减链表，同时删除重复元素
    
    void ComPound( SimpleLinkList<double> &link_1,  SimpleLinkList<double> &link_2,SimpleLinkList<double> &link_3);
    SimpleLinkList<double> link_3;
    ComPound(link_1,link_2,link_3);
    cout << "compound over" <<endl;
    link_3.Traverse(show);                                                   //遍历输出
    cout << endl;
    
    
    system("pause");
    return 0;
}

void Load_Data(SimpleLinkList<double> &link){
    cout <<"input the number of elements" <<endl;
    int n;                                                          //存储要输入元素的数量
    cin >> n;                                                       //从键盘上读取n
    double temElem;                                                 //临时变量，存储输入的元素                                   
    for(int i = 0;i<n;i++){
        //循环输入
        cin >> temElem;
        link.Insert(1,temElem);
        
    }
    cout <<"over" <<endl;
}

void show(const double &e){
    cout << e <<" ";
}

void ComPound( SimpleLinkList<double> &link_1,  SimpleLinkList<double> &link_2,SimpleLinkList<double> &link_3){
    //操作结果：将两个链表，降序合并
    link_1.local_reverse();
    link_2.local_reverse();

                                                                                       
    Node<double> *temPtr1 = link_1.head->next;                                          //用于遍历第一个链表
    Node<double> *temPtr2 = link_2.head->next;                                          //用于 遍历第二个链表
    Node<double> * cur = link_3.head;
    while(temPtr1 != NULL && temPtr2 != NULL){
        if(temPtr1->data > temPtr2->data){
            cur->next = temPtr1;
            temPtr1 = temPtr1->next;
            cur = cur->next;
        }
        else if(temPtr1->data == temPtr2->data){
            cur->next = temPtr1;
            temPtr1 = temPtr1->next;
            temPtr2 = temPtr2->next;
            cur = cur->next;
        }
        else{
            cur->next = temPtr2;
            temPtr2 = temPtr2->next;
            cur = cur->next;
        }
    }
    if(temPtr1 ==NULL){
        cur->next= temPtr2;
    }

    if(temPtr2 == NULL){
        cur->next= temPtr1;
    }

    temPtr1 = NULL;
    temPtr2 = NULL;
    cur = NULL;
    link_1.head ->next =  NULL;
    link_2.head ->next =  NULL;
    
    

}