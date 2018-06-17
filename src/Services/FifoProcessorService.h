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
    uint16_t * getProcessedData();
    void loadAveragedData(uint16_t * buffer, int length);
    void reInit();

protected:
    //protected Methods
    void process(uint16_t * dataBuffer);
    //uint16_t * average();

    //protected Vars
    std::shared_ptr<IFifoReaderService> readerService;
    std::shared_ptr<IConfigService> configService;
    fftw_complex *fftInput_seg0, *fftInput_seg1, *fftInput_seg2, *fftInput_seg3, *fftInput_seg4, *fftInput_seg5, *fftInput_seg6, *fftInput_seg7,
            *fftOutput_seg0, *fftOutput_seg1, *fftOutput_seg2, *fftOutput_seg3, *fftOutput_seg4, *fftOutput_seg5, *fftOutput_seg6, *fftOutput_seg7;
    fftw_plan fftPlan_seg0, fftPlan_seg1, fftPlan_seg2, fftPlan_seg3, fftPlan_seg4, fftPlan_seg5, fftPlan_seg6, fftPlan_seg7;
    uint16_t *processedDataBuffer_seg0;
    //uint16_t *averageDataBuffer;
    int sampleSize;
    int segmentLength;
    //int averageStep;
};

#endif //GTKMM_MVC_TEST_FIFOPROCESSORSERVICE_H
