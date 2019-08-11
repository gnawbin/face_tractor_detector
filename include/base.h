//
// Created by root on 2019/8/11.
//

#ifndef FACE_TRACKER_DETECTOR_BASE_H
#define FACE_TRACKER_DETECTOR_BASE_H

#include "face_tractor_data.h"
#include "shape_model.h"
#include "patch_model.h"

template <typename T>
T load_ft(const char *fname){
    T x;
    FileStorage fs(fname,FileStorage::READ);
    cout<<fs.isOpened()<<endl;
    if(fs.isOpened()) {
        fs["ft object"] >> x;
    }
    fs.release();
    return x;
}
template <typename  T>
void save_ft(const char *fname,const T& x){
    FileStorage f(fname,FileStorage::WRITE);
    f<<"ft object"<<x;
    f.release();
}
template <typename  T>
void write(FileStorage& fs,const string&,const T& x){
    x.write(fs);
}
template <typename T>
void read(const FileNode& node,T& x,const T& d){
    if(node.empty())
        x=d;
    else
        x.read(node);
}
#endif //FACE_TRACKER_DETECTOR_BASE_H
