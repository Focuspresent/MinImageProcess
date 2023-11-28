/**
 * 工具类
 * 单例模式
 * 提供方法和数据
*/

#ifndef TOOL_HPP
#define TOOL_HPP

#include <opencv2/opencv.hpp>
#include <QString>
#include <QRect>
#include <bits/stdc++.h>

#define TGI Tool::getInstance()
#define TGMAT Tool::getInstance().getCurMat()  
#define FUN
#define DEBUG

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

    void ReadCurMat(const QString& filename){
        //默认是BGR读取
        CurMat=cv::imread(filename.toLocal8Bit().toStdString());
        //转成RGB
        cv::cvtColor(CurMat,CurMat,cv::COLOR_BGR2RGB);
    }

    //保存图片到某个路径
    void WriteCurMat(const char* filename){
        QString FileName=QString(filename);
        cv::imwrite(FileName.toLocal8Bit().toStdString(),CurMat);
    }

    void WriteCurMat(const QString& filename){
        cv::imwrite(filename.toLocal8Bit().toStdString(),CurMat);
    }

    //操作数据

    //读取CurMat;
    cv::Mat getCurMat(){
        return CurMat;
    }

    //设置CurMat;
    void setCurMat(cv::Mat&& Input){
        CurMat=std::move(Input);
    }

    void setCurMat(cv::Mat Input){
        CurMat=std::move(Input);
    }

    //读取窗口数据
    int X() {
        return x;
    }

    int Y(){
        return y;
    }

    int Width(){
        return width;
    }

    int Height(){
        return height;
    }

    cv::Rect ShowRect(){
        return std::move(cv::Rect(x,y,width,height));
    }

    QRect ShowQRect(){
        return std::move(QRect(x,y,width,height));
    }

    //设置窗口数据
    void setX(int x){
        this->x=x;
    }

    void setY(int y){
        this->y=y;
    }

    void setWidth(int width){
        this->width=width;
    }

    void setHeight(int height){
        this->height=height;
    }

    void setShowRect(cv::Rect rect){
        setX(rect.x);
        setY(rect.y);
        setWidth(rect.width);
        setHeight(rect.height);
    }

    void setShowRect(cv::Rect& rect){
        setX(rect.x);
        setY(rect.y);
        setWidth(rect.width);
        setHeight(rect.height);
    }

    void setShowQRct(QRect qrect){
        setX(qrect.x());
        setY(qrect.y());
        setWidth(qrect.width());
        setHeight(qrect.height());
    }

    void setShowQRct(QRect& qrect){
        setX(qrect.x());
        setY(qrect.y());
        setWidth(qrect.width());
        setHeight(qrect.height());
    }

private:
    //私有化
    Tool()=default;
    Tool(const Tool& tool)=default;
    Tool& operator=(const Tool& tool)=default;

    //数据

    //显示的图片
    cv::Mat CurMat;
    //显示窗口的数据
    int x,y;
    int width,height;
};

#endif //TOOL_HPP