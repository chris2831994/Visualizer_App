//
// Created by chris on 5/10/18.
//

#ifndef GTKMM_MVC_TEST_IFIFOREADERSERVICE_H
#define GTKMM_MVC_TEST_IFIFOREADERSERVICE_H

#include "Util/IFifoReader.h"

class IFifoReaderService {
public:

    virtual uint16_t * getData() = 0;

protected:
    IFifoReader * reader;
};


#endif //GTKMM_MVC_TEST_IFIFOREADERSERVICE_H
