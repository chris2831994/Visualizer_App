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


namespace di = boost::di;

int main(int argc, char **argv) {

    const auto injector = di::make_injector(
        di::bind<IFifoProcessorService>.to<FifoProcessorService>(),
        di::bind<IFifoReaderService>.to<MPDReaderService>(),
        di::bind<IVisualizer>.to<LineVisualizer>(),
        di::bind<IConfigService>.to<SimpleConfigService>()
    );

    auto window = injector.create<std::unique_ptr<VisualizerWindow>>();

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.asd");

    return app->run(window);
}

//    auto refBuilder = Gtk::Builder::create();
//    try
//    {
//        refBuilder->add_from_file("test.glade");
//    }
//    catch(const Glib::FileError& ex)
//    {
//        std::cerr << "FileError: " << ex.what() << std::endl;
//        return 1;
//    }
//    catch(const Glib::MarkupError& ex)
//    {
//        std::cerr << "MarkupError: " << ex.what() << std::endl;
//        return 1;
//    }
//    catch(const Gtk::BuilderError& ex)
//    {
//        std::cerr << "BuilderError: " << ex.what() << std::endl;
//        return 1;
//    }

//    refBuilder->get_widget("MainWindow", mainWindow);