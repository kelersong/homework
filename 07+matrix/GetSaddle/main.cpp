/**
 * @Author: tao
 * @Create Time: 2023-10-24 23:10:59
 * @Modified by: Your name
 * @Modified time: 2023-10-27 15:48:11
 * @Description: 求矩阵的马鞍点
 */
#define MAXROW 10
#define MAXCOL 10
#define ElemType int 
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
typedef struct Position{
    //存放横纵数
    int row;
    int col;
} Position;

void GetSaddle( const int &count_row,const int &count_col);

int main(){
    int row;
    int col;
    cout<< "inout row" <<endl;;
    cin >>row;
    cout<< "inout col" <<endl;
    cin >>col;
    GetSaddle(row,col);
    system("pause");
    return 0;
}

void GetSaddle(  const int &count_row, const int &count_col){
    //操作结果：返回一个位置数组
    /*
    思路
    1、将每一列的最大值存放在一个数组中
    2、将每一行的最小值存放在一个数组中
    3、遍历整个矩阵，若该位置的值与最大值与最小值都相等，则该点为马鞍点
    
    
    */

    // 矩阵初始化及其赋值
    ElemType m[count_row][count_col];
    cout<< "input value" <<endl;
    for(int i = 0;i<count_row;i++){
        for(int j = 0;j<count_col;j++){
            cin>>m[i][j];
        }
    }
    //1、求每列的最大值
    ElemType max[1024];                         //存放第j列最大值
    for(int j = 0;j<count_col;j++){
        max[j] = m[0][j];                        //该列的max初值设置为0
        for(int i  =0;i<count_col;i++){
            if(m[i][j]> max[j]){
                max[j] = m[i][j];
            }
        }
    }

    // 2、求每行的最小值
    ElemType min[1024];
    for(int i = 0;i<count_row;i++){
        min[i] = m[i][0];
        for(int j = 0;j<count_col;j++){
            // 遍历行
            if(m[i][j] < min[i]){
                min[i] = m[i][j];
            }
        }
    }
    Position result[1024];

    //遍历整个矩阵
    int count;                            // 马鞍点存放索引
    for(int i = 0;i<count_row;i++){
        for(int j = 0;j<count_col;j++){
            if((m[i][j] == min[i]) && (m[i][j] == max[j])){
                //该点为马鞍点，返回其位置
                result[count].col = j;
                result[count].row = i;
                count++;
            }
        }
    }

    //打印输出
    for(int i=0;i<count;i++){
        //输出马鞍点的位置
        cout<< "<"  << result[i].row +1<<"," << result[i].col+1 << ">" <<endl;
    }

}

