#ifndef MPD_VISUALIZER_H
#define MPD_VISUALIZER_H

#include <gtkmm/drawingarea.h>
#include "../../Services/IFifoProcessorService.h"
#include <stdint.h>

class IVisualizer : public Gtk::DrawingArea
{
public:

protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override = 0;
    virtual bool on_timeout() = 0;
};


#endif // MPD_VISUALIZER_H