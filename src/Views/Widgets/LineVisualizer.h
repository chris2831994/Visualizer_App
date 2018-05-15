#ifndef MPD_LINE_VISUALIZER_H
#define MPD_LINE_VISUALIZER_H

#include <gtkmm/drawingarea.h>
#include "IVisualizer.h"

class LineVisualizer : public IVisualizer
{
public:
    LineVisualizer(std::shared_ptr<IFifoProcessorService> processorService);
    ~LineVisualizer();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    std::shared_ptr<IFifoProcessorService> processorService;
};

#endif // MPD_LINE_VISUALIZER_H