/**
 * @Author: tao
 * @Create Time: 2023-11-09 16:07:12
 * @Modified by: Your name
 * @Modified time: 2023-11-11 01:10:55
 * @Description: 二叉树建树、二叉树中序遍历(非递归)、二叉树删除，结点父结点求解，结点兄弟结点求解
 */
#include <iostream>
#define STACKSIZE 128
typedef char ElemType;
using std::cout;
using std::cin;
using std::endl;


//节点结构
typedef struct BinNode{
    //数据成员
    ElemType data;                        //存放数据成分
    BinNode* lchild;                      //存放左孩子指针
    BinNode* rchild;                      //存放右孩子指针
}*BinPtr;

//函数声明
void CreateBinTree(BinNode* &T);
void InOrder(BinNode* T,void (*visit)(BinNode* node));
void show(BinNode* node);
BinPtr FindNode(BinPtr T,const ElemType &elem);
void DeleteNode(BinPtr &T, const ElemType &elem);
BinPtr FindFatherNode(BinPtr T,const ElemType &elem);





struct Stack{
    //数据成员：
    BinPtr* base;                                       //栈的基地指针
    BinPtr* top;                                        //栈顶指针，动态变化
   };
   
   //函数声明
   void InitStack(Stack &S);                              //初始化栈，分配空间
   bool Empty(const Stack &S);                            //判断栈是否为空
   bool Push(Stack &S, BinPtr &elem);              //入栈
   bool Pop(Stack &S);                                    //弹栈
   ElemType GetTop(const Stack &S,BinPtr &elem);        //返回栈顶元素，用elem接收
   

   

// 主程序
int main(){
    //1、根据先序序列创建一个二叉树
    BinNode* T;                            //创建一个根节点
    cout << "input the pre :" <<endl;
    CreateBinTree(T);
    //2、中序遍历，非递归方式
    InOrder(T,show);
    cout <<endl;
    
    //4、求节点的兄弟结点和双亲结点
    ElemType elem;
    cout << "input element searched :" <<endl;
    cin >> elem;
    BinPtr p;
    p = FindFatherNode(T,elem);
    if(p){
        cout << "Father :"<< p->data <<endl;
       if(p->lchild){
          if(p->lchild->data == elem){
              if(p->rchild){
                cout << "Brother : " <<p->rchild <<endl;
              }
             }
       }
       if(p->rchild){
        if(p->rchild->data==elem){
           if(p->lchild){
            cout << "Brother : " <<p->lchild->data <<endl;
           }
       }
           
       }
       if(!p->lchild || !p->rchild){
        cout<< "NO Brother " <<endl;
       }
    }
    if(!p){
        cout << "NO FatherNode" <<endl;
        cout << "NO BrotherNode" <<endl;
    } 
    
    //3、二叉树删除
    
    cout << "input element deleted :" <<endl;
    cin >> elem;
    DeleteNode(T,elem);
    InOrder(T,show);
    cout << endl;
    
    
    system("pause");
    return 0;
}



// 函数实现
void CreateBinTree(BinNode *&T){
    // 操作结果 ：根据先序序列创建一个二叉树

    ElemType ch;
    
    cin >> ch;
    if(ch == '#') T = NULL;
    else{
        T = (BinNode*)malloc(sizeof(BinNode));
        T->data = ch;
        CreateBinTree(T->lchild);
        CreateBinTree(T->rchild);
    }
}

void InOrder(BinNode *T, void (*visit)(BinNode *node)){
    // 中序遍历，非递归
    /*
    思路：
    1、非递归要使用栈
    2、当节点的左孩子存在时，将他的左孩子入栈
    3、当节点的左孩子不存在时，访问当前节点
    4、将该节点的右孩子入栈
    5、直到将二叉树遍历完全并且栈为空
    */
   

   //遍历函数
   Stack s;
   InitStack(s);
   BinNode* q = T;                                             //用于遍历二叉树
   while((q!=NULL) || (!Empty(s))){
     while(q!=NULL){
        //当左孩子存在时，入栈
        Push(s,q);
        q = q->lchild;
     }
     if(!Empty(s)){
        //当左孩子不存在，且栈非空
        GetTop(s,q);                                           //取出栈顶元素
        visit(q);                                              //访问栈顶元素
        Pop(s);                                                //将栈顶元素弹出
        q = q->rchild;                                         //遍历右孩子分支

     }
   }

   

}

void show(BinNode *node){
    //在遍历中，对每个元素进行操作
    cout << node->data; 
}

// 栈函数实现
void InitStack(Stack &S){
    //操作结果，初始化一个栈
    S.base =(BinPtr*)malloc(STACKSIZE*sizeof(BinPtr));                   //开辟一块内存
    if(S.base == NULL) cout<<"内存申请失败"<<endl;                               //内存申请失败
    S.top = S.base;                                                              //初始时 top与base重合
    
}

bool Empty(const Stack &S){
    if(S.base == S.top) return true;
    else return false;
}


bool Push(Stack &S,  BinPtr &elem){
    
    *S.top= elem;
    S.top++;
    return true;
}

bool Pop(Stack &S){
    
    S.top--;
    return true;
}

ElemType GetTop(const Stack &S, BinPtr &elem){
    //操作结果 ：将顺序栈的栈顶元素返回给elem
    if(S.top == S.base){
        return false;
    }
    elem = *(S.top-1);
    return true;
}

BinPtr FindNode(BinPtr T, const ElemType &elem){
    BinPtr p = NULL;
    if(T==NULL) return NULL;
    else if(T->data == elem) return T;
    else{
        p = FindNode(T->lchild,elem);
        if(p == NULL){
            //说明在左分支中没有找到
            return FindNode(T->rchild,elem);
        }
        else{
            return p;
        }
    }
}

void DeleteNode(BinPtr &T,  const ElemType &elem){
    
    BinPtr p = FindFatherNode(T,elem);
    if(p->lchild->data == elem) p->lchild = NULL;
    if(p->rchild->data == elem) p->rchild = NULL;
}

BinPtr FindFatherNode(BinPtr T, const ElemType &elem){
    BinPtr p = NULL;
    if(T==NULL) return NULL;
    if(T->lchild){
        if(T->lchild->data == elem){
            return T;
        }
    }
    if(T->rchild){
        if(T->rchild->data == elem){
            return T;
        }
    }
   
    p = FindFatherNode(T->lchild,elem);
    if(p == NULL){
        //说明在左分支中没有找到
        return FindFatherNode(T->rchild,elem);
    }
    else{
        return p;
    }
    
    
}