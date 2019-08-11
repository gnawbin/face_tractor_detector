//
// Created by root on 2019/8/11.
//

#include "base.h"
#include <opencv2/opencv.hpp>
#include <iostream>
int main(int argc,char **argv){
    //if(argc<2){
   //     cout<<"usage: ./visualise_annotation annotation_file"<<endl;
     //   return 0;
    //}
    cout<<"filename ="<<argv[1]<<endl;
    argv[1]="/media/wangbin/36005E93005E59C7/face_tracker_detector/res/annotations.ymal";

    FaceTractorData data=load_ft<FaceTractorData>(argv[1]);
    if(data.imnames.size()==0){
        cerr<<"Data file does not contain any annotations."<<endl;
        return -1;
    }

    data.rm_incomplete_samples();
    cout<<"n images: "<<data.imnames.size()<<endl
    <<"n points: "<<data.symmery.size()<<endl
    <<"n connections: "<<data.connections.size()<<endl;
    namedWindow("Annoations");
    int index=0;
    bool flipped=false;
    while (1){
        Mat image;
        if(flipped){
            image=data.get_image(index,3);
        }else{
            image=data.get_image(index,2);
        }
        data.draw_connect(image,index,flipped);
        data.draw_sym(image,index,flipped);
        imshow("Annotations",image);
        int c=waitKey(0);
        if(c=='q')
            break;
        else if(c=='p')
            index++;
        else if(c=='o')
            index--;
        else if(c=='f')
            flipped=!flipped;
        if(index<0)
            index=0;
        else if(index>=int(data.imnames.size()))
            index=data.imnames.size()-1;
    }
    destroyWindow("Annotations");
    return 0;
}