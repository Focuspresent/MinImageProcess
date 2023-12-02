#include "ColorAdjust.h"

//光感
void LightSense(double alpha,int beta){
    //读取
    cv::Mat image=TGOMAT,LSimage;
    //操作
    cv::convertScaleAbs(image,LSimage,alpha,beta);
    //写回
    TGI.setCurMat(LSimage);
}

//曲线调整
void CurveAdjustment(){
    
}

//饱和度
void Saturation(double factor){
    //读取
    cv::Mat image=TGOMAT,Satimage;
    //从RGB转成HSV
    cv::cvtColor(image,Satimage,cv::COLOR_RGB2HSV);
    //操作
    for (int row = 0; row < Satimage.rows; row++) {
        for (int col = 0; col < Satimage.cols; col++) {
            cv::Vec3b& pixel = Satimage.at<cv::Vec3b>(row, col);
            pixel[1] = cv::saturate_cast<uchar>(pixel[1] * factor);
        }
    }
    //从HSV转成RGB
    cv::cvtColor(Satimage,Satimage,cv::COLOR_HSV2RGB);
    //写回
    TGI.setCurMat(Satimage);
}

//曲线调色
void CurveTone(){

}

//HSL(色调、饱和度、亮度)
void HSL(){

}