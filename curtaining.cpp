#include "curtaining.hpp"

Mat HPF1D(Mat img)
{
	Mat res = img * 0;

	int ksize = 2 * img.cols / 150 + 1;	// is always an odd number

	float* kernel = new float[ksize] {};

	for (int i = 0; i < ksize / 2; i++)
	{
		kernel[i] = -i - 1;
		kernel[ksize - i - 1] = -i - 1;
		kernel[ksize / 2] += 2 * (i + 1);
	}

	for (int i = ksize / 2 + 1; i < img.rows - ksize / 2 - 1; i++)
		for (int j = ksize; j < img.cols - ksize / 2; j++)
			if (img.at<uchar>(i, j))
			{
				float cell = 0.0f;

				for (int jj = 0; jj < ksize; jj++)
					cell += kernel[jj] * img.at<uchar>(i, j + jj - ksize / 2);

				if (cell < 0)
					res.at<uchar>(i, j) = 0;
				else if (cell > 255)
					res.at<uchar>(i, j) = 255;
				else
					res.at<uchar>(i, j) = (uchar)cell;
			}
	return res;
}

Mat HPF2D(Mat img, int flag)
{
	Mat res = img * 0;

	const int ksize = 5;
	/*float kernel[ksize][ksize]{ {-1, -1, 4, -1, -1},
								{-1, -1, 4, -1, -1},
								{-2, -2, 8, -2, -2},
								{-1, -1, 4, -1, -1},
								{-1, -1, 4, -1, -1} };*/

	float kernel[ksize][ksize]{ {-1, -1, -1, -1, -1},
								{-1, -1, -1, -1, -1},
								{-1, -1, 24, -1, -1},
								{-1, -1, -1, -1, -1},
								{-1, -1, -1, -1, -1} };

	if (flag == -1)
		for (int i = 0; i < ksize; i++)
			for (int j = 0; j < ksize; j++)
				kernel[i][j] *= -1.0f;

	for (int i = ksize / 2 + 1; i < img.rows - ksize / 2 - 1; i++)
		for (int j = ksize / 2 + 1; j < img.cols - ksize / 2 - 1; j++)
		{
			float cell = 0.0f;

			for (int ii = 0; ii < ksize; ii++)
				for (int jj = 0; jj < ksize; jj++)
					cell += kernel[ii][jj] * img.at<uchar>(i + ii - ksize / 2, j + jj - ksize / 2);

			if (cell < 0)
				res.at<uchar>(i, j) = 0;
			else if (cell > 255)
				res.at<uchar>(i, j) = 255;
			else
				res.at<uchar>(i, j) = (uchar)cell;
		}

	return res;
}

Mat LPF1D(Mat img)
{
	Mat res = img * 0;

	const int ksize = 3;

	//float kernel[ksize]{ 0.5, 0.5};
	float kernel[ksize]{ 1.0 / 3, 1.0 / 3, 1.0 / 3 };
	//float kernel[ksize]{ 1.0 / 4, 1.0 / 4, 1.0 / 4, 1.0 / 4 };

	for (int i = 0; i < img.rows - 1; i++)
		for (int j = 0; j < img.cols; j++)
		{
			float cell = 0.0f;

			for (int ii = 0; ii < ksize; ii++)
				cell += kernel[ii] * img.at<uchar>(i + ii, j);

			res.at<uchar>(i, j) = (uchar)cell;
		}

	return res;
}

Mat LPF2D(Mat img)
{
	Mat res = img * 0;

	const int ksize = 3;

	/*float kernel[ksize][ksize]{ {0, 0, 0, 0, 0},
								{0, 0, 1, 0, 0},
								{0, 1, 1, 1,0},
								{0, 0, 1, 0, 0},
								{0, 0, 0, 0, 0} };*/
	
	float kernel[ksize][ksize]{ {0, 1, 0},
								{1, 1, 1},
								{0, 1, 0} };

	for (int i = 0; i < ksize; i++)
		for (int j = 0; j < ksize; j++)
			kernel[i][j] /= 5.0f;

	for (int i = ksize / 2 + 1; i < img.rows - ksize / 2 - 1; i++)
		for (int j = ksize / 2 + 1; j < img.cols - ksize / 2 - 1; j++)
		{
			float cell = 0.0f;

			for (int ii = 0; ii < ksize; ii++)
				for (int jj = 0; jj < ksize; jj++)
					cell += kernel[ii][jj] * img.at<uchar>(i + ii - ksize / 2, j + jj - ksize / 2);

			res.at<uchar>(i, j) = (uchar)cell;
		}

	return res;
}

Mat binared(Mat img, int threshold)
{
	Mat temp = img * 0;
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<uchar>(i, j) > threshold)
				temp.at<uchar>(i, j) = 255;
	return temp;
}

Mat onlySurface(Mat img)
{
	Mat res(img.rows, img.cols, CV_8UC1);
	int medium = mean(img)[0];
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<uchar>(i, j) > medium * 1.1 ||
				img.at<uchar>(i, j) < medium * 0.9)
				res.at<uchar>(i, j) = 0;
			else res.at<uchar>(i, j) = img.at<uchar>(i, j);

	return res;
}

void cleanPores(Mat img, Mat mask)
{
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (!mask.at<uchar>(i, j))
				img.at<uchar>(i, j) = 0;
}

map<int, int> whitesCount(Mat img)
{
	/*
	 * function for counting non-zero pixels in each img column
	 *
	 * use it only for binared images (0 or 255 only)
	*/
	map<int, int> res;	// contains (-whitesCount, column) to sort by whites (from high to low)

	int* w255 = new int[img.cols] {};

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<uchar>(i, j))
				w255[j]++;


	for (int j = 0; j < img.cols; j++)
		res[-w255[j]] = j;		// minus for reverse sorting 

	delete[] w255;
	return res;
}

void detectLines(Mat img, uchar* curt_mask, map<int, int> whites)
{
	int max_width = img.cols / 150 - 2;		// - for 1 edge column, that is hard to detect,
	// and -1 for accuracy 

	int* was = new int [img.cols * img.rows] {};	// matrix of elements where we have already been

	int lines = 2;

	typedef pair<int, int> pr;
	auto iter_end = whites.begin();
	advance(iter_end, 125);
	for (auto iter = whites.begin(); lines > 0 || iter != iter_end; iter++)
	{			// go from whitest to blackest img column while it has curt-lines
		lines = 0;
		list<pr> line;	// list for pixels == 255. If size >=30, this is a line
		for (int i = 0; i < img.rows; i++)	// down the column
		{
			if (was[i * img.cols + iter->second])
				continue;
			if (img.at<uchar>(i, iter->second))	// assuming curt-line is a connected component (4-linked) 
			{
				stack<int> pixel;
				pixel.push(i * img.cols + iter->second);
				// index = i * img.cols + j, i = index / img.cols, j = index % img.cols

				while (!pixel.empty())
				{
					int row = pixel.top() / img.cols;
					int col = pixel.top() % img.cols;
					pixel.pop();

					was[row * img.cols + col] = 1;

					line.push_back({ row, col });

					if (img.at<uchar>(row + 1, col) && !was[(row + 1) * img.cols + col])
						pixel.push((row + 1) * img.cols + col);
					if (img.at<uchar>(row, col - 1) && !was[row * img.cols + col - 1]
						&& abs(iter->second - col) < max_width)
						pixel.push(row * img.cols + col - 1);	// going down the curt-line, checking neighbours
					if (img.at<uchar>(row, col + 1) && !was[row * img.cols + col + 1]
						&& abs(iter->second - col) < max_width)
						pixel.push(row * img.cols + col + 1);

				}
			}
			if (line.size() > img.rows / 4)
			{
				lines++;
				while (!line.empty())
				{
					curt_mask[line.front().first * img.cols + line.front().second] = 255;
					line.pop_front();
				}
			}
			else line.clear();
		}

		//cout << lines << endl;
	}
	delete[] was;
}

void specifyLines(Mat img, Mat curt_mask)
{
	list<int> nonEmptyCols;

	for (int j = 0; j < img.cols - 1; j++)
		for (int i = 0; i < img.rows; i++)
			if (curt_mask.at<uchar>(i, j))
			{
				nonEmptyCols.push_back(j);
				i = 0;
				j++;
			}

	int max_width = img.cols / 150 - 2;		// - for 1 edge column, that is hard to detect,
	// and -1 for accuracy 

	int* was = new int [img.cols * img.rows] {};	// matrix of elements where we have already been

	typedef pair<int, int> pr;

	for (auto iter = nonEmptyCols.begin(); iter != nonEmptyCols.end(); iter++)
	{
		list<pr> line;
		for (int i = 0; i < img.rows - 1; i++)
		{
			if (img.at<uchar>(i, *iter))
			{
				stack<int> pixel;
				pixel.push(i * img.cols + *iter);

				while (!pixel.empty())
				{
					int row = pixel.top() / img.cols;
					int col = pixel.top() % img.cols;
					pixel.pop();

					was[row * img.cols + col] = 1;

					line.push_back({ row, col });

					if (img.at<uchar>(row + 1, col) && !was[(row + 1) * img.cols + col])
						pixel.push((row + 1) * img.cols + col);
					if (img.at<uchar>(row, col - 1) && !was[row * img.cols + col - 1]
						&& abs(*iter - col) < max_width)
						pixel.push(row * img.cols + col - 1);	// going down the curt-line, checking neighbours
					if (img.at<uchar>(row, col + 1) && !was[row * img.cols + col + 1]
						&& abs(*iter - col) < max_width)
						pixel.push(row * img.cols + col + 1);

				}
			}
			if (line.size() > img.rows / 10)
				while (!line.empty())
				{
					curt_mask.at<uchar>(line.front().first, line.front().second) = 255;
					line.pop_front();
				}
			else line.clear();
		}
	}
	delete[] was;
}

bool inCurtainRange(uchar pixel, int med)
{
	int i_max = (255 - med) / 10 + 3;
	if (pixel > (med - i_max) && pixel < med * 0.99 || 
		pixel > med * 1.01 && pixel < (med + i_max) )
		return true;
	return false;
}

double median(Mat channel)
{
	double m = (channel.rows * channel.cols) / 2;
	int bin = 0;
	double med = -1.0;

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;
	Mat hist;
	calcHist(&channel, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	for (int i = 0; i < histSize && med < 0.0; ++i)
	{
		bin += cvRound(hist.at< float >(i));
		if (bin > m && med < 0.0)
			med = i;
	}

	return med;
}

Mat denoiseStripes(Mat img, Mat curts)
{
	Mat res = img.clone();
	int med = median(img);
	
	for (int i = 0; i < curts.rows; i++)
		for (int j = 0; j < curts.cols; j++)
			if (curts.at<uchar>(i, j) && inCurtainRange(img.at<uchar>(i, j), med))
				res.at<uchar>(i, j) = med;

	return res;
}
