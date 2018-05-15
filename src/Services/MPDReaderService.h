//
// Created by chris on 5/13/18.
//

#ifndef GTKMM_MVC_TEST_MPDREADERSERVICE_H
#define GTKMM_MVC_TEST_MPDREADERSERVICE_H

class MPDReaderService : public IFifoReaderService{
public:
    MPDReaderService(IFifoReader * reader);
    ~MPDReaderService();
    uint16_t * getData();
protected:
    IFifoReader * reader;
};

#endif //GTKMM_MVC_TEST_MPDREADERSERVICE_H
