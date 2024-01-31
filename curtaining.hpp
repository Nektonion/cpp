#pragma once

#ifndef CURTAINING_H
#define CURTAINING_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <map>
#include <list>
#include <stack>
#include <iostream>

using namespace cv;
using namespace std;
Mat HPF1D(Mat);

Mat HPF2D(Mat, int flag = 1);

Mat LPF1D(Mat);

Mat LPF2D(Mat);

Mat binared(Mat, int);

Mat onlySurface(Mat);

void cleanPores(Mat, Mat);

map<int, int> whitesCount(Mat);

void detectLines(Mat, uchar*, map<int, int>);

void specifyLines(Mat, Mat);

bool outtaMeanRange(uchar, int);

Mat denoiseStripes(Mat, Mat);

#endif // !CURTAINING_H



