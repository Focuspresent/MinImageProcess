/**
 * 图像编辑头文件
*/

#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H

#include "Tool.hpp"

void Composition(cv::Rect& cropRect);
void Composition(cv::Rect&& cropRect);
void Composition(int x,int y,int width,int height);

#endif //IMAGEEDIT_H