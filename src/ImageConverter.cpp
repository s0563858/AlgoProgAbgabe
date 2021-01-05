/*INFO: This class is resposible for two image-transformation operations:
 * rgb to grayscale and changing of the brightness.
 *
 * */
#include <cstdio>
#include <iostream>
#include <omp.h>

#include "opencv2/opencv.hpp"

class ImageConverter {

private:
    cv::Mat image;
    double lastOperationTime;
    bool assemblyEnabled;
    int numberOfThreads;

public:
    void setNumberOfThreads(int numOfThreads)
    {
        numberOfThreads = numOfThreads;
        omp_set_dynamic(0); // garantees the right number of threads
        omp_set_num_threads(numberOfThreads);
    }

    void setAssemblyExecution(bool enabled)
    {
        assemblyEnabled = enabled;
    }

    ImageConverter(std::string pathImage)
    {
        assemblyEnabled = true;
        image = cv::imread(pathImage, cv::IMREAD_UNCHANGED);
    }

    double getDurationOfLastOperation()
    {
        return lastOperationTime;
    }

    static uchar sadd(uchar a, uchar b)
    {
        return (a > 0xFF - b) ? 0xFF : a + b;
    }

    void rgbToGrayscale()
    {
        double startTime = omp_get_wtime();

        int rows = image.rows;
        int cols = image.cols;
        int channels = image.channels();
        uchar* ptr = image.data;
        // which version should be executed - asm or c++:
        if (!assemblyEnabled) {
#pragma omp parallel for
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    uchar* pixel = ptr + channels * (i * cols + j);

                    uchar b = *(pixel + 0);
                    uchar g = *(pixel + 1);
                    uchar r = *(pixel + 2);

                    double grayscale = 0.21 * r + 0.72 * g + 0.07 * b;

                    pixel[0] = grayscale;
                    pixel[1] = grayscale;
                    pixel[2] = grayscale;
                }
            }
        } else {
#pragma omp parallel for
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    uchar* pixel = ptr + channels * (i * cols + j);
                    __asm {
                        mov rcx, pixel
                        mov eax, [rcx]

                        shr al, 4
                        shr ah, 1
                        add al, ah
                        shr ah, 1
                        add ah, al

                        shr eax, 8
                        shr ah, 2
                        add al, ah
                        jnc label
                        mov al, 255

                        label:
                        mov [rcx], al
                        mov [rcx+1], al
                        mov [rcx+2], al
                    }
                }
            }
        }

        double endTime = omp_get_wtime();

        lastOperationTime = endTime - startTime;
    }

    void changeBrightness(uchar brightness)
    {
        double startTime = omp_get_wtime();

        int rows = image.rows;
        int cols = image.cols;
        int channels = image.channels();
        uchar* ptr = image.data;
        // which version should be executed - asm or c++:
        if (!assemblyEnabled) {
#pragma omp parallel for
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {

                    uchar* pixel = ptr + channels * (i * cols + j);

                    uchar b = *(pixel + 0);
                    uchar g = *(pixel + 1);
                    uchar r = *(pixel + 2);

                    pixel[0] = sadd(b, brightness);
                    pixel[1] = sadd(g, brightness);
                    pixel[2] = sadd(r, brightness);
                }
            }
        } else {
            uchar brightnessArr[4] = { brightness, brightness, brightness, 0 };
#pragma omp parallel for
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    uchar* pixel = ptr + channels * (i * cols + j);
                    __asm {
                        mov rcx, pixel
                        movd mm1, [rcx]
                        movd mm0, brightnessArr
                        paddusb mm1, mm0
                        movd [rcx], mm1
                    }
                }
            }
        }

        double endTime = omp_get_wtime();

        lastOperationTime = endTime - startTime;
    }

    cv::Mat getImage()
    {
        return image;
    }
};
