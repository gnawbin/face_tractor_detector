//
// Created by root on 2019/8/11.
//

#ifndef FACE_TRACKER_DETECTOR_MUCT_DATA_H
#define FACE_TRACKER_DETECTOR_MUCT_DATA_H

#include "face_tractor_data.h"
#include <iostream>
#include <fstream>
using  namespace std;
using namespace cv;
class MuctData {
public:
    string name;
    string index;
    vector<Point2f> points;
    MuctData(string str,string muct_dir){
        size_t p1=0,p2;
        string idir=muct_dir;
        if(idir[idir.length()-1]!='/') idir+="/";
        idir+="jpg/";
        p2=str.find(",");
        if(p2==string::npos){
            cerr<<"Invalid MUCT file"<<endl;
            exit(0);
        }
        if(strcmp(name.c_str(),"i434xe-fn")==0||(name[1]=='r'))
           name="";
        else{
            name=idir+str.substr(p1,p2-p1)+".jpg";
            p1=p2+1;
          //  cout<<"name="<<name<<endl;
            p2=str.find(",",p1);
            if(p2==string::npos){
                cerr<<"Invalid MUCT file"<<endl;
            }
            index=str.substr(p1,p2-p1);
            p1=p2+1;
            //cout<<"index="<<index<<endl;
            for(int i=0;i<75;i++){
                p2=str.find(",",p1);
                if(p2==string::npos){cerr<<"Invalid MUCT file"<<endl;exit(0);}
                string x=str.substr(p1,p2-p1);
                p1=p2+1;
                p2=str.find(",",p1);
                if(p2 == string::npos){cerr << "Invalid MUCT file" << endl; exit(0);}
                string y=str.substr(p1,p2-p1);
                p1=p2+1;
                points.push_back(Point2f(atoi(x.c_str()),atoi(y.c_str())));
            }
            p2 = str.find(",",p1);
            if(p2 == string::npos){cerr << "Invalid MUCT file" << endl; exit(0);}
            string x = str.substr(p1,p2-p1); p1 = p2+1;
            string y = str.substr(p1,str.length()-p1);
            points.push_back(Point2f(atoi(x.c_str()),atoi(y.c_str())));
         //   cout<<"points siz/e="<<points.size()<<endl;
          //  for(Point2f point:points){
               // cout<<"x="<<point.x<<"y="<<point.y<<endl;
            //}
        }
    }
};


#endif //FACE_TRACKER_DETECTOR_MUCT_DATA_H
