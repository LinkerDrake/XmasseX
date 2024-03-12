
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace cv;

using namespace std;
/*
int main(int argc, char const* argv[]) {
    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0, apiID = cv::CAP_ANY;
    cap.open(deviceID, apiID);

    if (!cap.isOpened()) {
        std::cerr << "Error open camera\n";
        return -1;
    }
    cout << "Start" << endl;
    for (;;) {
        cap.read(frame);
        if (frame.empty()) {
            std::cerr << "Error blank frame\n";
            break;
        }
        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }

    */

Mat dilate(Mat const& s)
{
    int Ny = s.rows;
    int Nx = s.cols;
    Mat d(Ny, Nx, CV_8U);

    for (int y = 1; y < Ny - 1; ++y)
    {
        uchar const* ps0 = s.ptr<uchar>(y - 1);
        uchar const* ps1 = s.ptr<uchar>(y);
        uchar const* ps2 = s.ptr<uchar>(y + 1);
        uchar* pd = d.ptr<uchar>(y);

        for (int x = 1; x < Nx - 1; ++x)
        {
            pd[x] = 1.0/9.0*(
                ps0[x - 1]+ ps0[x]+ ps0[x + 1]+
                ps1[x - 1]+ ps1[x]+ ps1[x + 1]+
                ps2[x - 1]+ ps2[x]+ ps2[x + 1]
            );
        }
    }
    return d;
};



Mat dilate1(Mat const& s, int param)
{
    int Ny = s.rows;
    int Nx = s.cols;
    Mat d(Ny, Nx, CV_8U);
    int boundary = (int)(param / 2.0);



    for (int y = boundary; y < Ny - boundary; ++y)
    {

        uchar** arr = new uchar*[param];

        for (int counter = 0; counter < param; ++counter) 
        {
            arr[counter] = (uchar*)s.ptr<uchar>(y - boundary + counter);
        }


        
        /*
        uchar const* ps0 = s.ptr<uchar>(y - 1);
        uchar const* ps1 = s.ptr<uchar>(y);
        uchar const* ps2 = s.ptr<uchar>(y + 1);
        */

        uchar* pd = d.ptr<uchar>(y);
        


        for (int x = boundary; x < Nx - boundary; ++x)
        {   
            pd[x] = 0;
            for (int i = 0; i < param; ++i) {
                for (int j = 0; j < param; ++j) {

                    
                    pd[x] += 1.0 / param/param * arr[i][x - boundary + j];
                }

            }
        };


        /*

        for (int x = 1; x < Nx - 1; ++x)
        {
            pd[x] = 1.0/9.0*(
                ps0[x - 1] + ps0[x] + ps0[x + 1]+
                ps1[x - 1] + ps1[x] + ps1[x + 1]+
                ps2[x - 1] + ps2[x] + ps2[x + 1]
            );
        }

        */

        delete[] arr;
    }
    return d;
};




int main(){

    Mat image = imread("C:/Users/user/Downloads/flower.png", 0);
    
    



    //cv::Mat image_blurred_with_5x5_kernel;
    //cv::GaussianBlur(image, image_blurred_with_5x5_kernel, Size(5, 5), 0);
    

    Mat obj = dilate1(image, 15);
    Mat obj_0 = dilate(image);




    cv::namedWindow("image", 0);
    cv::resizeWindow("image", 300, 300);
    cv::imshow("image", obj);

    cv::namedWindow("image_0", 0);
    cv::resizeWindow("image_0", 300, 300);

    cv::imshow("image_0", obj_0);


    while (cv::waitKey(0) != 'q') {}
    return 0;

    //while (cv::waitKey(0) != 'q') {};














    //return 0;
}