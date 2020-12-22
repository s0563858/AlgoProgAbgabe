// clang++  -I /usr/local/Cellar/opencv/4.4.0_2/include/opencv4 -L /usr/local/Cellar/opencv/4.4.0_2/lib -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_highgui -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -Xpreprocessor -fopenmp -lomp -std=c++11  helloWorld.cpp -o yourFileProgram
//#include "Histogram.h"
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

        //#pragma omp parallel for shared(histogramDataR, histogramDataG, histogramDataB)
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
