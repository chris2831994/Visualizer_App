//
// Created by chris on 5/10/18.
//

#ifndef GTKMM_MVC_TEST_IFIFOPROCESSORSERVICE_H
#define GTKMM_MVC_TEST_IFIFOPROCESSORSERVICE_H

class IFifoProcessorService{

public:

    virtual uint16_t * getProcessedData() = 0;

protected:

};

#endif //GTKMM_MVC_TEST_IFIFOPROCESSORSERVICE_H
