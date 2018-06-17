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
    //opens fifo file, settings O_NONBLOCK flag stops system from blocking calling thread
    this->fifo = open(config->getFileName().c_str(), O_RDONLY | O_NONBLOCK);
    //this->readingBuffer = (uint16_t *) malloc(sizeof(uint16_t) * config->getSampleSize());
    this->readingBuffer = new uint16_t[config->getSampleSize()];
}

MPDReaderService::~MPDReaderService() {
    close(this->fifo);
    delete(readingBuffer);
}

void MPDReaderService::readData() {
    if(!read(this->fifo,(uint16_t *) readingBuffer, 2 * (configService->getConfig()->getSampleSize()))){
        for(int i = 0; i < configService->getConfig()->getSampleSize(); i++){
            readingBuffer[i] = 1;
        }
    }
}

uint16_t * MPDReaderService::getData() {
    readData();
    return this->readingBuffer;
}

void MPDReaderService::reInit(){

    //close access to old fifo file
    close(this->fifo);

    //free bufer memory
    delete(readingBuffer);

    VisualizerConfig * config = configService->getConfig();
    //opens fifo file, settings O_NONBLOCK flag stops system from blocking calling thread
    this->fifo = open(config->getFileName().c_str(), O_RDONLY | O_NONBLOCK);
    this->readingBuffer = new uint16_t[config->getSampleSize()];
}