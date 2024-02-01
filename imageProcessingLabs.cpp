#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
//#include <math.h>
#include <fstream>

using namespace std;
using namespace cv;

//   First lab

/*
int main()
{
	Mat img1 = imread("C:/Users/Asus/Desktop/images4labs/baboon.png", IMREAD_GRAYSCALE);
	Mat img2 = imread("C:/Users/Asus/Desktop/images4labs/Peppers.png", IMREAD_GRAYSCALE);
	Mat alpha_ch = imread("C:/Users/Asus/Desktop/images4labs/grad_y.png", IMREAD_GRAYSCALE);
	Mat res = img1 * 0;

	double one256 = 0.00390625;
	for (ushort i = 0; i < img1.rows; i++)
	{
		for (ushort j = 0; j < img1.cols; j++)
		{
			res.at<uchar>(i, j) = (1 - alpha_ch.at<uchar>(i, j) * one256) * img1.at<uchar>(i, j) + \
									alpha_ch.at<uchar>(i, j) * img2.at<uchar>(i, j) * one256;
		}
	}


	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/1.blending.png", res);
	namedWindow("1.blending", WINDOW_AUTOSIZE);
	imshow("1.blending", res);
	moveWindow("1.blending", 500, 150);
	waitKey(0);

	Mat res1 = res.clone();
	for (ushort i = 0; i < res1.rows; i++)
		for (ushort j = 0; j < res1.cols / 2 - 1; j++)
			swap(res1.at<uchar>(i, j), res1.at<uchar>(i, res1.cols - j - 1));

	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/1.vertical_reflecrtion.png", res1);
	namedWindow("1.vertical_reflecrtion", WINDOW_AUTOSIZE);
	imshow("1.vertical_reflecrtion", res1);
	moveWindow("1.vertical_reflecrtion", 500, 150);
	waitKey(0);

	Mat res2 = res.clone();
	for (ushort i = 0; i < res2.rows / 2 - 1; i++)
		for (ushort j = 0; j < res2.cols; j++)
			swap(res2.at<uchar>(i, j), res2.at<uchar>(res2.rows - i - 1, j));
	
	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/1.horizontal_reflecrtion.png", res2);
	namedWindow("1.horizontal_reflecrtion", WINDOW_AUTOSIZE);
	imshow("1.horizontal_reflecrtion", res2);
	moveWindow("1.horizontal_reflecrtion", 500, 150);
	waitKey(0);

	Mat res3 = res.clone();
	for (ushort i = 0; i < res3.rows; i++)
		for (ushort j = 0; j < i; j++)
		{
			swap(res3.at<uchar>(i, j), res3.at<uchar>(j, i));
		}

	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/1.transposition.png", res3);
	namedWindow("1.transposition", WINDOW_AUTOSIZE);
	imshow("1.transposition", res3);
	moveWindow("1.transposition", 500, 150);
	waitKey(0);

	destroyAllWindows();
	return 0;
}
*/

// Second lab

/*

void co_occurence(Mat img, ushort r, ushort c, ushort comatrix[])		// comatrix 256 x 256
{
	for (ushort i = 0; i < img.rows - r; i++)
		for (ushort j = 0; j < img.cols - c; j++)
			comatrix[img.at<uchar>(i + r, j + c) * 256 + img.at<uchar>(i, j)]++;
}

int main()
{
	const ushort N = 256;
	Mat img = imread("C:/Users/Asus/Desktop/images4labs/baboon.png", IMREAD_GRAYSCALE);
	Mat hist = img * 0;
	uint br[N]{};
	for(ushort i = 0; i < img.rows; i++)
		for(ushort j = 0; j < img.cols; j++)
			br[img.at<uchar>(i, j)]++;

	ushort factor = 0; // max amount of pixels with concrete brightness
	for (ushort i = 0; i < N; i++)
		factor = ((br[i] > factor) ? br[i] : factor);

	ushort step = (hist.cols / N);
	for (ushort i = 0; i < hist.rows; i += step)
		for (ushort j = 0; j < br[i/step] * hist.cols / factor; j++)
			hist.at<uchar>(i, j) = 255;

	rotate(hist, hist, ROTATE_90_COUNTERCLOCKWISE);

	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/2.brightness_hist.png", hist);
	namedWindow("2.brightness_hist", WINDOW_AUTOSIZE);
	imshow("2.brightness_hist", hist);
	moveWindow("2.brightness_hist", 500, 150);
	waitKey(0);
	destroyAllWindows();

	int normF = img.cols * img.rows;

	double meanV = 0;
	for (ushort i = 0; i < N; i++)
		meanV += i * br[i];	
	meanV /= normF;

	double variance = 0;
	for (ushort i = 0; i < N; i++)
		variance += pow(i - meanV, 2) * br[i];
	variance /= normF;

	double entropy = 0;
	for (ushort i = 0; i < N; i++)
		if (br[i] != 0)
			entropy -= br[i] * (log2(br[i]) - log2(normF));
	entropy /= normF;

	double uniformity = 0;
	for (ushort i = 0; i < N; i++)
		uniformity += double(br[i] * br[i]) / normF / normF;
	
	double skewness = 0;
	for (ushort i = 0; i < N; i++)
		skewness += pow((i - meanV), 3) * br[i];
	skewness *= (pow(variance, -3 / 2) / normF);

	double kurtosis = 0;
	for (ushort i = 0; i < N; i++)
		kurtosis += pow((i - meanV), 4) * br[i];
	kurtosis *= (pow(variance, -2) / normF);
	kurtosis -= 3;

	cout << "Mean value:\t" << meanV << endl;
	cout << "Variance:\t" << variance << endl;
	cout << "Entropy:\t" << entropy << endl;
	cout << "Uniformity:\t" << uniformity << endl;
	cout << "Skewness:\t" << skewness << endl;
	cout << "Kurtosis:\t" << kurtosis << endl;

	ushort comatrix[256 * 256]{};	// filled with 0
	ushort r = 2, c = 3;
	ofstream out;

	co_occurence(img, r, c, comatrix);
	out.open("comatrix.txt");

	long double co_energy = 0;
	for (ushort i = 0; i < 256; i++)
	{
		for (ushort j = 0; j < 256; j++)
		{
			out << comatrix[i * 256 + j] << " \t";
			co_energy += pow(comatrix[i * 256 + j], 2);
		}
		out << endl;
	}
	out.close();

	co_energy /= pow((img.cols - c) * (img.rows - r), 2);

	cout << "Co-matrix energy:\t" << co_energy << endl;

	return 0;
}
*/

// third lab

/*
float bicubic(float c, float r, Mat img)
{
	float res, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16;
	short ci = int(c);
	short ri = int(r);
	float x = c - ci;
	float y = r - ri;

	b1 = (x - 1) * (x - 2) * (x + 1) * (y - 1) * (y - 2) * (y + 1) / 4;
	b2 = -x * (x - 2) * (x + 1) * (y - 1) * (y - 2) * (y + 1) / 4;
	b3 = -(x - 1) * (x - 2) * (x + 1) * y * (y - 2) * (y + 1) / 4;
	b4 = x * (x - 2) * (x + 1) * y * (y - 2) * (y + 1) / 4;
	b5 = -x * (x - 1) * (x - 2) * (y - 1) * (y - 2) * (y + 1) / 12;
	b6 = -(x - 1) * (x - 2) * (x + 1) * y * (y - 1) * (y - 2) / 12;
	b7 = x * (x - 1) * (x - 2) * y * (y - 2) * (y + 1) / 12;
	b8 = x * (x - 2) * (x + 1) * y * (y - 1) * (y - 2) / 12;
	b9 = x * (x - 1) * (x + 1) * (y - 1) * (y - 2) * (y + 1) / 12;
	b10 = (x - 1) * (x - 2) * (x + 1) * y * (y - 1) * (y + 1) / 12;
	b11 = x * (x - 1) * (x - 2) * y * (y - 1) * (y - 2) / 36;
	b12 = -x * (x - 1) * (x + 1) * y * (y - 2) * (y + 1) / 12;
	b13 = -x * (x - 2) * (x + 1) * y * (y - 1) * (y + 1) / 12;
	b14 = -x * (x - 1) * (x + 1) * y * (y - 1) * (y - 2) / 36;
	b15 = -x * (x - 1) * (x - 2) * y * (y - 1) * (y + 1) / 36;
	b16 = x * (x - 1) * (x + 1) * y * (y - 1) * (y + 1) / 36;

	return res = b1 * img.at<uchar>(c, r) + b2 * img.at<uchar>(c, r + 1) + b3 * img.at<uchar>(c + 1, r) + \
		b4 * img.at<uchar>(c + 1, r + 1) + b5 * img.at<uchar>(c, r - 1) + b6 * img.at<uchar>(c - 1, r) + \
		b7 * img.at<uchar>(c + 1, r - 1) + b8 * img.at<uchar>(c - 1, r + 1) + b9 * img.at<uchar>(c, r + 2) + \
		b10 * img.at<uchar>(c + 2, r) + b11 * img.at<uchar>(c - 1, r - 1) + b12 * img.at<uchar>(c + 1, r + 2) + \
		b13 * img.at<uchar>(c + 2, r + 1) + b14 * img.at<uchar>(c - 1, r + 2) + b15 * img.at<uchar>(c + 2, r - 1) + \
		b16 * img.at<uchar>(c + 2, r + 2);
}

Mat turn(Mat img, float phi = 0)
{
	phi = phi * 3.14159265359 / 180;		// grad to rad
	ushort xc = img.cols / 2;
	ushort yc = img.rows / 2;
	float rm[9]{ cos(phi), sin(phi), 0,
				 -sin(phi), cos(phi), 0,
				 0		,	0		, 1 };
	//		xc * (1 - cos(phi)) + yc * sin(phi), yc * (1 - cos(phi)) - xc * sin(phi), 1 }; //includes center shifting
	Mat rot_mat(3, 3, CV_32FC1, rm);
	Mat inv_mat = rot_mat.inv();

	short xcorner1 = -xc * rm[0] - yc * rm[3];
	short xcorner2 = (img.cols - xc) * rm[0] + (img.rows - yc) * rm[3];
	short xcorner3 = (img.cols - xc) * rm[0] - yc * rm[3];
	short xcorner4 = (img.rows - yc) * rm[3] - xc * rm[0];

	short ycorner1 = -xc * rm[1] - yc * rm[4];
	short ycorner2 = (img.cols - xc) * rm[1] + (img.rows - yc) * rm[4];
	short ycorner3 = (img.cols - xc) * rm[1] - yc * rm[4];
	short ycorner4 = (img.rows - yc) * rm[4] - xc * rm[1];

	ushort cols = max(max(xcorner2, xcorner3), max(xcorner4, xcorner1)) - \
		min(min(xcorner2, xcorner3), min(xcorner4, xcorner1)) + 1;
	ushort rows = max(max(ycorner2, ycorner3), max(ycorner1, ycorner4)) - \
		min(min(ycorner2, ycorner3), min(ycorner1, ycorner4)) + 1;

	Mat result(rows, cols, CV_8UC1);
	short xc1 = cols / 2;
	short yc1 = rows / 2;
	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			float xback = (j - xc1) * inv_mat.at<float>(0, 0) + (i - yc1) * inv_mat.at<float>(1, 0) + inv_mat.at<float>(2, 0);
			float yback = (j - xc1) * inv_mat.at<float>(0, 1) + (i - yc1) * inv_mat.at<float>(1, 1) + inv_mat.at<float>(2, 1);

			if (xback >= (2 - xc) && xback <= (img.cols - 2 - xc) && yback >= (2 - yc) && yback <= (img.rows - 2 - yc))
			{
				result.at<uchar>(i, j) = bicubic(xback + xc, yback + yc, img);
			}
			else
				result.at<uchar>(i, j) = 0;
		}
	}

	return result;
}



int main()
{
	Mat img = imread("C:/Users/Asus/Desktop/images4labs/baboon.png", IMREAD_GRAYSCALE);

	Mat turned = turn(img, 30);

	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/3.gibon_turned.png", turned);
	namedWindow("3.gibon_turned", WINDOW_AUTOSIZE);
	imshow("3.gibon_turned", turned);
	moveWindow("3.gibon_turned", 500, 150);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
*/

// Fourth lab
/*

Mat Floyd_Steinberg(Mat img)
{
	Mat result = img * 0;
	for (ushort i = 0; i < img.rows; i++)
		for (ushort j = 0; j < img.cols; j++)
		{
			int err;
			if (img.at<uchar>(i, j) >= 128)
			{
				err = -255 + img.at<uchar>(i, j); 
				result.at<uchar>(i, j) = 255;
			}
			else
			{
				err = img.at<uchar>(i, j);
				result.at<uchar>(i, j) = 0;
			}

			int r_err = 7 * err / 16;
			if ((j + 1) < img.cols)
				if(img.at<uchar>(i, j + 1) + r_err > 255)
					img.at<uchar>(i, j + 1) = 255;
				else
					img.at<uchar>(i, j + 1) += r_err;
			
			int d_err = 5 * err / 16;
			if ((i + 1) < img.rows)
				if(img.at<uchar>(i + 1, j) + d_err > 255)
					img.at<uchar>(i + 1, j) = 255;
				else
					img.at<uchar>(i + 1, j) += d_err;

			int dl_err = 3 * err / 16;
			if (j > 0 && (i + 1) < img.rows)
				if(img.at<uchar>(i + 1, j - 1) + dl_err > 255)
					img.at<uchar>(i + 1, j - 1) = 255;
				else
					img.at<uchar>(i + 1, j - 1) += dl_err;

			int	 dr_err = err / 16;
			if ((j + 1) < img.cols && (i + 1) < img.rows)
				if(img.at<uchar>(i + 1, j + 1) + dr_err > 255)
					img.at<uchar>(i + 1, j + 1) = 255;
				else
					img.at<uchar>(i + 1, j + 1) += dr_err;
		}

	return result;
}

Mat negative(Mat img)
{
	for (ushort i = 0; i < img.rows; i++)
		for (ushort j = 0; j < img.cols; j++)
			img.at<uchar>(i, j) = 255 - img.at<uchar>(i, j);
	return img;
}

int main()
{
	//Mat img = imread("C:/Users/Asus/Desktop/images4labs/baboon.png", IMREAD_GRAYSCALE);
	Mat img = imread("C:/Users/Asus/Desktop/images4labs/Lena.png", IMREAD_GRAYSCALE);

	Mat binared = Floyd_Steinberg(img);
	//binared = negative(binared);
	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/4.Floyd_Steinberg1.png", binared);
	namedWindow("4.Floyd_Steinberg", WINDOW_AUTOSIZE);
	imshow("4.Floyd_Steinberg", binared);
	moveWindow("4.Floyd_Steinberg", 500, 150);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
*/

// 5th lab
/*
Mat convolution(Mat img)
{
	Mat res = img * 0;
	ushort flag = 0;
	// enter the convolution kernel and size:
	cout << "Enter 1 for LPF, 2 for HPF, 3 for sharpening filter:" << endl;
	cin >> flag;
	const uchar ksize = 5;
	float kernel[ksize][ksize];
	if (flag == 1)
	{
		cout << 1 << endl;
		float ker[ksize][ksize]{    {0, 0, 1, 0, 0},
									{0, 1, 1, 1, 0},
									{1, 1, 2, 1, 1},
									{0, 1, 1, 1, 0},
									{0, 0, 1, 0, 0} };
		for (uchar i = 0; i < ksize; i++)
			for (uchar j = 0; j < ksize; j++)
				kernel[i][j] = ker[i][j];
	}
	else if (flag == 2)
	{
		cout << 2 << endl;
		float ker[ksize][ksize]{    {0, 1, 1, 1, 0},
									{1, -2, -2, -2, 1},
									{1, -2, 4, -2, 1},
									{1, -2, -2, -2, 1},
									{0, 1, 1, 1, 0} };
		for (uchar i = 0; i < ksize; i++)
			for (uchar j = 0; j < ksize; j++)
				kernel[i][j] = ker[i][j];
	}	
	else if (flag == 3)
	{
		cout << 3 << endl;
		float ker[ksize][ksize]{    {-1, -1, -1, -1, -1},
									{-1, 3, 3, 3, -1},
									{-1, 3, 16, 3, -1},
									{-1, 3, 3, 3, -1},
									{-1, -1, -1, -1, -1} };
		for (uchar i = 0; i < ksize; i++)
			for (uchar j = 0; j < ksize; j++)
				kernel[i][j] = ker[i][j];
	}
	else if (flag > 3)
	{
		cout << 0 << endl;
		float ker[ksize][ksize]{    {1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1} };
		for (uchar i = 0; i < ksize; i++)
			for (uchar j = 0; j < ksize; j++)
				kernel[i][j] = ker[i][j];
	}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			cout << kernel[i][j] << " ";
			if (j == 4)
				cout << endl;
		}

	// normalization
	if (flag != 2)
	{
		ushort ksum = 0;
		for (uchar i = 0; i < ksize; i++)
			for (uchar j = 0; j < ksize; j++)
				ksum += kernel[i][j];
		for (uchar i = 0; i < ksize; i++)
			for (uchar j = 0; j < ksize; j++)
				kernel[i][j] /= ksum;
	}
	

	for (ushort i = 0; i < img.rows; i++)
		for (ushort j = 0; j < img.cols; j++)
		{
			float cell = 0.0f;
			uchar is, ie, js, je;	// start, end
			is = (i == 0 ? 1 : 0);
			js = (j == 0 ? 1 : 0);
			ie = ( (i == img.rows - 1) ? (ksize - 1) : ksize);
			je = ( (j == img.cols - 1) ? (ksize - 1) : ksize);

			for (uchar ii = is; ii < ie; ii++)
				for (uchar jj = js; jj < je; jj++)
					cell += kernel[ii][jj] * img.at<uchar>(i - is + ii, j - js + jj);

			if (cell < 0)
				res.at<uchar>(i, j) = 0;
			else
			res.at<uchar>(i, j) = (uchar)cell;
		}

	return res;
}

int main()
{
	//Mat img = imread("C:/Users/Asus/Desktop/images4labs/baboon_blured.png", IMREAD_GRAYSCALE);
	Mat img = imread("C:/Users/Asus/Desktop/images4labs/baboon.png", IMREAD_GRAYSCALE);

	Mat img_conv = convolution(img);
	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/5.HPF.png", img_conv);
	namedWindow("5.convolution", WINDOW_AUTOSIZE);
	imshow("5.convolution", img_conv);
	moveWindow("5.convolution", 500, 150);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
*/

// 6th lab
/*

Mat order_statistic(Mat img)
{
	Mat res = img * 0;
	
	const uchar ksize = 5;
	float kernel[ksize][ksize]{     {0, 0, 1, 0, 0},
									{0, 1, 1, 1, 0},
									{1, 1, 1, 1, 1},
									{0, 1, 1, 1, 0},
									{0, 0, 1, 0, 0} };

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			vector<int> list;	// of img elements	
			int is, ie, js, je;	// start, end
			is = (i == 0 ? 1 : 0);
			js = (j == 0 ? 1 : 0);
			ie = ((i == img.rows - 1) ? (ksize - 1) : ksize);
			je = ((j == img.cols - 1) ? (ksize - 1) : ksize);

			for (int ii = is; ii < ie; ii++)
				for (int jj = js; jj < je; jj++)
					if (kernel[ii][jj])
						list.push_back(img.at<uchar>(i - is + ii, j - js + jj));
			
			sort(list.begin(), list.end());
			res.at<uchar>(i, j) = list[list.size() / 2];
		}

	return res;
}

int main()
{
	//Mat img = imread("C:/Users/Asus/Desktop/images4labs/barbara_noise.png", IMREAD_GRAYSCALE);
	Mat img = imread("C:/Users/Asus/Desktop/images4labs/Chrom.png", IMREAD_GRAYSCALE);

	Mat filtered = order_statistic(img);
	imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/6.order_statistic_3.png", filtered);
	namedWindow("6.order_statistic", WINDOW_AUTOSIZE);
	imshow("6.order_statistic", filtered);
	moveWindow("6.order_statistic", 500, 150);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
*/

// 7th lab
///*

#include <stack>
#include<time.h>

//int clr = 20;

Mat binared(Mat img)
{
	Mat temp = img * 0;
	//int med = mean(img)[0];
	int med = 157;
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<uchar>(i, j) > med)
				temp.at<uchar>(i, j) = 1; 
	return temp;
}

void rgb_rand(int rgb[])
{
	for (int i = 0; i < 3; i++)
		rgb[i] = rand() % 256;
}

void floodFill8(Mat img, int x, int y, Mat res)
{
	static const int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 }; 
	static const int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int clr[3];
	typedef pair<int, int> ii;
	stack<ii> Stack;

	Stack.push(ii(x, y));
	rgb_rand(clr);
	while (!Stack.empty()) 
	{ 
		x = Stack.top().first;
		y = Stack.top().second;
		//cout << (int)img.at<uchar>(x, y) << " " << x << " " << y << endl;
		Stack.pop();
		img.at<uchar>(x, y) = 0;
		for (int i = 0; i < 3; i++)
			res.at<Vec3b>(x, y).val[i] = clr[i];
			
		for (int i = 0; i < 8; i++) 
		{
			int nx = x + dx[i]; 
			int ny = y + dy[i];
			if (nx >= 0 && nx < img.cols && ny >= 0 && ny < img.rows)
			{
				if(img.at<uchar>(nx, ny) == 1)
					Stack.push(ii(nx, ny));
			}
		}
		//cout << "len: " << Stack.size() << endl;
	}
}

void GeomMom(Mat img, int x, int y, Mat orig)
{
	Mat cpy = img.clone();
	unsigned long m00 = 0;
	unsigned long m01 = 0;
	unsigned long m10 = 0;

	int x0 = x; // x-y backup
	int y0 = y;

	static const int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	static const int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int clr[3];
	typedef pair<int, int> ii;
	stack<ii> Stack;

	Stack.push(ii(x, y));
	while (!Stack.empty())
	{
		x = Stack.top().first;
		y = Stack.top().second;
		Stack.pop();

		for (int i = 0; i < 3; i++)
		{
			clr[i] = (int)img.at<Vec3b>(x, y).val[i];
			img.at<Vec3b>(x, y).val[i] = 0;
			//cout << clr[i] << " ";
		}
		//cout << endl;
		//cout << Stack.size() << endl;
		m00 += 1 * orig.at<uchar>(x, y);
		m01 += x * orig.at<uchar>(x, y);
		m10 += y * orig.at<uchar>(x, y);

		for (int i = 0; i < 8; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < img.cols && ny >= 0 && ny < img.rows)
			{
				if ((int)img.at<Vec3b>(nx, ny).val[0] == clr[0] && \
					(int)img.at<Vec3b>(nx, ny).val[1] == clr[1] && \
					(int)img.at<Vec3b>(nx, ny).val[2] == clr[2] && \
					clr[0] + clr[1] + clr[2] > 0)
				{
					Stack.push(ii(nx, ny));
				}
			}
		}
	}
	//cout << m00 << endl;
	if (m00 > 500)
	{
		ofstream out;
		out.open("GeometryMoments.txt", ios_base::app);
		out << "Next part:\n";
		out << "m_00: " << m00 << endl;
		out << "m_10: " << m10 << endl;
		out << "m_01: " << m01 << endl;
	
		long double xc = (long double)m10 / m00 ;
		long double yc = (long double)m01 / m00;
		long double mu02 = 0.0f;
		long double mu20 = 0.0f;
		long double mu11 = 0.0f;

		Stack.push(ii(x0, y0));
		while (!Stack.empty())
		{
			x = Stack.top().first;
			y = Stack.top().second;
			Stack.pop();

			for (int i = 0; i < 3; i++)
			{
				clr[i] = (int)cpy.at<Vec3b>(x, y).val[i];
				cpy.at<Vec3b>(x, y).val[i] = 0;
				//cout << clr[i] << " ";
			}
			//cout << endl;
			//cout << Stack.size() << endl;
			mu20 += (long double)orig.at<uchar>(x, y) * (xc - x) * (xc - x);
			mu02 += (long double)orig.at<uchar>(x, y) * (yc - y) * (yc - y);
			mu11 += (long double)orig.at<uchar>(x, y) * (y - yc) * (x - xc);

			for (int i = 0; i < 8; i++)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx >= 0 && nx < cpy.cols && ny >= 0 && ny < cpy.rows)
					if ((int)cpy.at<Vec3b>(nx, ny).val[0] == clr[0] && \
						(int)cpy.at<Vec3b>(nx, ny).val[1] == clr[1] && \
						(int)cpy.at<Vec3b>(nx, ny).val[2] == clr[2] && \
						clr[0] + clr[1] + clr[2] > 0)
						Stack.push(ii(nx, ny));
			}
		}
		out << "mu02: " << mu02 << endl;
		out << "mu20: " << mu20 << endl;
		out << "mu11: " << mu11 << endl;
		out << endl;
		out.close();
	}
}

int main()
{
	srand(time(0));
	Mat img = imread("C:/Users/Asus/Desktop/images4labs/Lena.png", IMREAD_GRAYSCALE);
	Mat res = Mat(img.rows, img.cols, CV_8UC3, Scalar(0,0,0));
	
	Mat img_bin = binared(img);
	
	for (int i = 0; i < img_bin.rows; i++)
		for (int j = 0; j < img_bin.cols; j++)
			if (img_bin.at<uchar>(i, j) == 1)
				floodFill8(img_bin, i, j, res);


	namedWindow("7.floodFill", WINDOW_AUTOSIZE);
	imshow("7.floodFill", res);
	moveWindow("7.floodFill", 500, 150);
	waitKey(0);
	destroyAllWindows();

	Mat res2 = res.clone();

	for (int i = 0; i < res.rows; i++)
		for (int j = 0; j < res.cols; j++)
			if ((int)res.at<Vec3b>(i, j).val[0] + \
				(int)res.at<Vec3b>(i, j).val[1] + \
				(int)res.at<Vec3b>(i, j).val[2] > 0)
				GeomMom(res, i, j, img);	
	

	//imwrite("C:/Users/Asus/Desktop/2 СЕМ/Комп. обработка изображений/7.floodFill3.png", res);


	img.release(); 
	return 0;
}
//*/