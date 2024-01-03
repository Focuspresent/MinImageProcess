/**
 * 其他功能
*/

#ifndef OTHERS_H
#define OTHERS_H

#include "Tool.hpp"

void Beauty(int value);
void Text(const char* text,int x,int y,int cvenum,double fontScale,cv::Scalar scalar, int thickness=1,int linetype=8);
void Watermark();

#endif //OTHERS_H