#include "Others.h"

//美颜
//haar级联分类器
//双边滤波
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