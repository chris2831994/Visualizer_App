//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERCONFIG_H
#define GTKMM_MVC_TEST_VISUALIZERCONFIG_H

#include <string>

class VisualizerConfig {
public:

    VisualizerConfig(std::string fileName, int sampleRate, uint8_t fpsCount);

    std::string getFileName();
    void setFileName(std::string value);

    int getSampleRate();
    void setSampleRate(int value);

    uint8_t getFpsCount();
    void setFpsCount(uint8_t value);

    int getSampleSize();
    //void setSampleSize(int value);
protected:
    std::string fileName;
    int sampleRate;
    uint8_t fpsCount;
    int sampleSize;
};

#endif //GTKMM_MVC_TEST_VISUALIZERCONFIG_H
