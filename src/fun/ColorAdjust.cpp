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