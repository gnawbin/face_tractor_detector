//
// Created by root on 2019/8/11.
//

#ifndef FACE_TRACKER_DETECTOR_PATCH_MODEL_H
#define FACE_TRACKER_DETECTOR_PATCH_MODEL_H

#include "base.h"
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

class PatchModel{//correlation-based patch expert
public:
    Mat P;//normalised patch
    Size patch_size(){return P.size();}
    Mat calc_response(const Mat& im,const bool sum2one=false);//response map(CV_32F)
    //image to compute response from
    //normalize response to sum to one?
    void train(const vector<Mat> &images,//feature centered training images
            const Size psize,//desired patch size
            const float var=1.0,//variance of annotation  error
            const float lambda=1e-6,//regularization weight
            const float mu_init=1e-3,//initial stoch-grad step size
            const int nsamples=1000,//number fo stoch-grad samples
            const bool visi=false//visualize intermediate results?
            );
    void write(FileStorage &fs)const ;//file storage object to write to
    void read(const FileNode &node);//file storage node to read from


protected:
    Mat convert_image(const Mat& im);
};

class PatchModels{//collection of patch experts


public:
    Mat reference;//reference shape
    vector<PatchModel> patches;//patch models
    inline  int n_patches(){return patches.size();}
    void train(FaceTractorData& data,
       const vector<Point2f> &ref,//reference shape
       const Size psize,//desired patch size
       const Size ssize,//search window size
       const bool mirror=false,//use mirrored images
       const float var=1.0,//variance of annotation error
       const float lambda=1e-6,//regularization weight
       const float mu_init=1e-3,//initial stoch-grad step size
       const int nsamples=1000,//number of stoch-grad samples
       const bool visi =false //visualize intermediate results?
            );
    vector<Point2f> calc_peeks(//locations of peaks/feature
            const Mat &im,//image to detect features in
            const vector<Point2f> &points,//initial estimate of shape
             const Size ssize=Size(21,21)//search window size
            ){
            int n = points.size(); assert(n == int(patches.size()));
            Mat pt = Mat(points).reshape(1,2*n);
            Mat S = this->calc_simil(pt);
            Mat Si = this->inv_simil(S);
            vector<Point2f> pts = this->apply_simil(Si,points);
            for(int i = 0; i < n; i++){
                Size wsize = ssize + patches[i].patch_size(); Mat A(2,3,CV_32F);
                A.at<float>(0,0) = S.at<float>(0,0); A.at<float>(0,1) = S.at<float>(0,1);
                A.at<float>(1,0) = S.at<float>(1,0); A.at<float>(1,1) = S.at<float>(1,1);
                A.at<float>(0,2) = pt.at<float>(2*i  ) -
                            (A.at<float>(0,0) * (wsize.width-1)/2 + A.at<float>(0,1)*(wsize.height-1)/2);
                A.at<float>(1,2) = pt.at<float>(2*i+1) -
                            (A.at<float>(1,0) * (wsize.width-1)/2 + A.at<float>(1,1)*(wsize.height-1)/2);
                Mat I; warpAffine(im,I,A,wsize,INTER_LINEAR+WARP_INVERSE_MAP);
                Mat R = patches[i].calc_response(I,false);
                Point maxLoc; minMaxLoc(R,0,0,0,&maxLoc);
                pts[i] = Point2f(pts[i].x + maxLoc.x - 0.5*ssize.width,
                                 pts[i].y + maxLoc.y - 0.5*ssize.height);
                cout<<"-------------------------"<<endl;

            }
            return this->apply_simil(S,pts);

    }
    void write(FileStorage &fs) const;//file storage object to write to
    void read(const FileNode &node);//file storage node to read from
protected:
    Mat inv_simil(const Mat &S);
    Mat calc_simil(const Mat &pts);
    vector<Point2f> //similarity transformed shape
    apply_simil(const Mat &S//similarity transform
            ,const vector<Point2f> &points);//shape to transform
};

#endif //FACE_TRACKER_DETECTOR_PATCH_MODEL_H
