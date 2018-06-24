#include <iostream>
#include <gtkmm.h>
#include "../include/boost_di.hpp"
#include "Services/IFifoProcessorService.h"
#include "Services/FifoProcessorService.h"
#include "Services/MPDReaderService.h"
#include "Services/IConfigService.h"
#include "Services/SimpleConfigService.h"
#include "Views/Widgets/IVisualizer.h"
#include "Views/Widgets/LineVisualizer.h"
#include "Views/VisualizerWindow.h"
#include "Views/SettingsWindow.h"
#include "Services/SimpleReaderService.h"
#include "Services/SimpleProcessorService.h"
#include "Views/Widgets/SettingsDialog.h"
#include "Views/Widgets/BlockVisualizer.h"
#include "Util/VisualizerWindowFactory.h"
#include "Util/VisualizerWidgetFactory.h"


namespace di = boost::di;

int main(int argc, char **argv) {

    //integration of widget example
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.asd");

    Gtk::Window window;
    window.set_default_size(200, 200);

    //create a block visualizer using the signal in time domain
    std::unique_ptr<IVisualizer> vis = VisualizerWidgetFactory::createBlockVisualizer(45, "/tmp/mpd.fifo", true);

    window.add(*vis);

    window.show_all_children();

    return app->run(window);

    //running standalone app example
    //VisualizerWindowFactory::createAndRunVisualizerWindow();
//
}