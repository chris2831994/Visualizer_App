//
// Created by chris on 5/29/18.
//

#ifndef GTKMM_MVC_TEST_SIMPLEPROCESSORSERVICE_H
#define GTKMM_MVC_TEST_SIMPLEPROCESSORSERVICE_H

#include <memory>
#include "IFifoProcessorService.h"
#include "IConfigService.h"
#include "IFifoReaderService.h"

class SimpleProcessorService : public IFifoProcessorService {
public:
    SimpleProcessorService(std::shared_ptr<IConfigService> configService, std::shared_ptr<IFifoReaderService> readerService);
    ~SimpleProcessorService();
    uint16_t * getProcessedData();
protected:
    std::shared_ptr<IConfigService> configService;
    std::shared_ptr<IFifoReaderService> readerService;
    uint16_t * processingBuffer;
};
#endif //GTKMM_MVC_TEST_SIMPLEPROCESSORSERVICE_H
