/*INFO: This class is resposible for creating of the histogram of some image.
 *
 * */
#include <cstdio>
#include <iostream>
#include <omp.h>

#include "opencv2/opencv.hpp"

class Histogram {

private:
    cv::Mat image;
    double lastOperationTime;
    int numberOfThreads;

public:
    void setNumberOfThreads(int numberOfThreads)
    {
        numberOfThreads = numberOfThreads;
    }

    Histogram(cv::Mat imageForHist)
    {
        image = imageForHist;
    }

    double getDurationOfLastOperation()
    {
        return lastOperationTime;
    }

    cv::Mat generateHistogram(int scale)
    {
        double startTime = omp_get_wtime();

        int histogramDataR[256];
        int histogramDataG[256];
        int histogramDataB[256];
        int pixelCounter = 0;

        for (int i = 0; i < 256; ++i) {
            histogramDataR[i] = 0;
            histogramDataG[i] = 0;
            histogramDataB[i] = 0;
        }

        uchar* ptrImg = (uchar*)image.data;

        cv::Mat histMatrix((256 * scale) / 4, 256 * scale, CV_8UC3);
        uchar* ptrHist = (uchar*)histMatrix.data;

        //count the pixel-values:
#pragma omp parallel for reduction(+ \
                                   : histogramDataR, histogramDataG, histogramDataB)
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                uchar* pixel = ptrImg + image.channels() * (i * image.cols + j);
                histogramDataB[pixel[0]] += 1;
                histogramDataG[pixel[1]] += 1;
                histogramDataR[pixel[2]] += 1;
            }
        }

        //get the highest counter: (needed for apropriate scaling of the histogram)
        int highestCounter = 0;
#pragma omp parallel for reduction(max \
                                   : highestCounter)
        for (int i = 0; i < 256; ++i) {
            if (histogramDataB[i] > highestCounter) {
                highestCounter = histogramDataB[i];
            }
            if (histogramDataG[i] > highestCounter) {
                highestCounter = histogramDataG[i];
            }
            if (histogramDataR[i] > highestCounter) {
                highestCounter = histogramDataR[i];
            }
        }

        //draw the histogram:
#pragma omp parallel for
        for (int i = 0; i < 256 * scale; i += 1 * scale) {
            float r = histogramDataR[i / scale];
            float g = histogramDataG[i / scale];
            float b = histogramDataB[i / scale];
            for (int j = 0; j < histMatrix.rows; ++j) {
                uchar* pixel = ptrHist + histMatrix.channels() * (j * histMatrix.cols + i);
                float rowTemp = (float)j / histMatrix.rows;
                if (r / highestCounter > rowTemp) {
                    pixel[2] = 255;
                }
                if (g / highestCounter > rowTemp) {
                    pixel[1] = 255;
                }
                if (b / highestCounter > rowTemp) {
                    pixel[0] = 255;
                }
            }
        }

        double endTime = omp_get_wtime();

        lastOperationTime = endTime - startTime;

        return histMatrix;
    }
};
