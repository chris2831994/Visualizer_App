//
// Created by chris on 6/17/18.
//

#include "VisualizerWidgetFactory.h"
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

std::unique_ptr<IVisualizer> VisualizerWidgetFactory::createLineVisualizer(std::string fifoPath, int sampleRate, uint8_t fpsCount, bool useTimeDomain){

    if(useTimeDomain){
            const auto injector = di::make_injector(
                di::bind<IFifoProcessorService>.to<TimeDomainProcessorService>(),
                di::bind<IFifoReaderService>.to<MPDReaderService>(),
                di::bind<int>.to(sampleRate),
                di::bind<uint8_t>.to(fpsCount),
                di::bind<std::string>.to(fifoPath),
                di::bind<IConfigService>.to<SimpleConfigService>()
        );
        std::unique_ptr<IVisualizer> vis = injector.create<std::unique_ptr<LineVisualizer>>();


        return vis;
    } else {
            const auto injector = di::make_injector(
                di::bind<IFifoProcessorService>.to<FifoProcessorService>(),
                di::bind<IFifoReaderService>.to<MPDReaderService>(),
                di::bind<int>.to(sampleRate),
                di::bind<uint8_t>.to(fpsCount),
                di::bind<std::string>.to(fifoPath),
                di::bind<IConfigService>.to<SimpleConfigService>()
        );
        std::unique_ptr<IVisualizer> vis = injector.create<std::unique_ptr<LineVisualizer>>();


        return vis;
    }


}

std::unique_ptr<IVisualizer> VisualizerWidgetFactory::createBlockVisualizer(std::string fifoPath, int sampleRate, uint8_t fpsCount, bool useTimeDomain){

    if(useTimeDomain){
        const auto injector = di::make_injector(
                di::bind<IFifoProcessorService>.to<TimeDomainProcessorService>(),
                di::bind<IFifoReaderService>.to<MPDReaderService>(),
                di::bind<int>.to(sampleRate),
                di::bind<uint8_t>.to(fpsCount),
                di::bind<std::string>.to(fifoPath),
                di::bind<IConfigService>.to<SimpleConfigService>()
        );
        std::unique_ptr<IVisualizer> vis = injector.create<std::unique_ptr<BlockVisualizer>>();

        return vis;
    } else {
        const auto injector = di::make_injector(
                di::bind<IFifoProcessorService>.to<FifoProcessorService>(),
                di::bind<IFifoReaderService>.to<MPDReaderService>(),
                di::bind<int>.to(sampleRate),
                di::bind<uint8_t>.to(fpsCount),
                di::bind<std::string>.to(fifoPath),
                di::bind<IConfigService>.to<SimpleConfigService>()
        );
        std::unique_ptr<IVisualizer> vis = injector.create<std::unique_ptr<BlockVisualizer>>();

        return vis;
    }
}