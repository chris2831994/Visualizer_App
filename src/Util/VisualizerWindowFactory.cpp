//
// Created by chris on 5/31/18.
//

#include "VisualizerWindowFactory.h"
#include "../Views/VisualizerWindow.h"
#include <gtkmm.h>
#include "../../include/boost_di.hpp"
#include "../Services/IFifoProcessorService.h"
#include "../Services/FifoProcessorService.h"
#include "../Services/MPDReaderService.h"
#include "../Services/IConfigService.h"
#include "../Services/SimpleConfigService.h"
#include "../Views/Widgets/IVisualizer.h"
#include "../Views/Widgets/LineVisualizer.h"
#include "../Views/VisualizerWindow.h"
#include "../Views/SettingsWindow.h"
#include "../Services/SimpleReaderService.h"
#include "../Services/SimpleProcessorService.h"
#include "../Views/Widgets/SettingsDialog.h"
#include "../Views/Widgets/BlockVisualizer.h"
#include "../Services/TimeDomainProcessorService.h"

namespace di = boost::di;

void VisualizerWindowFactory::createAndRunVisualizerWindow() {

    const auto injector = di::make_injector(
            di::bind<IFifoProcessorService>.to<TimeDomainProcessorService>(),
    di::bind<IFifoReaderService>.to<MPDReaderService>(),
            di::bind<IVisualizer>.to<BlockVisualizer>(),
            di::bind<ISettingsDialog>.to<SettingsDialog>(),
            di::bind<IConfigService>.to<SimpleConfigService>()
    );

    auto app = Gtk::Application::create("org.gtkmm.asd");

    auto mainWindow = injector.create<std::unique_ptr<VisualizerWindow>>();

    app->run(*mainWindow);
}