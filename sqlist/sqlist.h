#ifndef SQLIST_H
#define SQLIST_H
template <class ElemType>
class SqList
{
    protected:
    
        int maxsize;
        int cout;
        ElemType *elems;
    
    public:
    
        SqList(int size);
        ~SqList();

};
#endif