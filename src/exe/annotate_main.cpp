//
// Created by root on 2019/8/11.
//

#include "base.h"
#include <iostream>
#include <fstream>
#include "annotate.h"
#include "muct_data.h"
using  namespace std;
using namespace cv;
bool parse_help(int argc,char **argv){
    for(int i=0;i<argc;i++){
        string str=argv[i];
        if(str.length()==2){
            if(strcmp(str.c_str(),"-h")==0)
                return true;
        }
        if(str.length()==6){
            if(strcmp(str.c_str(),"--help")==0){
                return true;
            }
        }
    }
    return false;
}
string parse_odir(int argc,char **argv){
    string odir="data/";
    for(int i=0;i<argc;i++){
        string str=argv[i];
        if(str.length()!=2)
            continue;
        if(strcmp(str.c_str(),"-d")==0){
            if(argc>i+1)
            {
                odir=argv[i+1];
                break;
            }
        }
    }
    if(odir[odir.length()-1]!='/')
        odir+"/";
    return odir;
}

int
parse_ifile(int argc,
            char** argv,
            string& ifile)
{
    for(int i = 1; i < argc; i++){
        string str = argv[i];
        if(str.length() != 2)continue;
        if(strcmp(str.c_str(),"-m") == 0){ //MUCT data
            if(argc > i+1){ifile = argv[i+1]; return 2;}
        }
        if(strcmp(str.c_str(),"-v") == 0){ //video file
            if(argc > i+1){ifile = argv[i+1]; return 1;}
        }
    }
    ifile = ""; return 0;
}
int main(int argc,char **argv){
  if(parse_help(argc,argv)){
    cout<<"usage: ./annotate [-v video] [-m muct_dir] [-d output]"<<endl;
    return 0;
  }
  string odir=parse_odir(argc,argv);
  cout<<"odir="<<odir<<endl;
  string ifile;
  int type=2;parse_ifile(argc,argv,ifile);
   cout<<"type="<<type<<endl;
   string fname=odir+"annotations.yaml";
   fname="/media/wangbin/36005E93005E59C7/face_tracker_detector/res/annotations.ymal";
   ifile="/media/wangbin/36005E93005E59C7/muct/";
    namedWindow(annotation.wname);
   if(type==2){//MUCT data
       string imfile=ifile+"muct-landmarks/muct76-opencv.csv";
       ifstream file(imfile.c_str());
       if(!file.is_open()){
           cerr<<"Failed opening"<<imfile.c_str()<<" for reading"<<endl;
       }
       string str;
       while (!file.eof()&&getline(file,str)){
           if(str.length()==0)
               break;
        //   cout<<str<<endl;

           MuctData d(str,ifile);
           if(d.name.length()==0)
               continue;
           annotation.data.imnames.push_back(d.name);
           annotation.data.points.push_back(d.points);
       }
       file.close();
       annotation.data.rm_incomplete_samples();

   }else{
       VideoCapture cam;
       if(type==1)
         cam.open(ifile);
         else{
             cam.open(0);

         }
         if(!cam.isOpened()){
             cout<<"Failed opening video file."<<endl
             <<"usage: ./annotate [-v video] [-m mudct_dir] [-d output]"<<endl;
             return 0;
         }


   }
    for(auto name:annotation.data.imnames){
        cout<<"name1= "<<name <<endl;
    }

   save_ft(fname.c_str(),annotation.data);
   for(int i=0;i<annotation.data.points.size();i++){
       cout<<"name="<<annotation.data.imnames[i];
       for(int j=0;j<annotation.data.points[i].size();j++){
           cout<<"i="<<i<<",j="<<j<<",x="<<annotation.data.points[i][j].x<<",y="<<annotation.data.points[i][j].y<<endl;
       }
       cout<<endl;
   }
   setMouseCallback(annotation.wname,pc_MouseCallback,0);
   annotation.set_connectivity_instructions();
   annotation.set_current_image(0);
   annotation.draw_instructions();
;
    while (1){
       annotation.draw_connections();
       imshow(annotation.wname,annotation.image);
       if(waitKey(0)=='q')
           break;
   }
    cout<<"fname="<<fname.c_str()<<endl;
    save_ft(fname.c_str(),annotation.data);
   //annotate symmetry
   setMouseCallback(annotation.wname,ps_MouseCallback,0);
   annotation.initialize_symmetry(0);
   annotation.set_symmetry_instructions();
   annotation.set_current_image(0);
   annotation.draw_instructions();
   annotation.idx=0;
   annotation.pidx=-1;

     while (1){
       annotation.draw_symmetry();
       imshow(annotation.wname,annotation.image);
       if(waitKey(0)=='q')
           break;
   }
     cout<<"fname="<<fname.c_str()<<endl;
    save_ft(fname.c_str(),annotation.data);
    destroyWindow("Annotate");
    return 0;
}