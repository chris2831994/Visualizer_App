//
// Created by chris on 5/14/18.
//

#ifndef GTKMM_MVC_TEST_ICONFIGSERVICE_H
#define GTKMM_MVC_TEST_ICONFIGSERVICE_H

#include "../Model/VisualizerConfig.h"

class IConfigService {

public:
    virtual VisualizerConfig getConfig() = 0;

};


#endif //GTKMM_MVC_TEST_ICONFIGSERVICE_H
