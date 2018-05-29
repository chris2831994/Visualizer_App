//
// Created by chris on 5/29/18.
//

#include "SimpleReaderService.h"

SimpleReaderService::SimpleReaderService(std::shared_ptr<IConfigService> configService) : configService(configService) {

    //int sampleSize = configService->getConfig()->getSampleSize();
    int sampleSize = 1024;
    this->dataBuffer = new uint16_t[sampleSize];
    for(int i = 0; i < sampleSize; i++){
        dataBuffer[i] = 1;
    }
}

SimpleReaderService::~SimpleReaderService() {
    delete(dataBuffer);
}

uint16_t * SimpleReaderService::getData() {
    return this->dataBuffer;
}