
#include "opencv2/opencv.hpp"

class Histogram {

private:
    cv::Mat image;
    double lastOperationTime;
    bool assemblyEnabled;
    int numberOfThreads;

public:
    Histogram(cv::Mat image);
    void setNumberOfThreads(int numberOfThreads);
    cv::Mat generateHistogram(int scale);
    double getDurationOfLastOperation();
    void setAssemblyExecution(bool enabled);
};
