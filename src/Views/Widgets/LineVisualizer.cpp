//
// Created by chris on 4/26/18.
//

#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "LineVisualizer.h"
#include <random>

LineVisualizer::LineVisualizer(std::shared_ptr<IFifoProcessorService> processorService, std::shared_ptr<IConfigService> configService)
        : processorService(processorService),
          configService(configService)
{
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &LineVisualizer::on_timeout), configService->getConfig()->getFpsCount());
    this->displayBuffer = new double[visualElementCount];
}

LineVisualizer::~LineVisualizer()
{
    delete(this->displayBuffer);
}

bool LineVisualizer::on_draw(const Cairo::RefPtr <Cairo::Context> &cr)
{

    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    cr->scale(width, height);
    cr->set_line_width(0.01);

    cr->save();
    cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
    cr->paint();
    cr->restore();

    cr->save();
    cr->set_line_width(0.004);

    cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    this->processorService->loadAveragedData(this->displayBuffer, this->visualElementCount);

    for(int i = 0; i < this->visualElementCount; i++){
        double x = 0.02 + i * 0.0075;
        double yUpper = 1.0 - displayBuffer[i] / 160;
        //double yLower = (double)displayBuffer[i] / 140;

        double yLower = 0.8;
        cr->move_to(x, yLower);
        cr->line_to(x, yUpper);
        cr->stroke();
    }

//    cr->move_to(0, 0.5);
//    cr->line_to(1, 0.5);
//    cr->stroke();

    cr->restore();

    return true;
}

bool LineVisualizer::on_timeout() {
    auto win = get_window();
    if(win){
        Gdk::Rectangle r(0,0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}