//
// Created by chris on 5/10/18.
//

#ifndef GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H
#define GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H

#include <memory>
#include <fftw3.h>
#include "IFifoProcessorService.h"
#include "IFifoReaderService.h"

class FifoProcessorService : public IFifoProcessorService{
public :
    //Constructor
    FifoProcessorService(std::shared_ptr<IFifoReaderService> readerService);
    //Destructor
    ~FifoProcessorService();

    //public Methods
    uint16_t * getProcessedData();
protected:
    //protected Methods
    void process(uint16_t * dataBuffer);
    uint16_t *average();

    //protected Vars
    std::shared_ptr<IFifoReaderService> readerService;
    fftw_complex *fftInput, *fftOutput;
    fftw_plan fftPlan;
    uint16_t *dataBuffer;
    uint16_t *processedDataBuffer;
    uint16_t *averageDataBuffer;
    int sampleSize;
    int averageStep;
};

#endif //GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H
