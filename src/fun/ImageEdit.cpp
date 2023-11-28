#include "ImageEdit.h"

//裁剪
void Composition(cv::Rect cropRect)
{
#ifdef FUN
    //读取
    cv::Mat image=TGI.getCurMat();

    //裁剪
    cv::Mat cropImage=image(cropRect);

    //写回
    TGI.setCurMat(cropImage);
#else
#endif
}