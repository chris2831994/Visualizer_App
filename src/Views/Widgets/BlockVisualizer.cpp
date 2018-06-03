//
// Created by chris on 5/31/18.
//
#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include <iostream>
#include "BlockVisualizer.h"

BlockVisualizer::BlockVisualizer(std::shared_ptr <IFifoProcessorService> processorService)
    : processorService(processorService)
{
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &BlockVisualizer::on_timeout), 1);
    this->displayBuffer = new uint16_t[visualElementCount];
}

BlockVisualizer::~BlockVisualizer() {
    delete(this->displayBuffer);
}

bool BlockVisualizer::on_draw(const Cairo::RefPtr <Cairo::Context> &cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    const double blockWidth = 0.05;
    const double blockHeight = 0.01;
    const double offsetX = 0.085;
    const double offsetY = 0.85;
    const double blockSpacerX = 0.005;
    const double blockSpacerY = 0.01;

    cr->scale(width, height);
    cr->set_line_width(0.01);

    cr->save();
    cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
    cr->paint();
    cr->restore();

    cr->save();
    cr->set_line_width(blockWidth);

    //cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
    Gdk::Color start_color("red");
    Gdk::Color end_color("green");

    Cairo::RefPtr<Cairo::LinearGradient> gradient_ptr = Cairo::LinearGradient::create(0, 0, 0, 1);
    gradient_ptr->add_color_stop_rgb(0, start_color.get_red_p(), start_color.get_green_p(), start_color.get_blue_p());
    gradient_ptr->add_color_stop_rgb(1, end_color.get_red_p(), end_color.get_green_p(), end_color.get_blue_p());

    cr->set_source(gradient_ptr);
    cr->set_line_cap(Cairo::LINE_CAP_SQUARE);

    this->processorService->loadAveragedData(this->displayBuffer, this->visualElementCount);



    for(int i = 0; i < this->visualElementCount; i++){


        int k = 0;
        for(int j = 102; j < 130; j += 2){
            double x = offsetX + i * blockWidth + i * blockSpacerX;
            double y = offsetY - k * 0.06;

            if((int)displayBuffer[i] >= j){

                cr->move_to(x, y - k* blockSpacerY);
                cr->line_to(x, y - blockHeight - k* blockSpacerY);
                cr->stroke();

            }

            k++;
        }
        //std::cout << displayBuffer[i] << " ";
    }

    //std::cout << std::endl;
    cr->restore();

    return true;
}

bool BlockVisualizer::on_timeout() {
    auto win = get_window();
    if(win){
        Gdk::Rectangle r(0,0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}