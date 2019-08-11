//
// Created by root on 2019/8/11.
//

#ifndef FACE_TRACKER_DETECTOR_SHAPE_MODEL_H
#define FACE_TRACKER_DETECTOR_SHAPE_MODEL_H

#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
class ShapeModel{//2d linear shape model
public:
    Mat P;//parameter vector(kx1) CV_32F
    Mat V;//shape basis (2nxk) CV_32F
    Mat E;//parameter variance (kx1) CV_32F
    Mat C;//connectivity (cx2) CV_32S
    int npts(){return V.rows/2;}//number of in shape model
    void calc_params(const vector<Point2f> &pts,///points to compute parmaeters from
                const Mat weight=Mat(),//Weight of each point(nx1) CV_32
                const float c_factor=3.0 //clamping factor
            );
    vector<Point2f> calc_shape();//shape described by parameters
    void set_identity_params();//set identity
    Mat rot_scale_align(const Mat& src,//source points
            const Mat& dst);//destination points

            Mat center_shape(const Mat &pts);//shape to center
            void train(const vector<vector<Point2f>> &p,//N-example shapes
                    const vector<Vec2i> &con=vector<Vec2i>(),//point-connectivity
                    const float frac=0.95,//fraction of variation to retain
                    const int kmax=10 //maximum number of modes to retain
                    );
            void write(FileStorage &fs) const;//file storage object to write to
            void read(const FileNode& node);//file storage node to read from
protected:
    void clamp(const float c=3.0);//clamping factor(or standard dev)
    Mat pts2mat(const vector<vector<Point2f>> &p);//points to vectorise
    Mat procrustes(const Mat& X,const int itol=100,
            const float ftol=1e-6);
    Mat calc_rigid_basis(const Mat &X);//procrustes algned shaples/column
};
#endif //FACE_TRACKER_DETECTOR_SHAPE_MODEL_H
