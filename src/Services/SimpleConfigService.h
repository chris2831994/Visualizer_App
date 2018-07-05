//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_SIMPLECONFIGSERVICE_H
#define GTKMM_MVC_TEST_SIMPLECONFIGSERVICE_H

#include "IConfigService.h"
#include <memory>

class SimpleConfigService : public IConfigService{
public :
    //SimpleConfigService();
    SimpleConfigService(int sampleRate, std::string fifoPath, uint8_t fps);
    ~SimpleConfigService();
    VisualizerConfig * getConfig();
    void writeConfig();
protected:
    VisualizerConfig * config;
};

#endif //GTKMM_MVC_TEST_SIMPLECONFIGSERVICE_H
