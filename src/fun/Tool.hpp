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
#include "Config.h"

#define TGI Tool::getInstance()
#define TGMAT Tool::getInstance().getCurMat() 
#define TGOMAT Tool::getInstance().getOriginMat()
#define TGQTL Tool::getInstance().TopLeft()
#define TGQTR Tool::getInstance().TopRight()
#define TGQBL Tool::getInstance().BottomLeft()
#define TGQBR Tool::getInstance().BottomRight()
#define NVal 3

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
        //转成BGR
        cv::cvtColor(OriginMat,OriginMat,cv::COLOR_RGB2BGR);
        cv::imwrite(FileName.toLocal8Bit().toStdString(),OriginMat);
        //转成RGB
        cv::cvtColor(OriginMat,OriginMat,cv::COLOR_BGR2RGB);
    }

    void WriteCurMat(const QString& filename){
        //转成BGR
        cv::cvtColor(OriginMat,OriginMat,cv::COLOR_RGB2BGR);
        cv::imwrite(filename.toLocal8Bit().toStdString(),OriginMat);
        //转成RGB
        cv::cvtColor(OriginMat,OriginMat,cv::COLOR_BGR2RGB);
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

    //取消操作
    void Cancel(){
        CurMat=OriginMat;
    }

    /**
     * 三次样条插值曲线
     *
     * @param x [in]  控制点的x坐标数组
     * @param y [in]  控制点的y坐标数组
     * @param n [in]  控制点的总数
     * @param t [in]  输出点的x坐标数组
     * @param m [in]  输出点的总数
     * @param z [out]  输出点的y坐标数组
     * 
     * @return 所有数据点之间曲线拟合面积的总和
     */
    double spline(double *x, double *y, int n, double *t, int m, double *z){
        double* dy = new double[n];
        memset(dy, 0, sizeof(double)*n);
        dy[0] = -0.5;

        double* ddy = new double[n];
        memset(ddy, 0, sizeof(double)*n);

        double h1;
        double* s = new double[n];
        double h0 = x[1] - x[0];

        s[0] = 3.0 * (y[1] - y[0]) / (2.0 * h0) - ddy[0] * h0 / 4.0;
        for( int j = 1; j <= n - 2; ++j )
        {
            h1 = x[j + 1] - x[j];
            double alpha = h0 / (h0 + h1);
            double beta = (1.0 - alpha) * (y[j] - y[j - 1]) / h0;
            beta = 3.0 * (beta + alpha * ( y[j + 1] - y[j] ) / h1);
            dy[j] = -alpha / (2.0 + (1.0 - alpha) * dy[j - 1]);
            s[j] = (beta - (1.0 - alpha) * s[j - 1]);
            s[j] = s[j] / (2.0 + (1.0 - alpha) * dy[j - 1]);
            h0 = h1;
        }
        dy[n-1] = (3.0*(y[n-1] - y[n-2]) / h1 + ddy[n-1] * h1/2.0 - s[n-2]) / (2.0 + dy[n-2]);

        for( int j = n - 2; j >= 0; --j )
        {
            dy[j] = dy[j] * dy[j + 1] + s[j];
        }

        for( int j = 0; j <= n - 2; ++j )
        {
            s[j] = x[j + 1] - x[j];
        }

        for( int j = 0; j <= n - 2; ++j )
        {
            h1 = s[j] * s[j];
            ddy[j] = 6.0 * (y[j+1] - y[j]) / h1 - 2.0 * (2.0 * dy[j] + dy[j+1]) / s[j];
        }

        h1 = s[n-2] * s[n-2];
        ddy[n-1] = 6.0 * (y[n-2] - y[n-1]) / h1 + 2.0 * (2.0 * dy[n-1] + dy[n-2]) / s[n-2];
        double g = 0.0;
        for(int i=0; i<=n-2; i++)
        {
            h1 = 0.5 * s[i] * (y[i] + y[i+1]);
            h1 = h1 - s[i] * s[i] * s[i] * (ddy[i] + ddy[i+1]) / 24.0;
            g = g + h1;
        }

        for(int j=0; j<=m-1; j++)
        {
            int i;
            if( t[j] >= x[n-1] ) {
                i = n - 2;
            } else {
                i = 0;
                while(t[j] > x[i+1]) {
                    i = i + 1;
                }
            }
            h1 = (x[i+1] - t[j]) / s[i];
            h0 = h1 * h1;
            z[j] = (3.0 * h0 - 2.0 * h0 * h1) * y[i];
            z[j] = z[j] + s[i] * (h0 - h0 * h1) * dy[i];
            h1 = (t[j] - x[i]) / s[i];
            h0 = h1 * h1;
            z[j] = z[j] + (3.0 * h0 - 2.0 * h0 * h1) * y[i+1];
            z[j] = z[j] - s[i] * (h0 - h0 * h1) * dy[i+1];
        }

        delete [] s;
        delete [] dy;
        delete [] ddy;

        return (g);
    }

    //调整数据范围
    double clip(double value,double mi,double ma){
        if(value<mi) return mi;
        if(value>ma) return ma;
        return value;
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

    //设置缩放因子
    void setScaleWidth(double scalewidth){
        this->scalewidth=scalewidth;
    }

    void setScaleHeight(double scaleheight){
        this->scaleheight=scaleheight;
    }

    //读取缩放因子
    double getScaleWidth(){
        return scalewidth;
    }

    double getScaleHeight(){
        return scaleheight;
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
    //缩放图片的缩放因子
    double scalewidth,scaleheight;
};

#endif //TOOL_HPP