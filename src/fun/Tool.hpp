/**
 * 工具类
 * 单例模式
 * 提供方法和数据
*/

#ifndef TOOL_HPP
#define TOOL_HPP

#include <opencv2/opencv.hpp>
#include <QString>
#include <bits/stdc++.h>

#define TGI Tool::getInstance()

class Tool{
public:
    //获取唯一实例
    static Tool& getInstance(){
        static Tool tool;
        return tool;
    }

    //提供方法

    //读取图片到CurMat
    void ReadCurMat(const char* filename){
        QString FileName=QString(filename);
        //默认是BGR读取
        CurMat=cv::imread(FileName.toLocal8Bit().toStdString());
        //转成RGB
        cv::cvtColor(CurMat,CurMat,cv::COLOR_BGR2RGB);
    }

    //操作数据

    //读取CurMat;
    cv::Mat getCurMat(){
        return CurMat;
    }
private:
    //私有化
    Tool()=default;
    Tool(const Tool& tool)=default;
    Tool& operator=(const Tool& tool)=default;

    //数据
    cv::Mat CurMat;
};

#endif