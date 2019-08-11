//
// Created by root on 2019/8/11.
//

#include "patch_model.h"
#include "base.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#define  fl at<float>
Mat PatchModel::convert_image(const Mat &im) {
    Mat I;
    if(im.channels()==1){
        if(im.type()!=CV_32F)
            im.convertTo(I,CV_32F);
        else
            I=im;
    }
    else{
        if(im.channels()==3){
            Mat img;
            cvtColor(im,img,COLOR_GRAY2RGB);
            if(img.type()!=CV_32F)
                img.convertTo(I,CV_32F);
            else
                I=img;


        }else{
            cout<<"Unsupported image type!"<<endl;
            abort();
        }
    }
}

Mat PatchModel::calc_response(const Mat &im, const bool sum2one) {
    Mat I=this->convert_image(im);
    Mat res;
    matchTemplate(I,P,res,TM_CCOEFF_NORMED);
    if(sum2one){
        normalize(res,res,0,1,NORM_MINMAX);
        res/=sum(res)[0];
    }

    return res;
}
