//#include <iostream>
#include "curtaining.hpp"

int main()
{
	auto start = chrono::high_resolution_clock::now();

	Mat img = imread("0_cleaned.png", IMREAD_GRAYSCALE);
	Mat hpf = HPF2D(onlySurface(img));
	//Mat anti_hpf = HPF2D(img, -1);
	Mat binary = binared(hpf, 250);				// detect brigth lines
	//Mat anti_binary = binared(anti_hpf, 253);
	//imshow("binary", binary);
	//imshow("anti_binary", anti_binary);
	//waitKey(0);

	Mat result = binary.clone();


	morphologyEx(result, result, 3, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1));

	imshow("result", result);
	imshow("binary", binary);
	waitKey(0);

	int its = 2;
	//MORPH_CROSS	MORPH_RECT

	morphologyEx(result, result, 3, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), its);
	
	imshow("result", result);
	imshow("binary", binary);
	waitKey(0);

	/*morphologyEx(result, result, 2, getStructuringElement(MORPH_CROSS, Size(3, 3)), Point(-1, -1));
	imshow("result", result);
	imshow("binary", binary);
	waitKey(0);*/



	//Mat surf = onlySurface(img);
	//Mat hpf = HPF2D(surf);
	//Mat anti_hpf = HPF2D(surf, -1);
	//Mat binary = binared(hpf, 40);				// detect brigth lines
	//Mat anti_binary = binared(anti_hpf, 40);
	//imshow("binary", binary);
	//imshow("anti_binary", anti_binary);
	//waitKey(0);
	//
	//Mat lpf = LPF1D(HPF2D(surf));
	//Mat anti_lpf = LPF1D(HPF2D(surf, -1));*/

	//imshow("hpf", lpf);
	//imshow("anti_hpf", anti_lpf);
	//imwrite("lpf.png", lpf);
	//imwrite("anti_lpf.png", anti_lpf);
	//waitKey(0);

	//Mat binary = binared(lpf, 20);				// detect brigth lines
	//Mat anti_binary = binared(anti_lpf, 20);		// detect dark lines, flag == -1
	//

	//imwrite("binary.png", binary);
	//imwrite("anti_binary.png", anti_binary);
	//imshow("binary", binary);
	//imshow("anti_binary", anti_binary);
	//waitKey(0);

	//map<int, int> whites = whitesCount(binary);
	//map<int, int> anti_whites = whitesCount(anti_binary);

	//uchar* curt_mask = new uchar[img.cols * img.rows] {};
	//uchar* anti_curt_mask = new uchar[img.cols * img.rows]{};

	//detectLines(binary, curt_mask, whites);
	//detectLines(anti_binary, anti_curt_mask, anti_whites);

	//Mat mask(img.cols, img.rows, CV_8UC1);
	//Mat anti_mask(img.cols, img.rows, CV_8UC1);

	//memcpy(mask.data, curt_mask, img.rows * img.cols * sizeof(uchar));
	//memcpy(anti_mask.data, anti_curt_mask, img.rows * img.cols * sizeof(uchar));

	//delete[] curt_mask;
	//delete[] anti_curt_mask;

	//imshow("mask", mask);
	//imshow("anti_mask", anti_mask);
	//imwrite("anti_mask.png", anti_mask);
	//imwrite("mask.png", mask);
	//waitKey(0);

	//specifyLines(binary, mask);
	//specifyLines(anti_binary, anti_mask);


	//imshow("mask", mask);
	//imshow("anti_mask", anti_mask);
	//imwrite("anti_mask1.png", anti_mask);
	//imwrite("mask1.png", mask);
	//waitKey(0);

	//Mat result = denoiseStripes(img, mask);
	//result = denoiseStripes(result, anti_mask);

	//auto stop = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	//cout << duration.count() * pow(10, -6) << " sec" << endl;

	//imwrite("0_cleaned.png", result);
	//imshow("img", img);
	//imshow("result", result);
	//waitKey(0);
	

	destroyAllWindows();

	return 0;
}
