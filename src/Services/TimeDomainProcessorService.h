//
// Created by chris on 6/24/18.
//

#ifndef GTKMM_MVC_TEST_TIMEDOMAINPROCESSORSERVICE_H
#define GTKMM_MVC_TEST_TIMEDOMAINPROCESSORSERVICE_H

#include <memory>
#include "IFifoProcessorService.h"
#include "IConfigService.h"
#include "IFifoReaderService.h"


class TimeDomainProcessorService : public IFifoProcessorService{
public:

    TimeDomainProcessorService(std::shared_ptr<IFifoReaderService> readerService, std::shared_ptr<IConfigService> configService);
    ~TimeDomainProcessorService();
    uint16_t * getProcessedData();
    void loadAveragedData(uint16_t * buffer, int length);
    void reInit();

protected:
    std::shared_ptr<IFifoReaderService> readerService;
    std::shared_ptr<IConfigService> configService;

    int sampleSize;
    int segmentLength;
    uint16_t * workingBuffer;
};

#endif //GTKMM_MVC_TEST_TIMEDOMAINPROCESSORSERVICE_H
