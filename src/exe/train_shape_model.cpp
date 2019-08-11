//
// Created by root on 2019/8/11.
//

#include "base.h"
#include "opencv2/opencv.hpp"
#include <iostream>
const char *usage="usage: ./train_shape_model annotation_file shape_model_file"
                  "[-f fraction_of_variation][-k maximum-modes] [--mirror]";
int main(int argc,char **argv){
    const char * annotation_file="/media/wangbin/36005E93005E59C7/face_tracker_detector/res/annotations.ymal";
    bool mirror=true;
    FaceTractorData data=load_ft<FaceTractorData>(annotation_file);
    if(data.imnames.size()==0){
        cerr<<"Data file does not contain any annotations."<<endl;
    }
    data.rm_incomplete_samples();
    vector<vector<Point2f>> points;
    for(int i=0;i<int(data.points.size());i++){
        points.push_back(data.get_points(i,false));
        if(mirror)
            points.push_back(data.get_points(i,true));
    }
    cout<<"shape model training  samples: "<<points.size()<<endl;
    ShapeModel smodel;
    smodel.train(points,data.connections);
    cout<<"retained: "<<smodel.V.cols-4<<" modes "<<endl;
    save_ft("/media/wangbin/36005E93005E59C7/face_tracker_detector/res/shape_model.ymal",smodel);
    return 0;
}