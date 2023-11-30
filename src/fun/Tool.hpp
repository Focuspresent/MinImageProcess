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
#include <QPoint>
#include <bits/stdc++.h>

#define TGI Tool::getInstance()
#define TGMAT Tool::getInstance().getCurMat() 
#define TGOMAT Tool::getInstance().getOriginMat()
#define TGQTL Tool::getInstance().TopLeft()
#define TGQTR Tool::getInstance().TopRight()
#define TGQBL Tool::getInstance().BottomLeft()
#define TGQBR Tool::getInstance().BottomRight()
#define NVal 3
#define FUN
#define DEBUG

class Tool{
public:
    //获取唯一实例
    static Tool& getInstance(){
        static Tool tool;
        return tool;
    }

    enum Dir{TL,TR,BL,BR};
    //提供方法

    //读取图片到CurMat
    void ReadCurMat(const char* filename){
        QString FileName=QString(filename);
        //默认是BGR读取
        CurMat=cv::imread(FileName.toLocal8Bit().toStdString());
        //转成RGB
        cv::cvtColor(CurMat,CurMat,cv::COLOR_BGR2RGB);
        OriginMat=CurMat;
    }

    void ReadCurMat(const QString& filename){
        //默认是BGR读取
        CurMat=cv::imread(filename.toLocal8Bit().toStdString());
        //转成RGB
        cv::cvtColor(CurMat,CurMat,cv::COLOR_BGR2RGB);
        OriginMat=CurMat;
    }

    //保存图片到某个路径
    void WriteCurMat(const char* filename){
        QString FileName=QString(filename);
        cv::imwrite(FileName.toLocal8Bit().toStdString(),CurMat);
    }

    void WriteCurMat(const QString& filename){
        cv::imwrite(filename.toLocal8Bit().toStdString(),CurMat);
    }

    //看是否临近
    bool Is_Near(int x1,int y1,int x2,int y2){
        if(abs(x1-x2)>NVal) return false;
        if(abs(y1-y2)>NVal) return false;
        return true;
    }

    bool Is_Near(int x,int y){
        if(abs(x-y)>NVal) return false;
        return true;
    }

    bool Is_Near(QPoint p1,QPoint p2){
        return Is_Near(p1.x(),p1.y(),p2.x(),p2.y());
    }

    bool Is_Near(QPoint p,int x,int y){
        return Is_Near(p.x(),p.y(),x,y);
    }

    //是否临近这条线(矩阵的一条边)
    bool Is_Near(int x,int y,int x1,int y1,int x2,int y2){
        if(y1==y2){
            if(!Is_Near(y,y1)) return false;
            for(int x3=std::min(x1,x2);x3<=std::max(x1,x2);x3++){
                if(Is_Near(x,x3)) return true;
            }
            return false;   
        }else if(x1==x2){
            if(!Is_Near(x,x1)) return false;
            for(int y3=std::min(y1,y2);y3<=std::max(y1,y2);y3++){
                if(Is_Near(y,y3)) return true;
            }
            return false; 
        }
        return false;
    }

    bool Is_Near(QPoint p,QPoint p1,QPoint p2){
        return Is_Near(p.x(),p.y(),p1.x(),p1.y(),p2.x(),p2.y());
    }

    //返回(x2,y2)在(x1,y1)的什么方向上
    Dir CompareQPoint(int x1,int y1,int x2,int y2){
        if(x2>x1){
            if(y2>y1) return Dir::BR;
            return Dir::TR;
        }
        if(y2>y1) return Dir::BL;
        return Dir::TL;
    }

    Dir CompareQPoint(QPoint p1,QPoint p2){
        return CompareQPoint(p1.x(),p1.y(),p2.x(),p2.y());
    }

    //确认操作
    void Comfirm(){
        OriginMat=CurMat;
    }

    //操作数据

    //读取CurMat;
    cv::Mat getCurMat(){
        return CurMat;
    }

    cv::Mat getOriginMat(){
        return OriginMat;
    }

    //设置CurMat;
    void setCurMat(cv::Mat&& Input){
        CurMat=std::move(Input);
    }

    void setCurMat(cv::Mat Input){
        CurMat=std::move(Input);
    }

    void setOriginMat(cv::Mat&& Input){
        OriginMat=std::move(Input);
    }

    void setOriginMat(cv::Mat Input){
        OriginMat=std::move(Input);
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

    QPoint ShowQPoint(){
        return std::move(QPoint(x,y));
    }

    QPoint TopLeft(){
        return std::move(QPoint(x,y));
    }

    QPoint TopRight(){
        return std::move(QPoint(x+width,y));
    }

    QPoint BottomLeft(){
        return std::move(QPoint(x,y+height));
    }

    QPoint BottomRight(){
        return std::move(QPoint(x+width,y+height));
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

    void setShowQRect(QRect qrect){
        setX(qrect.x());
        setY(qrect.y());
        setWidth(qrect.width());
        setHeight(qrect.height());
    }

    void setShowQRect(QRect& qrect){
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
    //可以回退的图片
    cv::Mat OriginMat;
    //显示窗口的数据
    int x,y;
    int width,height;
};

#endif //TOOL_HPP