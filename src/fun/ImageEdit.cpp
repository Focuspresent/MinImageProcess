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
#ifdef DEBUG
    cv::imshow("text crop",cropImage);
#endif
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

//曝光
void Exposure(double alpha,int beta){
    //读取
    cv::Mat image=TGOMAT,Expimage;
    //曝光
    image.convertTo(Expimage,-1,alpha,beta);
    //写回
    TGI.setCurMat(Expimage);
}

//亮度
void Brightness(int bright){
    //读取
    cv::Mat image=TGOMAT;
    //增益或减益
    cv::Mat Briimage=image+cv::Scalar(bright,bright,bright);
    //写回
    TGI.setCurMat(Briimage);
}

//对比度
void ContrastRatio(double contrast){
    //读取
    cv::Mat image=TGOMAT;
    //对比
    cv::Mat Conimage=image*contrast;
    //写回
    TGI.setCurMat(Conimage);
}

//直方图均衡化
void HistogramEqualization(){
    cv::Mat image = TGOMAT;
    cv::Mat hsvImage;
    // 将图像转换为HSV颜色空间
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> channels;
    // 分离H、S、V通道
    cv::split(hsvImage, channels);
    // 对亮度通道进行直方图均衡化
    cv::equalizeHist(channels[2], channels[2]);
    // 合并通道  
    cv::merge(channels, hsvImage);  
    // 将图像转换回BGR颜色空间
    cv::cvtColor(hsvImage, hsvImage, cv::COLOR_HSV2BGR); 
    //写回
    TGI.setCurMat(hsvImage);
}

//锐化
void Sharpen(int level){
    //读取
    cv::Mat image=TGOMAT;
    cv::Mat Shaimage = cv::Mat::zeros(image.size(), image.type());
    // 创建拉普拉斯滤波器
    cv::Mat laplacian_filter = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    // 对彩色图像应用滤波器
    cv::filter2D(image,Shaimage,-1,laplacian_filter);
    //根据锐化程度调整
    double alpha=level/100.0;
    Shaimage=image+alpha*(Shaimage-image);
    //写回
    TGI.setCurMat(Shaimage);
}

//平滑(高斯滤波)
void Smooth(double level){
    //读取
    cv::Mat image=TGOMAT,Smoimage;
    if(!level){
        TGI.setCurMat(image);
        return ;
    }
    //平滑(高斯滤波)
    cv::GaussianBlur(image,Smoimage,cv::Size(3,3),level,level,cv::BORDER_DEFAULT);
    //写回
    TGI.setCurMat(Smoimage);
}

//色温(RGB)
void ColorTemperature(int temperature){
    //计算增量
    double red=temperature*1.0/100;
    double blue=-temperature*1.0/100;
    //输出图像
    cv::Mat CTimage;
    //分离
    std::vector<cv::Mat> channels;
    cv::split(TGOMAT,channels);
    //增量计算
    channels[0]+=red;
    channels[2]+=blue;
    //合并
    cv::merge(channels,CTimage);
    //保证数据范围
    cv::normalize(CTimage,CTimage,0,255,cv::NORM_MINMAX);
    //写回
    TGI.setCurMat(CTimage);
}

//色调
void Tone(int tone){
    //读取
    cv::Mat image=TGOMAT,Tonimage;
    //从RGB转成HSV
    cv::cvtColor(image,Tonimage,cv::COLOR_RGB2HSV);
    //操作
    for(int i=0;i<Tonimage.rows;i++){
        for(int j=0;j<Tonimage.cols;j++){
            int hue=Tonimage.at<cv::Vec3b>(i,j)[0];
            int nhue=hue+100*tone/100.0;
            if(nhue<0) nhue+=180;
            if(nhue>179) nhue-=180;
            Tonimage.at<cv::Vec3b>(i,j)[0]=nhue;
        }
    }
    //从HSV转成RGB
    cv::cvtColor(Tonimage,Tonimage,cv::COLOR_HSV2RGB);
    //写回
    TGI.setCurMat(Tonimage);
}