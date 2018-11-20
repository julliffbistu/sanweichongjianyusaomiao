#include <iostream>  
#include <string>  
#include <iostream> 
#include <opencv2/opencv.hpp>
#include <opencv/ml.h>
#include "fstream"

using namespace std;  
using namespace cv;

cv::Mat read_data_from_csv(const char *filepath)
{
	fstream fin(filepath, ios::in);
	string   lines;
	int n_samples=0;
	while (std::getline(fin, lines))
	{
		n_samples++;
	}
	fin.close();
	//cout << filepath;
	fin.open(filepath, ios::in);
	getline(fin,lines);
	int numofcols;
	int i= 1;
	int pos = 0;
	int count = 1;
	for (i = 0; i < lines.length(); i++)
	{
		if (lines.at(i) == ',')
			count++;
	}

	cv::Mat image(n_samples,count,  CV_32F ); 
	string pixel;
	ifstream file(filepath, ifstream::in);
	if (!file)
		cout << "CSV read fail" << endl;
	int nl = image.rows;  // number of lines     
	int nc = image.cols; // number of columns     
	int eolElem = image.cols - 1;       //每行最后一个元素的下标  
	int elemCount = 0;
	if (image.isContinuous())
	{
		nc = nc*nl;    // then no padded pixels     
		nl = 1;        // it is now a 1D array     
	}
	for (int i = 0; i<nl; i++)
	{
		float* data = (float*)image.ptr<ushort>(i);
		for (int j = 0; j < nc; j++)
		{
			if (elemCount == eolElem)
			{
				getline(file, pixel, '\n');               //任意地读入，直到读到delim字符 '\n',delim字符不会被放入buffer中  
				data[j] = (float)atof(pixel.c_str());   //将字符串str转换成一个双精度数值并返回结果  
				elemCount = 0;                          //计数器置零  
			}
			else
			{
				getline(file, pixel, ',');                //任意地读入，直到读到delim字符 ','delim字符不会被放入buffer中  
				data[j] = (float)atof(pixel.c_str());   //将字符串str转换成一个双精度数值并返回结果  
				elemCount++;
			}
		}
	}
	return image;
}

void  gray2rainbowcolor(Mat &img,Mat &img_color)
{
img_color = Mat::zeros(img.rows, img.cols, CV_8UC3);
#define IMG_B(img,y,x) img.at<Vec3b>(y,x)[0]
#define IMG_G(img,y,x) img.at<Vec3b>(y,x)[1]
#define IMG_R(img,y,x) img.at<Vec3b>(y,x)[2]
	uchar tmp2=0;
	for (int y=0;y<img.rows;y++)
	{
		for (int x=0;x<img.cols;x++)
		{
			tmp2 = img.at<uchar>(y,x);
			if(tmp2 ==0 )
				continue;
			if (tmp2 <= 51)
			{
				IMG_B(img_color,y,x) = 255;
				IMG_G(img_color,y,x) = tmp2*5;
				IMG_R(img_color,y,x) = 0;
			}
			else if (tmp2 <= 102)
			{
				tmp2-=51;
				IMG_B(img_color,y,x) = 255-tmp2*5;
				IMG_G(img_color,y,x) = 255;
				IMG_R(img_color,y,x) = 0;
			}
			else if (tmp2 <= 153)
			{
				tmp2-=102;
				IMG_B(img_color,y,x) = 0;
				IMG_G(img_color,y,x) = 255;
				IMG_R(img_color,y,x) = tmp2*5;
			}
			else if (tmp2 <= 204)
			{
				tmp2-=153;
				IMG_B(img_color,y,x) = 0;
				IMG_G(img_color,y,x) = 255-uchar(128.0*tmp2/51.0+0.5);
				IMG_R(img_color,y,x) = 255;
			}
			else
			{
				tmp2-=204;
				IMG_B(img_color,y,x) = 0;
				IMG_G(img_color,y,x) = 127-uchar(127.0*tmp2/51.0+0.5);
				IMG_R(img_color,y,x) = 255;
			}
		}
	}
}

/*
Mat normalized(Mat &img, Mat &imgout)
{
	float data_min = 0, data_max = 0;
	int 	threshold_max = 255,threshold_min = 0;
	for (int i = 0; i < img.rows; i ++)
	{
		for (int j = 0; j < img.cols; j ++)
		{
		    float data =	img.at<uchar>(0,0);
			if (	data > img.at<uchar>(i,j))
			{
				data_max = data;
			}
			else
			{
				data_max = img.at<uchar>(i,j);
			}
			if (	data < img.at<uchar>(i,j))
			{
				data_min = data;
			}
			else
			{
				data_min = img.at<uchar>(i,j);
			}
		}
			cout<<"img_max="<<data_max<<endl;
			cout<<"img_min="<<data_min<<endl;
			for (int i = 0; i < img.rows; i ++)
			{
				for (int j = 0; j < img.cols; j ++)
				{
					float xiugaihou_piexl=round((threshold_max-threshold_min)*(img.at<uchar>(i,j) - data_min)/(data_max-data_min)+threshold_min);
				}
			}
	}
}
*/


int main()  
{  
	Mat StdZ = read_data_from_csv("Paded.csv");
	Mat StdX = read_data_from_csv("PadedY.csv");
	Mat StdY = read_data_from_csv("Paded_move.csv");
	//imshow("tu xiangz1",StdZ);
	//imshow("tu xiangx",StdX);
	//imshow("tu xiangy",StdY);
	//imshow("tu xiangx",StdX);
	normalize(StdZ, StdZ, 0,255, NORM_MINMAX);
	StdZ.convertTo(StdZ, CV_8UC1, 1, 0);
	Mat img_colorppp;
	//cout<<StdZ<<endl;
	//gray2rainbowcolor(StdZ,img_colorppp); 
	applyColorMap(StdZ, img_colorppp, cv::COLORMAP_JET);
	imshow("彩虹图",img_colorppp);   
	
	waitKey(0);
	return 0;  
}

