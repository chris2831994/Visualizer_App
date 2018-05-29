//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_XMLCONFIGSERVICE_H
#define GTKMM_MVC_TEST_XMLCONFIGSERVICE_H

#include "IConfigService.h"

class XMLConfigService : public IConfigService{
public:
    XMLConfigService();
    ~XMLConfigService();
    VisualizerConfig * getConfig();
    void writeConfig();

protected:
    VisualizerConfig * config;
};

#endif //GTKMM_MVC_TEST_XMLCONFIGSERVICE_H
