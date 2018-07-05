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
    this->windowedFrame = new double[sampleSize];
    this->processedDataBuffer = new double[sampleSize];
    this->fftInput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (sampleSize));
    this->fftOutput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (sampleSize));
    this->fftPlan = fftw_plan_dft_1d(sampleSize, fftInput, fftOutput, FFTW_FORWARD, FFTW_ESTIMATE);
}

FifoProcessorService::~FifoProcessorService() {

    //free allocated memory
    delete(processedDataBuffer);
    delete(windowedFrame);
    fftw_destroy_plan(fftPlan);
    fftw_free(fftOutput);

}

void FifoProcessorService::process(uint16_t *dataBuffer) {

    //apply hamming window
    for (int i = 0; i < sampleSize; i++) {
        //windowedFrame[i] = 1;
        windowedFrame[i] = 0.54 - 0.46 * cos(2*M_PI*i/(sampleSize));
    }

    //load data for fft
    for(int i = 0; i < sampleSize; i++){
        fftInput[i][0] = dataBuffer[i] * windowedFrame[i];
        fftInput[i][1] = 0;
    }

    //execute fft
    fftw_execute(fftPlan);

    for(int i = 0; i < sampleSize; i++){
        //convert to polar notation
        double mag = sqrt(fftOutput[i][0] * fftOutput[i][0] + fftOutput[i][1] * fftOutput[i][1]);
        //convert to dB Scale
        processedDataBuffer[i] = 20*log10(mag);
    }

}

void FifoProcessorService::loadAveragedData(double *buffer, int length) {

    uint16_t * dataBuffer = this->readerService->getData();
    process(dataBuffer);

    int averageStep = (sampleSize / 2) / length;

//    if(averageStep == 1){
//        for(int i = 0; i < (sampleSize/2); i++){
//            buffer[i] = processedDataBuffer[i];
//        }
//        return;
//    }

    int k = 0;
    double avg = processedDataBuffer[0];
    for(int i = 1; i < (sampleSize / 2 + 1); i += averageStep){

        for(int j = 0; j < averageStep; j++){
            avg += processedDataBuffer[i+j];
        }
        buffer[k] = avg / averageStep;
        k++;
        avg = 0;
    }
}

void FifoProcessorService::reInit() {

    //free old allocation
    delete(processedDataBuffer);
    delete(windowedFrame);
    fftw_destroy_plan(fftPlan);
    fftw_free(fftOutput);

    //allocate new memory with config parameters
    VisualizerConfig * config = configService->getConfig();
    this->sampleSize = config->getSampleSize();
    this->windowedFrame = new double[sampleSize];
    this->processedDataBuffer = new double[sampleSize];
    this->fftOutput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (sampleSize));
    this->fftPlan = fftw_plan_dft_1d(sampleSize, fftInput, fftOutput, FFTW_FORWARD, FFTW_EXHAUSTIVE);

}