// clang++  -I /usr/local/Cellar/opencv/4.4.0_2/include/opencv4 -L /usr/local/Cellar/opencv/4.4.0_2/lib -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_highgui -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -Xpreprocessor -fopenmp -lomp -std=c++11  main.cpp -o yourFileProgram
#include <cstdio>
#include <iostream>
#include <list>
#include <omp.h>
#include <string>
//#include "ImageConverter.h"
#include "Histogram.cpp"
#include "ImageConverter.cpp"
#include "SettingsReader.cpp"

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "opencv2/opencv.hpp"
#include <immintrin.h>

bool contains(std::list<option> list, option element)
{
    auto search = std::find(list.begin(), list.end(), element);
    return search != list.end();
}

int main(int argc, char** argv)
{
    SettingsReader settings(argc, argv);

    if (settings.readSettings()) {

        std::list<option> options = settings.getOptions();
        if (!contains(options, option::PATH)) {
            std::cout << std::endl
                      << "Error: no path!";
            exit(1);
        }
        ImageConverter converter(settings.path);
        if (contains(options, option::PURE_CPP)) {
            converter.setAssemblyExecution(false);
        }
        if (contains(options, option::CHANGED_NUM_THREADS)) {
            converter.setNumberOfThreads(settings.numOfThreads);
        }
        double timeOfOperations = 0;
        if (contains(options, option::SHOW_ORIGINAL_PIC)) {
            cv::Mat img = converter.getImage();
            cv::imshow("Original Image", img);
        }
        if (contains(options, option::GRAYSCALE)) {
            converter.rgbToGrayscale();
            timeOfOperations += converter.getDurationOfLastOperation();
        }
        if (contains(options, option::BRIGHTNESS)) {
            converter.changeBrightness(settings.brightness);
            timeOfOperations += converter.getDurationOfLastOperation();
        }
        if (contains(options, option::HISTOGRAM)) {
            cv::Mat img = converter.getImage();
            Histogram histogram(img);
            if (contains(options, option::CHANGED_NUM_THREADS)) {
                histogram.setNumberOfThreads(settings.numOfThreads);
            }
            cv::Mat histImg = histogram.generateHistogram(settings.histogramScale);
            cv::imshow("Histogram", histImg);
            timeOfOperations += histogram.getDurationOfLastOperation();
        }
        if (contains(options, option::TIME_AS_NUMBER)) {
            std::cout << timeOfOperations << std::endl;
        } else {
            std::cout << "Processing took: " << timeOfOperations << " s" << std::endl;
        }
        cv::Mat img = converter.getImage();
        cv::imshow("Result", img);

        if (!contains(options, option::CLOSE_AFTER_DONE)) {
            int key = cv::waitKey(0);
            cv::destroyAllWindows();
        }
    }
}
