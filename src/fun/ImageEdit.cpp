#include "ImageEdit.h"

//裁剪
void Composition(cv::Rect& cropRect)
{   
    //读取
    cv::Mat image=TGMAT;
#ifdef FUN
    //裁剪
    cv::Mat cropImage=image(cropRect);
#else
    cv::Mat cropImage(cropRect.height,cropRect.width,CV_8UC3);
    for(int i=cropRect.x;i<cropRect.x+cropRect.width;i++){
        for(int j=cropRect.y;j<cropRect.y+cropRect.height;j++){
            cropImage.at<cv::Vec3b>(j-cropRect.y,i-cropRect.x)=image.at<cv::Vec3b>(j,i);
        }
    }
#endif
    //写回
    TGI.setCurMat(cropImage);
}

void Composition(cv::Rect&& cropRect){
    Composition(std::move(cropRect));
}

void Composition(int x,int y,int width,int height)
{
    cv::Rect cropRect(x,y,width,height);
    Composition(cropRect);
}