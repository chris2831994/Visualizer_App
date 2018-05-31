//
// Created by chris on 5/31/18.
//

#ifndef GTKMM_MVC_TEST_BLOCKVISUALIZER_H
#define GTKMM_MVC_TEST_BLOCKVISUALIZER_H


class BlockVisualizer : public IVisualizer{
public:
    BlockVisualizer(std::shared_ptr<IFifoProcessorService> processorService);
    ~BlockVisualizer();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    std::shared_ptr<IFifoProcessorService> processorService;
};


#endif //GTKMM_MVC_TEST_BLOCKVISUALIZER_H
