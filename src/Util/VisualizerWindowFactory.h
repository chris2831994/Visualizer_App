//
// Created by chris on 5/31/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERWINDOWFACTORY_H
#define GTKMM_MVC_TEST_VISUALIZERWINDOWFACTORY_H

#include "../Views/VisualizerWindow.h"

class VisualizerWindowFactory{
public:

    static std::unique_ptr<VisualizerWindow>  createVisualizerWindow();

private:
    VisualizerWindowFactory();
};


#endif //GTKMM_MVC_TEST_VISUALIZERWINDOWFACTORY_H
