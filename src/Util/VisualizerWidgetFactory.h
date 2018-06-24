//
// Created by chris on 6/17/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERWIDGETFACTORY_H
#define GTKMM_MVC_TEST_VISUALIZERWIDGETFACTORY_H

#include "../Views/Widgets/IVisualizer.h"

class VisualizerWidgetFactory{
public:
    static std::unique_ptr<IVisualizer> createLineVisualizer(int sampleSize, std::string fifoPath, bool useTimeDomain);
    static std::unique_ptr<IVisualizer> createBlockVisualizer(int sampleSize, std::string fifoPath, bool useTimeDomain);
private:
    VisualizerWidgetFactory();
};

#endif //GTKMM_MVC_TEST_VISUALIZERWIDGETFACTORY_H
