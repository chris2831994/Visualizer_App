//
// Created by chris on 5/29/18.
//

#ifndef GTKMM_MVC_TEST_SIMPLEREADERSERVICE_H
#define GTKMM_MVC_TEST_SIMPLEREADERSERVICE_H

#include <memory>
#include "IFifoReaderService.h"
#include "IConfigService.h"

class SimpleReaderService : public IFifoReaderService{

public:
    SimpleReaderService(std::shared_ptr<IConfigService> configService);
    ~SimpleReaderService();
    uint16_t * getData();
protected:
    std::shared_ptr<IConfigService> configService;
    uint16_t * dataBuffer;

};

#endif //GTKMM_MVC_TEST_SIMPLEREADERSERVICE_H
