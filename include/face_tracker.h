//
// Created by root on 2019/8/13.
//

#ifndef FACE_TRACKER_DETECTOR_FACE_TRACKER_H
#define FACE_TRACKER_DETECTOR_FACE_TRACKER_H

#include "patch_model.h"
#include "shape_model.h"
#include "face_detetor.h"
class FpsTimer{//frames /second timer
public:
    int64_t t_start; //start time
    int64_t t_end; //end time
    float fps;//current frames/sec
    int fnum;//number of frames since t_start
    FpsTimer(){this->reset();}//default constructor
    void increment();//increment timer index
    void reset();//reset timer
    void display_fps(Mat &im,Point p=Point(-1,-1));//

};
class FaceTrackerParams{//face tracking parameters
public:
    vector<Size> ssize;//search region size/level
    bool robust;//use robust fittig?
    int itol;//maximum number of iterations to try
    float ftol;//convergence tolerance
    float scaleFactor;//
    int minNeighbours;
    Size minSize;
    FaceTrackerParams();
    void write(FileStorage &fs) const;
    void read(const FileNode& node);

};
class FaceTracker{//face tracking class
public:
    bool tracking;//are we in tracking mode?
    FpsTimer timer;//frames/second timer
    vector<Point2f> points;//current tracked points
    FaceDetector detector;//detector for initialisation
    ShapeModel smodel;//shape Model
    PatchModels patchModels;//feature detectors
    FaceTracker():tracking(false){}
    int track(const Mat &im,
            const FaceTrackerParams &p=FaceTrackerParams());
    void reset(){
        tracking=false;
        timer.reset();
    }
    void draw(Mat &im,const Scalar pts_color=CV_RGB(255,0,0),
            const Scalar con_color=CV_RGB(0,255,0));
    void write(FileStorage &fs) const;
    void read(const FileNode& node);

protected:
    vector<Point2f> fit(const Mat &image,
            const vector<Point2f> &init,
            const Size size=Size(21,21),//initial point estimates
            const bool robust=false,
            const int itol=10,
            const float ftol=1e-3
            );
};
#endif //FACE_TRACKER_DETECTOR_FACE_TRACKER_H
