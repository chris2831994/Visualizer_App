//
// Created by chris on 5/14/18.
//

#ifndef GTKMM_MVC_TEST_ICONFIGSERVICE_H
#define GTKMM_MVC_TEST_ICONFIGSERVICE_H

#include "../Model/VisualizerConfig.h"

class IConfigService {
public:

    virtual VisualizerConfig * getConfig() = 0;
    virtual void writeConfig() = 0;

protected:
};


#endif //GTKMM_MVC_TEST_ICONFIGSERVICE_H
