//
// Created by chris on 5/31/18.
//

#ifndef GTKMM_MVC_TEST_BLOCKVISUALIZER_H
#define GTKMM_MVC_TEST_BLOCKVISUALIZER_H


#include "IVisualizer.h"
#include "../../Services/IConfigService.h"

class BlockVisualizer : public IVisualizer{
public:
    BlockVisualizer(std::shared_ptr<IFifoProcessorService> processorService, std::shared_ptr<IConfigService> configService);
    ~BlockVisualizer();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    const int visualElementCount = 32;
    std::shared_ptr<IFifoProcessorService> processorService;
    std::shared_ptr<IConfigService> configService;
    double * displayBuffer;
};


#endif //GTKMM_MVC_TEST_BLOCKVISUALIZER_H
