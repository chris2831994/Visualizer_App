//
// Created by chris on 5/10/18.
//

#ifndef GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H
#define GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H

#include <memory>
#include <fftw3.h>
#include "IFifoProcessorService.h"
#include "IFifoReaderService.h"
#include "IConfigService.h"

class FifoProcessorService : public IFifoProcessorService{
public :
    //Constructor
    FifoProcessorService(std::shared_ptr<IFifoReaderService> readerService, std::shared_ptr<IConfigService> configService);
    //Destructor
    ~FifoProcessorService();

    //public Methods
    void loadAveragedData(double * buffer, int length);
    void reInit();

protected:
    //protected Methods
    void process(uint16_t * dataBuffer);
    //uint16_t * average();

    //protected Vars
    std::shared_ptr<IFifoReaderService> readerService;
    std::shared_ptr<IConfigService> configService;
    double *processedDataBuffer;
    double *windowedFrame;
    fftw_complex *fftInput, *fftOutput;
    fftw_plan fftPlan;
    int sampleSize;

};

#endif //GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H
