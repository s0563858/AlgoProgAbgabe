
#include "opencv2/opencv.hpp"

class ImageConverter {

private:
    cv::Mat image;
    double lastOperationTime;
    bool assemblyEnabled;
    int numberOfThreads;

public:
    ImageConverter(std::string pathImage);
    void rgbToGrayscale();
    void setNumberOfThreads(int numberOfThreads);
    void changeBrightness(uchar brightness);
    void setAssemblyExecution(bool enabled);
    double getDurationOfLastOperation();
    cv::Mat getImage();
};
