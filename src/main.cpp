#include "Histogram.cpp"
#include "ImageConverter.cpp"
#include "SettingsReader.cpp"
#include <cstdio>
#include <iostream>
#include <list>
#include <omp.h>
#include <string>

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
