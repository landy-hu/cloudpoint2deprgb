#include<iostream>
#include<string>
using namespace std;

#include <XnCppWrapper.h> 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <boost/concept_check.hpp>
#include <pcl-1.7/pcl/common/concatenate.h>
using namespace cv;
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

const double camera_factor=1000;
const double camera_cx=325.5;
const double camera_cy=253.5;
const double camera_fx=518.0;
const double camera_fy=519.0;
 
int main(int argc, char **argv)
{ 
  //Define a PointCloud to load the PCD File.
  PointCloud::Ptr cloud(new PointCloud);
  if(pcl::io::loadPCDFile<PointT>("/home/lan-hu/Documents/slambook/cloudpoint/src/data/pointcloud.pcd",*cloud)==-1)
    cout<<"ERROR: loading pcd file fails"<<endl;
  
  //The number of points
  int pointsize = cloud->points.size();
   
  //get the size of the picture
  int m=480,n=640;
  cout<<"The size of the picture is "<< m << "*" << n << endl;
  // Initialize the Mat of rgb image and depth image
  cv::Mat rgb(m, n, CV_8UC3), depth(m, n, CV_8UC1);
    
   
  // calculation loop for rgb image and depth image  
  for (int i=0; i<pointsize; i++)
  { 
    // In order to get get rows
    int temp = i / n;
     
    // In order to get the cols
    int base = i - 640 * temp;
    /* The following does not work */
    //rgb.ptr<uchar>(temp, base)[0] = cloud->points[i].b;
    //rgb.ptr<uchar>(temp, base)[1] = cloud->points[i].g;
    //rgb.ptr<uchar>(temp, base)[2] = cloud->points[i].r;
    
    // calculate pixel RGB color
    rgb.at<Vec3b>(temp, base)[0] = cloud->points[i].b;
    rgb.at<Vec3b>(temp, base)[1] = cloud->points[i].g;
    rgb.at<Vec3b>(temp, base)[2] = cloud->points[i].r;
    // calculate pixel DEPTH
    depth.at<uchar>(temp,base)   = cloud->points[i].z*camera_factor;
     
  } // End of for
  
  /* To show the image of rgb and depth */
  // namedWindow("rgb");
  // imshow("rgb",rgb);
  // cv::waitKey(0);
  // namedWindow("depth");
  // cv::imshow("depth",depth);
  // cv::waitKey(0);
  
  // Save the image file
  cv::imwrite("/home/lan-hu/rgb.png", rgb);
  cv::imwrite("/home/lan-hu/depth.png", depth);
  
  cloud->points.clear();
  return 0; 
}
