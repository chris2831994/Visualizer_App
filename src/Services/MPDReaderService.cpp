//
// Created by chris on 5/13/18.
//

#include "MPDReaderService.h"

MPDReaderService::MPDReaderService(IFifoReader *reader) : reader(reader){

}

MPDReaderService::~MPDReaderService() {
    delete (reader);
}

uint16_t * MPDReaderService::getData() {
    return reader->getReadingBuffer();
}