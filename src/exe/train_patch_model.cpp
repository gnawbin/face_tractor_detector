//
// Created by root on 2019/8/12.
//
#include <base.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "util.h"
#define fl at<float>
const char *usage="usage: ./train_patch_model annotation_file shape_model_file patch_model_file"
                  "[-w face_width] [-p patch_size][-s search_window_siize][--mirror]";

int main(int argc,char **argv){
    int  width=200;
    int psize=200;
    int ssize=200;
    bool mirror=true;
    Size wsize(psize+ssize,psize+ssize);
    FaceTractorData data=load_ft<FaceTractorData>("/media/wangbin/36005E93005E59C7/face_tracker_detector/res/annotations.ymal");
    data.rm_incomplete_samples();
    if(data.imnames.size()==0){
        cerr<<"Data file does not contain contain any annotations."<<endl;
    }
    ShapeModel shapeModel=load_ft<ShapeModel>("/media/wangbin/36005E93005E59C7/face_tracker_detector/res/shape_model.ymal");
    shapeModel.P=Scalar::all(0.0);
    shapeModel.P.fl(0)=calc_scale(shapeModel.V.col(0),width);
    vector<Point2f> r=shapeModel.calc_shape();
    //
    PatchModels pmodels;
    pmodels.train(data,r,Size(psize,psize),Size(ssize,ssize));
    save_ft<PatchModels>("/media/wangbin/36005E93005E59C7/face_tracker_detector/res/patch_model.ymal",pmodels);

}