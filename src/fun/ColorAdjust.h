/**
 * 色彩调整
*/

#ifndef COLORADJUST_H
#define COLORADJUST_H

#include "Tool.hpp"

void LightSense(double alpha,int beta);
void CurveAdjustment();
void Saturation(double factor);
void CurveTone(bool R_flag=0,int R_origin=0,int R_target=0,bool G_flag=0,int G_origin=0,int G_target=0,bool B_flag=0,int B_origin=0,int B_target=0);
void CurveTone(int channel,std::vector<int> origin,std::vector<int> target);
void CurveTone(int channel,int origin,int target);
void HSL();

#endif //COLORADJUST_H