#include "Others.h"

/**
 * 美颜
 * haar级联分类器
 * 双边滤波
 * @param value 双边滤波的程度 
*/
void Beauty(int value)
{
    //创建人脸检测器
    cv::CascadeClassifier cascade;
    //加载采样文件
    cascade.load("./res/haarcascade_frontalface_default.xml");
    //读取文件
    cv::Mat image=TGOMAT;
    //复制
    cv::Mat Beimage=image.clone();
    //灰度图
    cv::Mat gray;
    cv::cvtColor(Beimage,gray,cv::COLOR_RGB2GRAY);
    //检测
    std::vector<cv::Rect> faces;
    cascade.detectMultiScale(gray,faces);
    //感兴趣区域
    std::vector<cv::Mat> rois;
    for(auto& face: faces){
        #ifdef DEBUG
            cv::rectangle(Beimage,face,cv::Scalar(0,0,255));
        #endif
        rois.emplace_back(Beimage(face));;
    }
    //美颜
    for(int i=0;i<faces.size();i++){
        cv::Mat roi;
        //双边滤波
        cv::bilateralFilter(rois[i],roi,value,value,value/2);
        //写回
        roi.copyTo(Beimage(faces[i]));
    }
    //写回
    TGI.setCurMat(Beimage);
}

/**
 * 文字(水平)
 * @param text 写入的字符串内容
 * @param x 文字左下角的x轴坐标
 * @param y 文字左下角的y轴坐标
 * @param cvenum 字体类型
 * @param fontScale 字体大小的缩放因子
 * @param scalar 字体的颜色
 * @param thickness 文本的线条粗细(1)
 * @param linetype 文本的线条类型(8)
*/
void Text(const char* text,int x,int y,int cvenum,double fontScale,cv::Scalar scalar,int thickness,int linetype){
    //读取
    cv::Mat image=TGOMAT;
    //复制
    cv::Mat Timage=image.clone();
    //修正
    double scalewidth=TGI.getScaleWidth(),scaleheight=TGI.getScaleHeight();
    x=(int)x/scalewidth;
    y=(int)y/scaleheight;
    //写字
    cv::putText(Timage,text,cv::Point(x,y),cvenum,fontScale,scalar,thickness,linetype);
    //写回
    TGI.setCurMat(Timage);
}