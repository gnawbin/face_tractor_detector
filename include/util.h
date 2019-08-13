//
// Created by root on 2019/8/13.
//

#ifndef FACE_TRACKER_DETECTOR_UTIL_H
#define FACE_TRACKER_DETECTOR_UTIL_H
//scaling factor
//scaling basis vector
//width of desired shape
float calc_scale(const Mat&  X,const float width){
    int n=X.rows/2;
    float xmin=X.at<float>(0),xmax=X.at<float>(0);
    for(int i=0;i<n;i++){
        xmin=min(xmin,X.at<float>(2*i));
        xmax=max(xmax,X.at<float>(2*i));
    }
    return width/(xmax-xmin);
}
void draw_string(Mat img,const string text){
    Size size=getTextSize(text,FONT_HERSHEY_COMPLEX,0.6f,1,NULL);
    putText(img,text,Point(0,size.height),FONT_HERSHEY_COMPLEX,0.6f,Scalar::all(0),CV_8U);
    putText(img,text,Point(1,size.height+1),FONT_HERSHEY_COMPLEX,0.6f,Scalar::all(255),1,CV_8U);

}
void draw_shape(Mat &img,const vector<Point2f> &q,const Mat &C){
    int n=q.size();
    for(int i=0;i<C.rows;i++){
        line(img,q[C.at<int>(i,0)],q[C.at<int>(i,1)],CV_RGB(255,0,0),2);
    }
    for(int i=0;i<n;i++){
        circle(img,q[i],1,CV_RGB(0,0,0),2,CV_8U);
    }
}
#endif //FACE_TRACKER_DETECTOR_UTIL_H
