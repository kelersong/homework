/**
 * @Author: 072210109 程涛
 * @Create Time: 2023-12-11 11:55:00
 * @文件名: Tool.h
 * @用途: 实用工具
 */



#ifndef TOOL_H
#define TOOL_H
#include <windows.h>

class Tool{
    public :
    void Set_Color(int x){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
        //此函数可控制字体颜色，颜色对应列表如下所示
		/*
		color(0);
		printf(“黑色\n”);
		color(1);
		printf(“蓝色\n”);
		color(2);
		printf(“绿色\n”);
		color(3);
		printf(“湖蓝色\n”);
		color(4);
		printf(“红色\n”);
		color(5);
		printf(“紫色\n”);
		color(6);
		printf(“黄色\n”);
		color(7);
		printf(“白色\n”);
		color(8);
		printf(“灰色\n”);
		color(9);
		printf(“淡蓝色\n”);
		color(10);
		printf(“淡绿色\n”);
		color(11);
		printf(“淡浅绿色\n”);
		color(12);
		printf(“淡红色\n”);
		color(13);
		printf(“淡紫色\n”);
		color(14);
		printf(“淡黄色\n”);
		color(15);
		printf(“亮白色\n”);
		在0-15范围修改的是字体的颜色超过15改变的是文本背景色
		*/
    }

    /*延迟time ms后清空屏幕*/
    void Sleep_cls(int time){
        Sleep(time);
        system("cls");
    }
};

#endif

