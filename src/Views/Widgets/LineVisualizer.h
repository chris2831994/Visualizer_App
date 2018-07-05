#ifndef MPD_LINE_VISUALIZER_H
#define MPD_LINE_VISUALIZER_H

#include <gtkmm/drawingarea.h>
#include "IVisualizer.h"
#include "../../Services/IConfigService.h"

class LineVisualizer : public IVisualizer
{
public:
    LineVisualizer(std::shared_ptr<IFifoProcessorService> processorService, std::shared_ptr<IConfigService> configService);
    ~LineVisualizer();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    const int visualElementCount = 128;
    std::shared_ptr<IFifoProcessorService> processorService;
    std::shared_ptr<IConfigService> configService;
    double * displayBuffer;
};

#endif // MPD_LINE_VISUALIZER_H