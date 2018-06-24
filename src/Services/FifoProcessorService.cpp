//
// Created by chris on 5/10/18.
//

#include "FifoProcessorService.h"
#include "IFifoReaderService.h"
#include <stdlib.h>
#include <fftw3.h>
#include <cmath>
#include <memory>
#include <iostream>


FifoProcessorService::FifoProcessorService(std::shared_ptr<IFifoReaderService> readerService, std::shared_ptr<IConfigService> configService)
        : readerService(readerService),
          configService(configService)
{
    VisualizerConfig * config = configService->getConfig();
    this->sampleSize = config->getSampleSize();

      this->processedDataBuffer = new uint16_t[sampleSize/2 +1];
      this->fftOutput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (sampleSize));
      this->realInput = new double[sampleSize];
      this->fftPlan = fftw_plan_dft_r2c_1d(sampleSize, realInput, fftOutput, FFTW_ESTIMATE_PATIENT);
}

FifoProcessorService::~FifoProcessorService() {

    //free allocated memory
    delete(processedDataBuffer);
    delete(realInput);
    fftw_destroy_plan(fftPlan);
    fftw_free(fftOutput);

}

void FifoProcessorService::process(uint16_t *dataBuffer) {

    for(int i = 0; i < sampleSize; i++){
        realInput[i] = dataBuffer[i];
    }

    fftw_execute(fftPlan);

    for(int i = 0; i < sampleSize/2 +1; i++){
        //convert to polar notation
        int mag = sqrt(fftOutput[i][0] * fftOutput[i][0] + fftOutput[i][1] + fftOutput[i][1]);
        //convert to dB Scale
        processedDataBuffer[i] = round(20*log10(mag));
    }

}

uint16_t * FifoProcessorService::getProcessedData() {
    uint16_t * dataBuffer = this->readerService->getData();
    process(dataBuffer);
    return dataBuffer;
}

void FifoProcessorService::loadAveragedData(uint16_t *buffer, int length) {

    uint16_t * dataBuffer = this->readerService->getData();
    process(dataBuffer);

    int averageStep = (sampleSize/ 2) / length;

    if(averageStep == 1){
        for(int i = 1; i < (sampleSize/2); i++){
            buffer[i] = processedDataBuffer[i];
        }
        return;
    }

    int k = 0;
    for(int i = 1; i < (sampleSize/2); i += averageStep){
        int avg = 0;
        for(int j = 0; j < averageStep; j++){
            avg += processedDataBuffer[i+j];
        }
        buffer[k] = avg / averageStep;
        k++;
    }
}

void FifoProcessorService::reInit() {

    //free old allocation
    delete(processedDataBuffer);
    delete(realInput);
    fftw_destroy_plan(fftPlan);
    fftw_free(fftOutput);

    //allocate new memory with config parameters
    VisualizerConfig * config = configService->getConfig();
    this->sampleSize = config->getSampleSize();
    this->processedDataBuffer = new uint16_t[sampleSize/2 + 1];
    realInput = new double[sampleSize];
    this->fftOutput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (sampleSize));
    this->fftPlan = fftw_plan_dft_1d(sampleSize, fftInput, fftOutput, FFTW_FORWARD, FFTW_EXHAUSTIVE);

}