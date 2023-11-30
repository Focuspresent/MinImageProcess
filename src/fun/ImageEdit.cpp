#include "ImageEdit.h"

//裁剪
void Composition(cv::Rect& cropRect)
{   
    //读取
    cv::Mat image=TGOMAT;
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
    //确认
    TGI.Comfirm();
}

void Composition(cv::Rect&& cropRect){
    Composition(std::move(cropRect));
}

void Composition(int x,int y,int width,int height)
{
    cv::Rect cropRect(x,y,width,height);
    Composition(cropRect);
}

//旋转
//angle>=-45&&angle<=45&&flag=true,旋转时会变大
void Spin(double angle,bool flag)
{
    auto getScale=[&]()->double{
        if(!flag) return 1.0;
        if(angle<-45||angle>45) return 1.0;
        return 1.0+(double)(abs(angle)/45.0*1.0);
    };
    //读取
    cv::Mat image=TGOMAT;
    //计算中心点
    cv::Point2f center(image.cols/2.0,image.rows/2.0);
    // 获取旋转矩阵
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, getScale());
    //旋转
    cv::Mat SpinedImage;
    cv::warpAffine(image,SpinedImage,rotationMatrix,image.size());
    //写回
    TGI.setCurMat(SpinedImage);
}