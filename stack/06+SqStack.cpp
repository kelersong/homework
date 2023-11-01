/**
 * @Author: tao
 * @Create Time: 2023-10-11 15:56:20
 * @Modified by: Your name
 * @Modified time: 2023-10-31 18:43:19
 * @Description: 用栈实现运算器
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#define ElemType double
#define STACKINITSIZE 256
#define STACKINITCREMENT 128
//定义栈结构体
typedef struct SqStack{
    ElemType *base;                                    //动态存储空间的基地址，作为栈底
    ElemType *top;                                     //栈顶指针，指向真实栈顶的下一个元素
    int stacksize;                                     //记录当前以分配内存空间的大小
}SqStack;                                             

//声明函数方法
void InitStack(SqStack &S);                            //初始化栈
void DestroyStack(SqStack &S);                         //销毁栈
void ClearStack(SqStack &S);                           //清空栈
bool GetTop(const SqStack &S,ElemType &e);             //返回栈顶的元素
bool Push(SqStack &S,const ElemType &e);               //压栈
bool Pop(SqStack &S,ElemType &e);                      //弹栈，将值赋给e
bool Pop(SqStack &S);                                  //弹栈不赋值


//实现表达式计算器

/*
思路：
1、准备两个栈OPERAND存放操作数 OPERATOR存放操作符,准备一个字符串数组存放表达式
2、核心思路：操作符优先级大于站内优先级压栈，操作符优先级小于等于站内优先级弹栈
3、准备一个枚举，定义各符号的优先级 其中左括号的优先级在压栈和弹栈时不一样。
*/

//函数原型声明
void CalculateExpression(char* str,double &result);
bool isDigit(char i);                                                    //用于判断是否为数字
void GetNumber(char c,double &data);                                      //用于将字符串转化为double
int GetPriority(char c);                                                 //用于获取运算符的优先级
double Operate(const double &a,char c,const double &b);                  //对两个数进行运算

int main(){
    //1、将表达式放入字符串数组中
    cout << "please input the expression end with '#': " <<endl;
    char str[1024] = {0};                                                   //用于存放表达式
    cin>>str;                                                               //传入表达式
    //检测用户是否忘记输入#
    int count;                                                              //存储字符串的数量
    while (str[count])
    {
        count++;
    }
    if(str[count-1] != '#'){
        //如果字符串末尾不是#，自动添加#
        str[count] = '#';
    }
    
    double result;                                                         //存储运算的结果
    CalculateExpression(str,result);                                       //调用计算表达式计算函数
    cout <<result <<endl; 
    system("pause");
    return 0;
}









// 函数实现
void CalculateExpression(char* str,double &result){
    //操作结果 ：将计算的结果赋给result 
    //2、初始化结构体对象
    SqStack OPERAND;                                                        //存放操作数
    SqStack OPERATOR;                                                       //存放操作符
    InitStack(OPERAND);
    InitStack(OPERATOR);
    Push(OPERATOR,'#');                                                     //操作符栈初始化栈底为‘#’
    
    //3、计算表达式

    int i = 0;
    double TemOptr;                                                          //存放运算符栈顶元素
    GetTop(OPERATOR,TemOptr);

    while((str[i+1])||(TemOptr!='#')){
        if(isDigit(str[i])){
            //将字符转化为对应的数字进行压栈
            double data;
            GetNumber(str[i],data );
            Push(OPERAND,data);
            i++;
        }
        
        else{
            if(GetPriority(str[i]) > GetPriority(TemOptr)){
                //优先级高，进栈
                Push(OPERATOR,str[i]);
                i++;
                GetTop(OPERATOR,TemOptr);                           //每次进栈后都要更新栈顶元素
            }
            else{
                //首先判断是不是左括号
                if(TemOptr == '('){
                    //此时左括号优先级看作最低
                    
                    if(str[i] == ')'){
                        //如果下一个运算符是右括号,弹出左括号并且跳过右括号
                        Pop(OPERATOR);
                        i++;
                    }
                    else{
                        //如果不是右括号，进栈
                        Push(OPERATOR,str[i]);
                        i++;
                        GetTop(OPERATOR,TemOptr);
                        // 判断下一个字符是不是右括号，如果是右括号，将左括号弹出
                        
                        
                    }
                }
                                                          
                
                else{
                    //优先级低，进行运算
                    double a;                                             //存放第一个运算数
                    double b;                                             //存放第二个运算数
                    double optr;
                    Pop(OPERAND,b);
                    Pop(OPERAND,a);
                    Pop(OPERATOR,optr);
                    // 将运算结果入栈
                    Push(OPERAND,Operate(a,optr,b));
                    
                     GetTop(OPERATOR,TemOptr);                             //更新操作符栈顶元素
                }
                
                
            }
        }
    }  
    Pop(OPERAND,result);
    DestroyStack(OPERAND);                                             //销毁栈
    DestroyStack(OPERATOR);                                            //销毁操作符栈
}

bool isDigit(char i){
    //操作结果 ：如果是数字 返回true 反之则返回false
    if(i>=48 && i<=57) return true;
    else return false;
 } 

void GetNumber(char c, double &data){
    data = double(c)-48;                             //48为0的ascll码
}

int GetPriority(char c){
    //操作结果：返回操作符的优先级
    // # 优先级最低
    // ) 优先级为LESS_2
    // + - 优先级为LESS_3
    // */ 优先级为LESS_4
    
    int optr_priority;
    enum priority{LESS_1,LESS_2,LESS_3,LESS_4,LESS_5};
    if(c==')'){
        optr_priority = LESS_2;
    }
    if(c=='+' || c=='-'){
        optr_priority = LESS_3;
    }
    if(c=='*' || c=='/'){
        optr_priority = LESS_4;
    }
    if(c=='('){
        optr_priority = LESS_5;
    }
    if(c=='#'){
        optr_priority = LESS_1;
    }
    return optr_priority;
}

double Operate(const double &a, char c, const double &b){
    //操作结果：根据c不同的符号进行运算
    switch (c)
    {
    case 43: return a+b;break;
    case 45: return a-b;break;
    case 42: return a*b;break;
    case 47: return a/b;break;
    
    default:
        break;
    }
}


//栈的方法实现
void InitStack(SqStack &S){
    //操作结果，初始化一个栈
    S.base =(ElemType*)malloc(STACKINITSIZE*sizeof(ElemType));                   //开辟一块内存
    if(S.base == NULL) cout<<"内存申请失败"<<endl;                               //内存申请失败
    S.top = S.base;                                                              //初始时 top与base重合
    S.stacksize = STACKINITSIZE;
}

void DestroyStack(SqStack &S){
    //操作结果：释放栈,因为时有顺序表实现，所以只需要释放S.base即可
    if(S.base!=NULL){
        free(S.base);
        S.base = NULL;
    }
    S.top = NULL;
    S.stacksize = 0;
}

void ClearStack(SqStack &S){
    //操作结果：清空顺序栈
    S.top = S.base;
}

bool GetTop(const SqStack &S, ElemType &e){
    //操作结果 ：将顺序栈的栈顶元素返回给e
    if(S.top == S.base){
        return false;
    }
    e = *(S.top-1);
    return true;
}

bool Push(SqStack &S, const ElemType &e){
    //操作结果：在栈顶插入元素e
    if(S.top-S.base >= S.stacksize){
        //栈空间已满
        S.base = (ElemType *) realloc(S.base,STACKINITCREMENT*sizeof(ElemType));           //增加存储空间
        if(S.base == NULL) {cout<<"增加空间失败"<<endl;return false;}
        S.top = S.base + S.stacksize;                                                      //重新计算top的位置
        S.stacksize += STACKINITCREMENT;
    }
    *S.top= e;
    S.top++;
    return true;
}

bool Pop(SqStack &S, ElemType &e){
    //操作结果：将栈顶元素删除并将值返回给e
    if(S.base == S.top){
        return false;
    }
    e = *(S.top-1);
    S.top--;
    return true;
}

bool Pop(SqStack &S){
    //删除元素
    if(S.base == S.top){
        return false;
    }
    return true;
}

