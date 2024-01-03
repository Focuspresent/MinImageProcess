#include "QCurve.h"

QCurve::QCurve(QWidget* parent,cv::Scalar color)
    :QWidget(parent)
    ,color(color)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(256,256);

    is_press=false;
    qpoints.push_back(QPoint(0,0));
    qpoints.push_back(QPoint(255,255));
    current=qpoints.end();
}

QCurve::~QCurve()
{
}

std::vector<QPoint>::iterator QCurve::find(int x)
{
    std::vector<QPoint>::iterator iter;
    for(iter=qpoints.begin();iter!=qpoints.end();iter++){
        if(std::abs(iter->x()-x)<=NVal){
            return iter;
        }
    }
    return qpoints.end();
}

std::vector<QPoint>::iterator QCurve::find(int x,int y)
{
    std::vector<QPoint>::iterator iter;
    for(iter=qpoints.begin();iter!=qpoints.end();iter++){
        if(std::abs(iter->x()-x)<=NVal && std::abs(iter->y()-y)<=NVal){
            return iter;
        }
    }
    return qpoints.end();
}

std::vector<QPoint>::iterator QCurve::add(int x,int y)
{
    std::vector<QPoint>::iterator it=find(x);
    if(it==qpoints.end()){
        QPoint p(x,y);
        std::vector<QPoint>::iterator iter;
        for(iter=qpoints.begin();iter!=qpoints.end();iter++){
            if(iter==qpoints.begin() && iter->x()>p.x()){
                #ifdef DEBUG
                    std::cout<<"insert at beginning"<<std::endl;
                #endif
                return qpoints.insert(iter,p);
            }
            if(iter->x()<x && (iter+1)!=qpoints.end() && (iter+1)->x()>p.x()){
                #ifdef DEBUG
                    std::cout<<"insert"<<std::endl;
                #endif
                return qpoints.insert(iter+1,p);
            }
        }
        #ifdef DEBUG
            std::cout<<"append"<<std::endl;
        #endif
        return qpoints.insert(qpoints.end(),p);
    }
    return it;
}

std::vector<QPoint>::iterator del(int x,int y){

}

int QCurve::calcCurve(double* output_y)
{
    //小于2
    if(qpoints.size()<2){
        for(int i=0;i<256;i++){
            output_y[i]=255-i;
        }
        return 0;
    }
    //等于2
    if(qpoints.size()==2){
        std::vector<QPoint>::iterator qpoint1=qpoints.begin();
        std::vector<QPoint>::iterator qpoint2=qpoint1+1;

        double delta_y=0;
        if(qpoint2->x()!=qpoint1->x()){
            delta_y=(qpoint2->y()-qpoint1->y())*1.0/(qpoint2->x()-qpoint1->x());
        }

        for(int i=0;i<256;i++){
            if(i<qpoint1->x()){
                output_y[i]=qpoint1->y();
            }else if(i>=qpoint1->x() && i<qpoint2->x()){
                output_y[i]=TGI.clip(qpoint1->y()+delta_y*(i-qpoint1->x()),0.0,255.0);
            }else{
                output_y[i]=qpoint2->y();
            }
        }
        return 0;
    }
    //大于2
    int n=qpoints.size();

    double x[n];
    double y[n];
    std::vector<QPoint>::iterator start_qpoint=qpoints.end();
    std::vector<QPoint>::iterator end_qpoint=qpoints.end();
    std::vector<QPoint>::iterator iter;
    int k=0;
    for(iter=qpoints.begin();iter!=qpoints.end();iter++,k++){
        if(k==0) start_qpoint=iter;
        x[k]=iter->x()-start_qpoint->x();
        y[k]=iter->y();
        end_qpoint=iter;
    }

    //如果无效
    if(start_qpoint==qpoints.end()||end_qpoint==qpoints.end()||start_qpoint==end_qpoint){
        for(int i=0;i<256;i++){
            output_y[i]=255-i;
        }
        return 0;
    }    

    //创建样条曲线
    int m=end_qpoint->x()-start_qpoint->x();
    double t[m];
    double z[m];
    for(int i=0;i<m;i++){
        t[i]=i;
    }

    //计算曲线
    TGI.spline(x,y,n,t,m,z);

    //创建输出
    for(int i=0;i<256;i++){
        if(i<start_qpoint->x()){
            output_y[i]=start_qpoint->y();
        }else if(i>=start_qpoint->x() && i<end_qpoint->x()){
            output_y[i]=TGI.clip(z[i-start_qpoint->x()],0,255);
        }else{
            output_y[i]=end_qpoint->y();
        }
    }
    return 1;
}

void QCurve::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    #ifdef DEBUG
        std::vector<QPoint>::iterator it;
        for(it=qpoints.begin();it!=qpoints.end();it++){
            std::cout<<"qpoint: "<<it->x()<<", "<<it->y()<<std::endl;
        }
    #endif
    //绘制边框
    painter.drawLine(QPoint(0,0),QPoint(255,0));
    painter.drawLine(QPoint(0,255),QPoint(255,255));
    painter.drawLine(QPoint(0,0),QPoint(0,255));
    painter.drawLine(QPoint(255,0),QPoint(255,255));

    painter.drawLine(QPoint(63,0),QPoint(63,255));
    painter.drawLine(QPoint(127,0),QPoint(127,255));
    painter.drawLine(QPoint(191,0),QPoint(191,255));
    painter.drawLine(QPoint(0,255-63),QPoint(255,255-63));
    painter.drawLine(QPoint(0,255-127),QPoint(255,255-127));
    painter.drawLine(QPoint(0,255-191),QPoint(255,255-191));

    //绘制控制点
    std::vector<QPoint>::iterator iter;
    for(iter=qpoints.begin();iter!=qpoints.end();iter++){
        painter.drawRect(QRect(QPoint(iter->x()-2,255-iter->y()+2),QPoint(iter->x()+2,255-iter->y()-2)));
        if(current==iter){
            painter.drawRect(QRect(QPoint(iter->x()-1,255-iter->y()+1),QPoint(iter->x()+1,255-iter->y()-1)));
        }
    }

    //绘制曲线
    double z[256];
    calcCurve(z);
    QColor qcolor(color[2],color[1],color[0]);
    painter.setPen(qcolor);
    for(int i=1;i<256;i++){
        painter.drawLine(QPoint(i-1,255-z[i-1]),QPoint(i,255-z[i]));
    }
}

bool QCurve::mouseDel(int x,int y){
    y=255-y;
    return deleteQPoint(QPoint(x,y));
}

void QCurve::mouseDown(int x,int y)
{
    y = 255 - y;
	current = add( x , y );
	is_press = true;
}

bool QCurve::mouseMove(int x,int y)
{
    y = 255 - y;
	if ( is_press ) {
		if (current != qpoints.end()) {
			int prev_x = 0;
			int next_x = 255;

			if (current != qpoints.begin()) {
				int prev_y = (current - 1)->y();
				prev_x = (current - 1)->x();

				//match the previous point
				if ( qpoints.size() > 2 && std::abs(x - prev_x) <= NVal && std::abs(y - prev_y) <= NVal ) {
					current--;
					current = qpoints.erase(current);
                    #ifdef DEBUG
                        std::cout<<"erase previous"<<std::endl;
                    #endif
					return true;
				}

				//if x less than x of previou point
				if ( x <= prev_x) {
					return true;
				}
			}

			if ( ( current + 1) != qpoints.end()) {
				int next_y = (current + 1)->y();
				next_x = (current + 1)->x();

				//match the next point
				if ( qpoints.size() > 2 && std::abs(x - next_x) <= NVal && std::abs(y - next_y) <= NVal ) {
					current = qpoints.erase(current);
                    #ifdef DEBUG
                        std::cout<<"erase next"<<std::endl;
                    #endif
					return true;
				}

				//if x great than x of next point
				if ( x >= next_x) {
					return true;
				}
			}

            current->setX(TGI.clip(x,0,255));
            current->setY(TGI.clip(y,0,255));

			return true;
		}
	}
	return false;
}

void QCurve::mouseUp(int x, int y)
{
	y = 255 - y;
	is_press = false;
}

/* void QCurve::mousePressEvent(QMouseEvent* event)
{
    mouseDown(event->x(),event->y());
    update();
}

void QCurve::mouseMoveEvent(QMouseEvent* event){
    if(mouseMove(event->x(),event->y())){
        update();
    }
}

void QCurve::mouseReleaseEvent(QMouseEvent* event)
{
    mouseUp(event->x(),event->y());
    update();
} */

void QCurve::clearQPoints()
{
    qpoints.clear();
}

int QCurve::addQPoint(const QPoint& p)
{
    std::vector<QPoint>::iterator iter=add(p.x(),p.y());
    if(iter!=qpoints.end()){
        return 1;
    }
    return 0;
}

int QCurve::deleteQPoint(const QPoint& p)
{
    if(qpoints.size()<=2) return 0;
    std::vector<QPoint>::iterator iter;
    iter=find(p.x(),p.y());
    if(iter!=qpoints.end()){
        if(current==iter){
            current=qpoints.end();
        }
        current=qpoints.erase(iter);
        return 1;
    }
    return 0;
}

int QCurve::moveQPoint(const QPoint& p,int x,int y)
{
    std::vector<QPoint>::iterator iter;
    iter=find(p.x(),p.y());
    if(iter!=qpoints.end()){
        iter->setX(x);
        iter->setY(y);
        return 1;
    }
    return 0;
}