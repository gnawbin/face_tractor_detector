//
// Created by root on 2019/8/13.
//

#ifndef FACE_TRACKER_DETECTOR_FACE_DETETOR_H
#define FACE_TRACKER_DETECTOR_FACE_DETETOR_H

#include <opencv2/opencv.hpp>
#include "face_tractor_data.h"
class FaceDetector{ //face detector for initialisation
public:
    string detector_fname;//file containing cascade classifier
    Vec3f detector_offset;//file containing cascade classifier
    Mat reference;//reference shape
    CascadeClassifier detector;//face detector
    vector<Point2f> //points for deteted face in image
    detect(const Mat& im,//image containing face
            const float scaleFactor=1.1,//scale increment
            const int minNeighbors=2,//minimum neigbhourhood size
            const Size minSize=Size(30,30)//minimum detection windo size
            );
    void train(FaceTractorData &data,//training data
            const string fname, //cascade detector
            const Mat& ref,//reference shape
            const bool mirror=false,//mirror data?
            const bool visi=false,//visualise trianing?
            const float frac =0.8,//fraction of points in detected rect
            const float scaleFactor=1.1,//scale increment
            const int minNeighbours=2,//minimum neighbourhood size
            const Size minSize=Size(30,30)//minimum detection window siz
            );
    void write(FileStorage &fs) const;//file storage object to write to
    void read(const FileNode& node);

protected:
    bool enough_bounded_points(const Mat &pts,
            const Rect R,
            const float frac);
    Point2f center_of_mass(const Mat pts);
    float calc_scale(const Mat &pts);//scaling from &reference
};
#endif //FACE_TRACKER_DETECTOR_FACE_DETETOR_H
