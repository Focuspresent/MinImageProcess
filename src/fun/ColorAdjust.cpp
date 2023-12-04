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

//曲线调色(RGB调色)
//单一值修改
//多通道
void CurveTone(bool R_flag,int R_origin,int R_target,bool G_flag,int G_origin,int G_target,bool B_flag,int B_origin,int B_target){
    //读取
    cv::Mat image=TGOMAT;
    //复制
    cv::Mat CTimage=image.clone();
    //操作
    for(int i=0;i<CTimage.rows;i++){
        for(int j=0;j<CTimage.cols;j++){
            //读取像素点
            cv::Vec3b& piexl=CTimage.at<cv::Vec3b>(i,j);
            //检测红色通道
            if(R_flag&&piexl[0]==R_origin){
                piexl[0]=R_target;
            }
            //检测绿色通道
            if(G_flag&&piexl[1]==G_origin){
                piexl[1]=G_target;
            }
            //检测蓝色通道
            if(B_flag&&piexl[2]==B_origin){
                piexl[2]=B_target;
            }
        }   
    }
    //写回
    TGI.setCurMat(CTimage);
}

//曲线调色(RGB调色)
//多值修改
//单一通道
void CurveTone(int channel,std::vector<int> origin,std::vector<int> target){
    //判定
    if(origin.size()!=target.size()){
        #ifdef DEBUG
            std::cout<<"input size diff"<<std::endl;
        #endif
        return;
    }
    //读取
    cv::Mat image=TGOMAT;
    //判定
    if(channel>=image.channels()){
        #ifdef DEBUG
            std::cout<<"channel is more"<<std::endl;
        #endif
        return;
    }
    //复制
    cv::Mat CTimage=image.clone();
    //生成对应关系
    std::unordered_map<int,int> ori_to_tar;
    for(int i=0;i<origin.size();i++){
        ori_to_tar[origin[i]]=target[i];
    }
    //操作
    for(int i=0;i<CTimage.rows;i++){
        for(int j=0;j<CTimage.cols;j++){
            //读取像素
            cv::Vec3b& pixel=CTimage.at<cv::Vec3b>(i,j);
            //修改像素
            if(ori_to_tar.count(pixel[channel])){
                pixel[channel]=ori_to_tar[pixel[channel]];
            }
        }
    }
    //写回
    TGI.setCurMat(CTimage);
}

//HSL(色调、饱和度、亮度)
void HSL(){

}