//
// Created by root on 2019/8/13.
//

#include "face_tracker.h"
#include "base.h"
#include <iostream>
#include <stdio.h>
#define fl at<float>
void FpsTimer::increment() {
    if(fnum>=29){
        t_end=cv::getTickCount();
        fps=30.0/(float(t_end-t_start)/getTickFrequency());
        t_start=t_end;
        fnum=0;
    } else
        fnum+=1;
}
void FpsTimer::reset(){
    t_start=cv::getTickCount();
    fps=0;
    fnum=0;
}
void FpsTimer::display_fps(Mat &im, Point p) {
    char str[256];
    Point pt;
    if(p.y<0)
        pt=Point(10,im.rows-20);
    else
        pt=p;
    sprintf(str,"%d frames/sec",(int)cvRound(fps));
    string text=str;
    putText(im,text,pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar::all(255));
}
