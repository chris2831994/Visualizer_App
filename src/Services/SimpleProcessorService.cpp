//
// Created by chris on 5/29/18.
//

#include "SimpleProcessorService.h"
#include <iostream>

SimpleProcessorService::SimpleProcessorService(std::shared_ptr<IConfigService> configService, std::shared_ptr<IFifoReaderService> readerService)
        : configService(configService),
          readerService(readerService)
{

    //int sampleSize = configService->getConfig()->getSampleSize();
    this->processingBuffer = new uint16_t[128];

}

SimpleProcessorService::~SimpleProcessorService() {
    delete(processingBuffer);
}

uint16_t * SimpleProcessorService::getProcessedData() {

    uint16_t * data = readerService->getData();
    int length = sizeof(data) / sizeof(uint16_t);
    for(int i = 0; i < length; i++){
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    for(int j = 0; j < 128; j++){
        processingBuffer[j] = 160;
    }

}