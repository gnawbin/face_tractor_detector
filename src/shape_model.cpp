//
// Created by root on 2019/8/11.
//
#include "shape_model.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#define  fl at<float>
void ShapeModel::calc_params(const vector<Point2f> &pts, Mat weight, const float c_factor) {
    int n=pts.size();
    assert(V.rows==2*n);
    Mat s=Mat(pts).reshape(1,2*n);//point set to vector format
    if(weight.empty()){
        P=V.t()*s;//simple projection
    }else{
        if(weight.rows!=n) {
            cerr << "Invalid weighting matrix" << endl;
            abort();
        }
            int c=V.cols;
            Mat H=Mat::zeros(c,c,CV_32F);
            Mat G=Mat::zeros(c,1,CV_32F);
            for(int i=0;i<n;i++){
                Mat v=V(Rect(0,2*i,c,2));
                float w=weight.fl(i);
                H +=w*v.t()*v;
                G +=w*v.t()*Mat(pts[i]);
            }
            solve(H,G,P,DECOMP_SVD);

    }
    this->clamp(c_factor);
}
Mat ShapeModel::center_shape(const Mat &pts) {
    int n=pts.rows/2;
    float mx=0,my=0;
    for(int i=0;i<n;i++){
        mx+=pts.fl(2*i);
        my+=pts.fl(2*i+1);
    }
    Mat p(2*n,1,CV_32F);
    mx/=n;
    my/=n;
    for(int i=0;i<n;i++){
        p.fl(2*i)=pts.fl(2*i);
        p.fl(2*i+1)=pts.fl(2*i+1)-my;
    }
    return p;
}
vector<Point2f> ShapeModel::calc_shape() {
    Mat S=V*P;
    int n=S.rows/2;
    vector<Point2f> pts;
    for(int i=0;i<n;i++){
        pts.push_back(Point2f(S.fl(2*i),S.fl(2*i+1)));
    }
    return pts;
}
void ShapeModel::set_identity_params(){
    P=0.0;
    P.fl(0)=1.0;
}
void ShapeModel::train(const vector<vector<Point2f>> &points, const vector<Vec2i> &con, const float frac, const int kmax) {
    //vectorize points
    Mat X=this->pts2mat(points);
    int c=X.cols,r=X.rows/2;
    //align shapes
    Mat Y=this->procrustes(X);
    //compute rigid transformation
    Mat R=this->calc_rigid_basis(Y);
    //compute non-rigid transformation
    Mat P=R.t()*Y;
    Mat dY=Y-R*P;
    SVD svd(dY*dY.t());
    int m=min(min(kmax,c-1),r-1);
    float vsum=0;
    for(int i=0;i<m;i++){
        vsum +=svd.w.fl(i);
    }
    float v=0;int k=0;
    for(k=0;k<m;k++){
        v+=svd.w.fl(k);
        if(v/vsum>=frac){
            k++;
            break;
        }
    }
    if(k>m)
        k=m;
    Mat D=svd.u(Rect(0,0,k,2*r));
    //combine bases
    V.create(2*r,4+k,CV_32F);
    Mat Vr=V(Rect(0,0,4,2*r));
    R.copyTo(Vr);
    Mat Vd=V(Rect(4,0,k,2*r));
    D.copyTo(Vd);
    //compute variance(normalized wrt scale)
    Mat Q=V.t()*X;
    for(int i=0;i<c;i++){
        float v=Q.fl(0,i);
        Mat q=Q.col(i);
        q/=v;
    }
    E.create(4+k,1,CV_32F);
    pow(Q,2,Q);
    for(int i=0;i<4+k;i++){
        if(i<4)
            E.fl(i)=-1;
        else
            E.fl(i)=Q.row(i).dot(Mat::ones(1,c,CV_32F))/(c-1);
    }
    //store connectivity
    if(con.size()>0){
        int m=con.size();
        C.create(m,2,CV_32F);
        for(int i=0;i<m;i++){
            C.at<int>(i,0)=con[i][0];
            C.at<int>(i,1)=con[i][1];
        }
    }else{
        C.create(r,2,CV_32F);
        for(int i=0;i<r-1;i++){
            C.at<int>(i,0)=i;
            C.at<int>(i,1)=i+1;
        }
        C.at<int>(r-1,0)=r-1;
        C.at<int>(r-1,1)=0;
    }


}
Mat ShapeModel::pts2mat(const vector<vector<Point2f>> &points) {
    int N=points.size();
    assert(N>0);
    int n=points[0].size();
    for(int i=1;i<N;i++){
        assert(int(points[i].size())==n);
    }
    Mat X(2*n,N,CV_32F);
    for(int i=0;i<N;i++){
        Mat x=X.col(i),
        y=Mat(points[i]).reshape(1,2*n);
        y.copyTo(x);
    }
    return X;
}
Mat ShapeModel::procrustes(const Mat &X, const int itol, const float ftol) {
    int c=X.cols,r=X.rows/2;
    //remove center of mass
    Mat P=X.clone();
    for(int i=0;i<c;i++){
        Mat p=P.col(i);
        float mx=0,my=0;
        for(int j=0;j<r;j++){
            mx +=p.fl(2*j);
            my +=p.fl(2*j+1);
        }
        mx/=r;
        my/=r;
        for(int j=0;j<r;j++){
            p.fl(2*j)-=mx;
            p.fl(2*j+1)-=my;
        }

    }
    Mat C_old;
    //optimise scale and rotation
    for(int iter=0;iter<itol;iter++){
        Mat C=P*Mat::ones(c,1,CV_32F);
        normalize(C,C);
        if(iter>0){
           if( norm(C,C_old)<ftol)
               break;
        }
        C_old=C.clone();
        for(int i=0;i<c;i++){
            Mat R=this->rot_scale_align(P.col(i),C);
            for(int j=0;j<r;j++){
                float x=P.fl(2*j,i),y=P.fl(2*j+1,i);
                P.fl(2*j,i)=R.fl(0,0)*x+R.fl(0,1)*y;
                P.fl(2*j+1,i)=R.fl(1,0)*x+R.fl(1,1)*y;
            }
        }

    }
    return P;
}
Mat ShapeModel::rot_scale_align(const Mat &src, const Mat &dst) {
    //construct linear system
    int r=src.rows/2;
    float a=0,b=0,d=0;
    for(int i=0;i<r;i++){
        d+=src.fl(2*i)*src.fl(2*i)+src.fl(2*i+1)*src.fl(2*i+1);
        a+=src.fl(2*i)*src.fl(2*i)+src.fl(2*i+1)*src.fl(2*i+1);
        b+=src.fl(2*i)+src.fl(2*i)+src.fl(2*i+1)*src.fl(2*i);
    }
    a/=d;
    b/=d;
    return (Mat_<float>(2,2)<<a,-b,b,a);
}

Mat ShapeModel::calc_rigid_basis(const Mat &X) {
    //compute mean shape
    int c=X.cols,r=X.rows/2;
    Mat mean=X*Mat::zeros(c,1,CV_32F)/r;
    //construct basis for similarity transform
    Mat R(2*r,4,CV_32F);
    for(int i=0;i<r;i++){
        R.fl(2*i,0)=mean.fl(2*i);
        R.fl(2*i+1,0)=mean.fl(2*i+1);
        R.fl(2*i,1)=-mean.fl(2*i+1);
        R.fl(2*i+1,1)=mean.fl(2*i);
        R.fl(2*i,2)=1.0;
        R.fl(2*i+1,2)=0.0;
        R.fl(2*i,3)=0.0;
        R.fl(2*i+1,3)=1.0;
    }
    for(int i=0;i<4;i++){
        Mat r=R.col(i);
        for(int j=0;j<i;j++){
            Mat b=R.col(j);
            r-=b*(b.t()*r);

        }
        normalize(r,r);
    }
    return R;
}
void ShapeModel::clamp(const float c) {
    double scale=P.fl(0);
    for(int i=0;i<E.rows;i++){
        if(E.fl(i)<0)
            continue;
        float v=c*sqrt(E.fl(i));
        if(fabs(P.fl(i)/scale)>v){
            if(P.fl(i)>0)
                P.fl(i)=v*scale;
            else{
                P.fl(i)=-v*scale;
            }
        }
    }

}
void ShapeModel::write(FileStorage &fs) const {
    assert(fs.isOpened());
    fs<<"{"<<"V"<<V<<"E"<<E<<"C"<<C<<"}";
}
void ShapeModel::read(const FileNode &node) {
    assert(node.type()==FileNode::MAP);
    node["V"]>>V;
    node["E"]>>E;
    node["C"]>>C;
    P=Mat::zeros(E.rows,1,CV_32F);
}