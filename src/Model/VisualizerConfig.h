//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERCONFIG_H
#define GTKMM_MVC_TEST_VISUALIZERCONFIG_H

#include <string>

class VisualizerConfig {
public:

    VisualizerConfig(std::string fileName, int sampleSize, int defaultVisualizer);

    std::string getFileName();
    void setFileName(std::string value);

    int getSampleSize();
    void setSampleSize(int value);

    int getDefaultVisualizer();
    void setDefaultVisualizer(int value);
protected:
    std::string fileName;
    int sampleSize;
    int defaultVisualizer;
};

#endif //GTKMM_MVC_TEST_VISUALIZERCONFIG_H
