//
// Created by chris on 6/24/18.
//

#include "TimeDomainProcessorService.h"
#include <cmath>

TimeDomainProcessorService::TimeDomainProcessorService(std::shared_ptr<IFifoReaderService> readerService,
                                                       std::shared_ptr<IConfigService> configService)
: readerService(readerService),
  configService(configService)
{
    this->sampleSize = configService->getConfig()->getSampleSize();
    this->workingBuffer = new uint16_t[sampleSize];
}

TimeDomainProcessorService::~TimeDomainProcessorService() {
    delete(workingBuffer);
}

void TimeDomainProcessorService::reInit() {
    this->sampleSize = configService->getConfig()->getSampleSize();
    this->workingBuffer = new uint16_t[sampleSize];
}

uint16_t* TimeDomainProcessorService::getProcessedData() {
    uint16_t * data = readerService->getData();

    for(int i = 0; i< sampleSize; i++){
        this->workingBuffer[i] = data[i];
    }

    return data;
}

void TimeDomainProcessorService::loadAveragedData(uint16_t *buffer, int length) {

    uint16_t * data = readerService->getData();

    for(int i = 0; i< sampleSize; i++){
        this->workingBuffer[i] = data[i];
    }

    int avg = 0;
    for(int i = 0; i < sampleSize; i++){
        avg += workingBuffer[i];
    }
    avg /= sampleSize;

    for(int i = 0; i< length; i++){
        buffer[i] = round(20*log10(avg));
    }

}