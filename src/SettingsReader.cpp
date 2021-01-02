#include <cstdio>
#include <iostream>
#include <list>
#include <omp.h>
#include <string>

#include <immintrin.h>

enum option { GRAYSCALE,
    TIME_AS_NUMBER,
    PURE_CPP,
    SHOW_ORIGINAL_PIC,
    BRIGHTNESS,
    HISTOGRAM,
    CHANGED_NUM_THREADS,
    CLOSE_AFTER_DONE,
    PATH
};

class SettingsReader {

private:
    int argumentNumber;
    char** argv;
    std::list<option> options;

public:
    std::string path = "";
    int histogramScale = 0;
    int brightness = 0;
    int numOfThreads = 0;

    SettingsReader(int argNumber, char** arg)
    {
        argv = arg;
        argumentNumber = argNumber;
    }

    std::list<option> getOptions()
    {
        return options;
    }
    bool readSettings()
    {
        //std::string path = "";
        //int histogramScale = 0;
        //int brightness = 0;
        //int numOfThreads = 0;
        //std::list<option> options;

        if (argumentNumber == 1) {
            std::cout << "Help:" << std::endl
                      << "path to image: -p path" << std::endl
                      << "for grayscale: -g " << std::endl
                      << "for showing oringinal picture: -s " << std::endl
                      << "for changing brightness: -b brightness" << std::endl
                      << "for changing number of threads: -t numOfThreads" << std::endl
                      << "for printing processing-time as number: -pn" << std::endl
                      << "for closing immediatly after the program is done: -c" << std::endl
                      << "for executing of the pure cpp-code(without asm): -cpp" << std::endl
                      << "for histogram: -h scaleOfHistogram" << std::endl;
            return false;
        } else {

            for (int i = 1; i < argumentNumber; ++i) {
                if (strcmp(argv[i], "-c") == 0) {
                    options.push_front(option::CLOSE_AFTER_DONE);
                }
                if (strcmp(argv[i], "-cpp") == 0) {
                    options.push_front(option::PURE_CPP);
                }
                if (strcmp(argv[i], "-pn") == 0) {
                    options.push_front(option::TIME_AS_NUMBER);
                }
                if (strcmp(argv[i], "-p") == 0) {
                    options.push_front(option::PATH);
                    path = argv[i + 1];
                }
                if (strcmp(argv[i], "-g") == 0) {
                    options.push_front(option::GRAYSCALE);
                }
                if (strcmp(argv[i], "-s") == 0) {
                    options.push_front(option::SHOW_ORIGINAL_PIC);
                }
                if (strcmp(argv[i], "-h") == 0) {
                    options.push_front(option::HISTOGRAM);
                    histogramScale = atoi(argv[i + 1]);
                }
                if (strcmp(argv[i], "-b") == 0) {
                    options.push_front(option::BRIGHTNESS);
                    brightness = atoi(argv[i + 1]);
                }
                if (strcmp(argv[i], "-t") == 0) {
                    options.push_front(option::CHANGED_NUM_THREADS);
                    numOfThreads = atoi(argv[i + 1]);
                }
            }

            return true;
        }
    }
};
