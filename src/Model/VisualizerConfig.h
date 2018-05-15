//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERCONFIG_H
#define GTKMM_MVC_TEST_VISUALIZERCONFIG_H

#include <string>

class VisualizerConfig {
public:

    VisualizerConfig(std::string fileName, int sampleSize);

    std::string getFileName();
    void setFileName(std::string value);

    int getSampleSize();
    void setSampleSize(int value);
protected:
    std::string fileName;
    int sampleSize;
};

#endif //GTKMM_MVC_TEST_VISUALIZERCONFIG_H
