//
// Created by chris on 5/13/18.
//

#ifndef GTKMM_MVC_TEST_MPDREADERSERVICE_H
#define GTKMM_MVC_TEST_MPDREADERSERVICE_H

#include <memory>
#include "IFifoReaderService.h"
#include "IConfigService.h"

class MPDReaderService : public IFifoReaderService{
public:
    MPDReaderService(std::shared_ptr<IConfigService> configService);
    ~MPDReaderService();
    uint16_t * getData();
protected:

    std::shared_ptr<IConfigService> configService;
    int fifo;
    uint16_t * readingBuffer;

    void readData();

};

#endif //GTKMM_MVC_TEST_MPDREADERSERVICE_H
