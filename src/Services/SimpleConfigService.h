//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_SIMPLECONFIGSERVICE_H
#define GTKMM_MVC_TEST_SIMPLECONFIGSERVICE_H

class SimpleConfigService : IConfigService{
public :
    SimpleConfigService();
    ~SimpleConfigService();
    VisualizerConfig * getConfig();
protected:
    VisualizerConfig * config;
};

#endif //GTKMM_MVC_TEST_SIMPLECONFIGSERVICE_H
