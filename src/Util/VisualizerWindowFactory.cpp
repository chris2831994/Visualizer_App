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
#include "../Views/Widgets/SettingsDialog.h"
#include "../Views/Widgets/BlockVisualizer.h"

namespace di = boost::di;

std::unique_ptr<VisualizerWindow> VisualizerWindowFactory::createVisualizerWindow() {

    uint8_t fps = 25;

    const auto injector = di::make_injector(
            di::bind<IFifoProcessorService>.to<FifoProcessorService>(),
            di::bind<IFifoReaderService>.to<MPDReaderService>(),
            di::bind<IVisualizer>.to<BlockVisualizer>(),
            di::bind<ISettingsDialog>.to<SettingsDialog>(),
            di::bind<int>.to(44100),
            di::bind<uint8_t>.to(fps),
            di::bind<std::string>.to("/tmp/mpd.fifo"),
            di::bind<IConfigService>.to<SimpleConfigService>()
    );

    auto window = injector.create<std::unique_ptr<VisualizerWindow>>();

    return window;
}