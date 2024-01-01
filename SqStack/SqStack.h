/**
 * @Author: 程涛
 * @Create Time: 2023-10-09 19:31:21
 * @Modified by: Your name
 * @Modified time: 2023-10-09 20:50:51
 * @Description: 顺序栈
 */

template <class ElemType>
class SqStack{
    // 创建一个栈类
    protected:
    // 数据
    ElemType *base;                        //指向栈底的指针
    ElemType *top;                         //指向栈顶的指针
    int maxsize;                           //最大存储空间
    
    public:
    //类方法及默认类函数重载版本声明；
    
    SqStack(int size = 100);               //有参数的构造函数
    ~SqStack();                            //析构函数
    int Length() const;                    //返回栈的元素个数
    bool Push(const ElemType &e);          //在栈顶插入元素
    bool Pop(ElemType &e);                 //删除栈顶的元素，并将值返回给e
    bool Pop();                            //删除栈顶的元素
    bool Top(ElemType &e) const;           //返回栈顶元素的值
    bool Empty();                          //判断栈是否为空
    bool Traverse(void (*visit)(ElemType &e)); //遍历栈元素
    void Clear();                          //清空栈
    
};
