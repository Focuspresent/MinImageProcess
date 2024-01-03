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
    x=(int)(1.0*x/scalewidth);
    y=(int)(1.0*y/scaleheight);
    //写字
    cv::putText(Timage,text,cv::Point(x,y),cvenum,fontScale,scalar,thickness,linetype);
    //写回
    TGI.setCurMat(Timage);
}

/**
 * 水印
*/
void Watermark(){
    //读取
    cv::Mat srcImage=TGOMAT;
    // 用来放之后拿来图层叠加的原始图片
    cv::Mat oriImg = srcImage.clone();
    // 创建水印图层
    cv::Mat overlay = srcImage.clone();

    // 计算合适的字体大小，使水印适应不同图像大小
    int fontSize = std::max(oriImg.rows, oriImg.cols) / 180;
    //选择字体样式
    int fontFace= cv::FONT_HERSHEY_SCRIPT_COMPLEX;
    //粗细
    int thickness=2;
    //文字
    std::string text="by:sghb and zdc";
    //计算添加水印的文本框大小
    cv::Size textSize = cv::getTextSize(text, fontFace, fontSize, thickness, nullptr);

    // 在图像上添加水印文本
    putText(overlay,text, cv::Point(0, textSize.height), fontFace, fontSize, cv::Scalar(0, 0, 255), thickness);
    addWeighted(overlay, 0.3, oriImg, 1 - 0.3, 0, oriImg);

    // 将添加水印后的图像保存在dstImage变量中
    cv::Mat dstImage = oriImg.clone();

#ifdef DEBUG
    cv::imshow("watermark",dstImage);
#endif
    //写回
    TGI.setCurMat(dstImage);
}