//
// Created by chris on 6/17/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERWIDGETFACTORY_H
#define GTKMM_MVC_TEST_VISUALIZERWIDGETFACTORY_H

#include "../Views/Widgets/IVisualizer.h"

class VisualizerWidgetFactory{
public:
    static std::unique_ptr<IVisualizer> createLineVisualizer(std::string fifoPath, int sampleRate, uint8_t fpsCount);
    static std::unique_ptr<IVisualizer> createBlockVisualizer(std::string fifoPath, int sampleRate, uint8_t fpsCount);
private:
    VisualizerWidgetFactory();
};

#endif //GTKMM_MVC_TEST_VISUALIZERWIDGETFACTORY_H
