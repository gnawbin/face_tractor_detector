//
// Created by root on 2019/8/12.
//

#include "base.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include "util.h"
using namespace std;
using namespace cv;
int main(int argc,char **argv){
    ShapeModel smodel=load_ft<ShapeModel>("/media/wangbin/36005E93005E59C7/face_tracker_detector/res/shape_model.ymal");
    int n=smodel.V.rows/2;
    float scale=calc_scale(smodel.V.col(0),200);
    float tranx=n*150.0/smodel.V.col(2).dot(Mat::ones(2*n,1,CV_32F));
    float trany=n*150.0/smodel.V.col(3).dot(Mat::ones(2*n,1,CV_32F));
    vector<float> val;
    for(int i = 0; i < 50; i++)val.push_back(float(i)/50);
    for(int i = 0; i < 50; i++)val.push_back(float(50-i)/50);
    for(int i = 0; i < 50; i++)val.push_back(-float(i)/50);
    for(int i = 0; i < 50; i++)val.push_back(-float(50-i)/50);

    //visualise
    Mat img(300,300,CV_8UC3); namedWindow("shape model");
    while (1){
        for(int k=4;k<smodel.V.cols;k++){
            for(int j=0;j<int(val.size());j++){
                Mat p = Mat::zeros(smodel.V.cols,1,CV_32F);
                p.at<float>(0) = scale; p.at<float>(2) = tranx; p.at<float>(3) = trany;

                p.at<float>(k) = scale*val[j]*3.0*sqrt(smodel.E.at<float>(k));
                p.copyTo(smodel.P); img = Scalar::all(255);
                char str[256]; sprintf(str,"mode: %d, val: %f sd",k-3,val[j]/3.0);
                draw_string(img,str);
                vector<Point2f> q = smodel.calc_shape();
                draw_shape(img,q,smodel.C);
                imshow("shape model",img);
                if(waitKey(10) == 'q')return 0;
            }
        }
    }
    return 0;
}