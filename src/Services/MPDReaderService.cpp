//
// Created by chris on 5/13/18.
//

#include "MPDReaderService.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

MPDReaderService::MPDReaderService(std::shared_ptr<IConfigService> configService) : configService(configService){

    VisualizerConfig * config = configService->getConfig();
    this->fifo = open(config->getFileName().c_str(), O_RDONLY);
    //this->readingBuffer = (uint16_t *) malloc(sizeof(uint16_t) * config->getSampleSize());
    this->readingBuffer = new uint16_t[config->getSampleSize()];
}

MPDReaderService::~MPDReaderService() {
    close(this->fifo);
    //free(readingBuffer);
    delete(readingBuffer);
}

int MPDReaderService::readData() {
    return read(this->fifo,(uint16_t *) readingBuffer, 2 * (configService->getConfig()->getSampleSize()));
}

uint16_t * MPDReaderService::getData() {
    readData();
    return this->readingBuffer;
}