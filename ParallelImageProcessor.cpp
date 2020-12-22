
#include <cstdio>
#include <iostream>
#include <omp.h>
#include <string>
//#include "ImageConverter.h"
//#include "Histogram.cpp"
//#include "ImageConverter.cpp"

#include "opencv2/opencv.hpp"
#include <immintrin.h>

typedef void (*ImageFunction)(cv::Mat image);
typedef void (*ImageFunctionWithArgs)(cv::Mat image, uchar* args);

class ParallelImageProcessor {

private:
    //int numberOfThreads;
    ImageFunction delegateFunction;
    ImageFunctionWithArgs delegateFunctionWithArgs;
    bool executionWithArgs;
    uchar* args;

public:
    ParallelImageProcessor(ImageFunction delegate)
    {
        ParallelImageProcessor::delegateFunction = delegate;
        ParallelImageProcessor::executionWithArgs = false;
    }
    ParallelImageProcessor(ImageFunctionWithArgs delegate, uchar* args)
    {
        ParallelImageProcessor::delegateFunctionWithArgs = delegate;
        ParallelImageProcessor::executionWithArgs = true;
        ParallelImageProcessor::args = args;
    }

    void setNumberOfThreads(int numberOfThreads)
    {
        omp_set_dynamic(0);
        omp_set_num_threads(numberOfThreads);
    }

    void execute(cv::Mat image)
    {
        if (!executionWithArgs) {
            ParallelImageProcessor::delegateFunction(image);
        } else {
            ParallelImageProcessor::delegateFunctionWithArgs(image, args);
        }
    }
};
