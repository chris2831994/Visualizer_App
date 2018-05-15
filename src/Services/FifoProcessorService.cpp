//
// Created by chris on 5/10/18.
//

#include "FifoProcessorService.h"
#include "IFifoReaderService.h"
#include <stdlib.h>
#include <fftw3.h>
#include <cmath>
#include <memory>


FifoProcessorService::FifoProcessorService(std::shared_ptr<IFifoReaderService> readerService)
        : readerService(readerService)
{
    this->sampleSize = 1024;
    this->averageStep = 1024 / 128;
    this->averageDataBuffer = (uint16_t *) malloc(sizeof(uint16_t) * 128);
    this->processedDataBuffer = (uint16_t *) malloc(sizeof(uint16_t) * 1024);
    this->fftInput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1024);
    this->fftOutput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1024);
    this->fftPlan = fftw_plan_dft_1d(1024, this->fftInput, this->fftOutput, FFTW_FORWARD,  FFTW_ESTIMATE);
}

FifoProcessorService::~FifoProcessorService() {
    delete(readerService);
    free(this->processedDataBuffer);
    free(this->averageDataBuffer);
    fftw_destroy_plan(fftPlan);
    fftw_free(fftInput);
    fftw_free(fftOutput);
}

void FifoProcessorService::process(uint16_t *dataBuffer) {

    for(int i = 0; i < sampleSize; i++){
        fftInput[i][0] = dataBuffer[i];
        fftInput[i][1] = 0;
    }
    fftw_execute(fftPlan);
    for(int i =0; i<sampleSize; i++){


        int sq = sqrt(pow(fftOutput[i][0], 2) + pow(fftOutput[i][1], 2));
        int res = round(20*log10(sq));

        this->processedDataBuffer[i] = res;
        //std::cout << res;
    }

}


uint16_t * FifoProcessorService::getProcessedData() {
    uint16_t * dataBuffer = this->readerService->getData();
    int length = sizeof(dataBuffer) / sizeof(uint16_t);
    process(dataBuffer);
    return average();
}

uint16_t *FifoProcessorService::average(){

    int k = 0;
    for(int i = 0; i < sampleSize; i+=averageStep){
        int avg = 0;
        for(int j = 0; j < averageStep; j++){
            avg += processedDataBuffer[i+j];
        }
        this->averageDataBuffer[k] = avg/averageStep;
        k++;
    }

    return averageDataBuffer;

}