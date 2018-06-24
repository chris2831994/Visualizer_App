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

    this->segmentLength = sampleSize / 8;

    //lprocessed data buffer, length of n/2 +1 where n is fft length
    this->processedDataBuffer_seg0 = new uint16_t[segmentLength/2 + 1];

    //allocate segment 0, input length = n, output length = n/2 + 1 where n is fft length
    this->fftInput_seg0 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg0 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg0 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg0, this->fftOutput_seg0, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 1
    //this->processedDataBuffer_seg1 = new uint16_t[sampleSize];
    this->fftInput_seg1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg1 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg1, this->fftOutput_seg1, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 2
    //this->processedDataBuffer_seg2 = new uint16_t[sampleSize];
    this->fftInput_seg2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg2 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg2, this->fftOutput_seg2, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 3
    //this->processedDataBuffer_seg3 = new uint16_t[sampleSize];
    this->fftInput_seg3 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg3 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg3 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg3, this->fftOutput_seg3, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 4
    //this->processedDataBuffer_seg4 = new uint16_t[sampleSize];
    this->fftInput_seg4 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg4 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg4 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg4, this->fftOutput_seg4, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 5
    //this->processedDataBuffer_seg5 = new uint16_t[sampleSize];
    this->fftInput_seg5 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg5 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg5 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg5, this->fftOutput_seg5, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 6
    //this->processedDataBuffer_seg6 = new uint16_t[sampleSize];
    this->fftInput_seg6 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg6 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg6 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg6, this->fftOutput_seg6, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 7
    //this->processedDataBuffer_seg7 = new uint16_t[sampleSize];
    this->fftInput_seg7 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg7 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg7 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg7, this->fftOutput_seg7, FFTW_FORWARD,  FFTW_ESTIMATE);
}

FifoProcessorService::~FifoProcessorService() {

    //free allocated memory for segment 0
    delete(this->processedDataBuffer_seg0);
    fftw_destroy_plan(fftPlan_seg0);
    fftw_free(fftInput_seg0);
    fftw_free(fftOutput_seg0);

    //free allocated memory for segment 1
    //delete(this->processedDataBuffer_seg1);
    fftw_destroy_plan(fftPlan_seg1);
    fftw_free(fftInput_seg1);
    fftw_free(fftOutput_seg1);

    //free allocated memory for segment 2
    //delete(this->processedDataBuffer_seg2);
    fftw_destroy_plan(fftPlan_seg2);
    fftw_free(fftInput_seg2);
    fftw_free(fftOutput_seg2);

    //free allocated memory for segment 3
    //delete(this->processedDataBuffer_seg3);
    fftw_destroy_plan(fftPlan_seg3);
    fftw_free(fftInput_seg3);
    fftw_free(fftOutput_seg3);

    //free allocated memory for segment 4
    //delete(this->processedDataBuffer_seg4);
    fftw_destroy_plan(fftPlan_seg4);
    fftw_free(fftInput_seg4);
    fftw_free(fftOutput_seg4);

    //free allocated memory for segment 5
    //delete(this->processedDataBuffer_seg5);
    fftw_destroy_plan(fftPlan_seg5);
    fftw_free(fftInput_seg5);
    fftw_free(fftOutput_seg5);

    //free allocated memory for segment 6
    //delete(this->processedDataBuffer_seg6);
    fftw_destroy_plan(fftPlan_seg6);
    fftw_free(fftInput_seg6);
    fftw_free(fftOutput_seg6);

    //free allocated memory for segment 7
    //delete(this->processedDataBuffer_seg7);
    fftw_destroy_plan(fftPlan_seg7);
    fftw_free(fftInput_seg7);
    fftw_free(fftOutput_seg7);
}

void FifoProcessorService::process(uint16_t *dataBuffer) {

    //load data into real part segments, initialize imaginary parts with 0

    int offset_seg1 = segmentLength;
    int offset_seg2 = 2 * segmentLength;
    int offset_seg3 = 3 * segmentLength;
    int offset_seg4 = 4 * segmentLength;
    int offset_seg5 = 5 * segmentLength;
    int offset_seg6 = 6 * segmentLength;
    int offset_seg7 = 7 * segmentLength;

    for(int i = 0; i < segmentLength; i++){
        fftInput_seg0[i][0] = dataBuffer[i];
        fftInput_seg0[i][1] = 0;

        fftInput_seg1[i][0] = dataBuffer[i + offset_seg1];
        fftInput_seg1[i][1] = 0;

        fftInput_seg2[i][0] = dataBuffer[i + offset_seg2];
        fftInput_seg2[i][1] = 0;

        fftInput_seg3[i][0] = dataBuffer[i + offset_seg3];
        fftInput_seg3[i][1] = 0;

        fftInput_seg4[i][0] = dataBuffer[i + offset_seg4];
        fftInput_seg4[i][1] = 0;

        fftInput_seg5[i][0] = dataBuffer[i + offset_seg5];
        fftInput_seg5[i][1] = 0;

        fftInput_seg6[i][0] = dataBuffer[i + offset_seg6];
        fftInput_seg6[i][1] = 0;

        fftInput_seg7[i][0] = dataBuffer[i + offset_seg7];
        fftInput_seg7[i][1] = 0;
    }

    //execute ffts of all segments
    fftw_execute(fftPlan_seg0);
    fftw_execute(fftPlan_seg1);
    fftw_execute(fftPlan_seg2);
    fftw_execute(fftPlan_seg3);
    fftw_execute(fftPlan_seg4);
    fftw_execute(fftPlan_seg5);
    fftw_execute(fftPlan_seg6);
    fftw_execute(fftPlan_seg7);

    //average segments, convert to real number, convert to dB scale, write to processedData Buffer
    for(int i =0; i< ((segmentLength / 2) +1); i++){

        double avgRe = fftOutput_seg0[i][0]
                    + fftOutput_seg1[i][0]
                    + fftOutput_seg2[i][0]
                    + fftOutput_seg3[i][0]
                    + fftOutput_seg4[i][0]
                    + fftOutput_seg5[i][0]
                    + fftOutput_seg6[i][0]
                    + fftOutput_seg7[i][0];
        avgRe = avgRe / 8;
        double avgIm = fftOutput_seg0[i][1]
                    + fftOutput_seg1[i][1]
                    + fftOutput_seg2[i][1]
                    + fftOutput_seg3[i][1]
                    + fftOutput_seg4[i][1]
                    + fftOutput_seg5[i][1]
                    + fftOutput_seg6[i][1]
                    + fftOutput_seg7[i][1];
        avgIm = avgIm / 8;

        int sq = sqrt(pow(avgRe, 2) + pow(avgIm, 2));
        int res = round(20*log10(sq));
        if(res < 0) res = 0;
        this->processedDataBuffer_seg0[i] = res;
        //std::cout << res << " ";
    }
    //std::cout << std::endl;
}

uint16_t * FifoProcessorService::getProcessedData() {
    uint16_t * dataBuffer = this->readerService->getData();
    process(dataBuffer);
    return dataBuffer;
}

void FifoProcessorService::loadAveragedData(uint16_t *buffer, int length) {

    uint16_t * dataBuffer = this->readerService->getData();
    process(dataBuffer);

    int averageStep = (segmentLength/2 + 1) / length;

    if(averageStep == 1){
        for(int i = 0; i < (segmentLength/2 + 1); i++){
            buffer[i] = processedDataBuffer_seg0[i];
        }
        return;
    }

    int k = 0;
    for(int i = 0; i < (segmentLength/2 + 1); i += averageStep){
        int avg = 0;
        for(int j = 0; j < averageStep; j++){
            avg += processedDataBuffer_seg0[i+j];
        }
        buffer[k] = avg / averageStep;
        k++;
    }
}

void FifoProcessorService::reInit() {

    //free old allocated memory / fftw memory
    //free allocated memory for segment 0
    delete(this->processedDataBuffer_seg0);
    fftw_destroy_plan(fftPlan_seg0);
    fftw_free(fftInput_seg0);
    fftw_free(fftOutput_seg0);

    //free allocated memory for segment 1
    //delete(this->processedDataBuffer_seg1);
    fftw_destroy_plan(fftPlan_seg1);
    fftw_free(fftInput_seg1);
    fftw_free(fftOutput_seg1);

    //free allocated memory for segment 2
    //delete(this->processedDataBuffer_seg2);
    fftw_destroy_plan(fftPlan_seg2);
    fftw_free(fftInput_seg2);
    fftw_free(fftOutput_seg2);

    //free allocated memory for segment 3
    //delete(this->processedDataBuffer_seg3);
    fftw_destroy_plan(fftPlan_seg3);
    fftw_free(fftInput_seg3);
    fftw_free(fftOutput_seg3);

    //free allocated memory for segment 4
    //delete(this->processedDataBuffer_seg4);
    fftw_destroy_plan(fftPlan_seg4);
    fftw_free(fftInput_seg4);
    fftw_free(fftOutput_seg4);

    //free allocated memory for segment 5
    //delete(this->processedDataBuffer_seg5);
    fftw_destroy_plan(fftPlan_seg5);
    fftw_free(fftInput_seg5);
    fftw_free(fftOutput_seg5);

    //free allocated memory for segment 6
    //delete(this->processedDataBuffer_seg6);
    fftw_destroy_plan(fftPlan_seg6);
    fftw_free(fftInput_seg6);
    fftw_free(fftOutput_seg6);

    //free allocated memory for segment 7
    //delete(this->processedDataBuffer_seg7);
    fftw_destroy_plan(fftPlan_seg7);
    fftw_free(fftInput_seg7);
    fftw_free(fftOutput_seg7);

    //allocate new memory with config parameters
    VisualizerConfig * config = configService->getConfig();
    this->sampleSize = config->getSampleSize();

    this->segmentLength = sampleSize / 8;

    //lprocessed data buffer, length of n/2 +1 where n is fft length
    this->processedDataBuffer_seg0 = new uint16_t[segmentLength/2 + 1];

    //allocate segment 0, input length = n, output length = n/2 + 1 where n is fft length
    this->fftInput_seg0 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg0 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg0 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg0, this->fftOutput_seg0, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 1
    //this->processedDataBuffer_seg1 = new uint16_t[sampleSize];
    this->fftInput_seg1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg1 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg1, this->fftOutput_seg1, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 2
    //this->processedDataBuffer_seg2 = new uint16_t[sampleSize];
    this->fftInput_seg2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg2 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg2, this->fftOutput_seg2, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 3
    //this->processedDataBuffer_seg3 = new uint16_t[sampleSize];
    this->fftInput_seg3 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg3 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg3 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg3, this->fftOutput_seg3, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 4
    //this->processedDataBuffer_seg4 = new uint16_t[sampleSize];
    this->fftInput_seg4 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg4 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg4 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg4, this->fftOutput_seg4, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 5
    //this->processedDataBuffer_seg5 = new uint16_t[sampleSize];
    this->fftInput_seg5 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg5 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg5 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg5, this->fftOutput_seg5, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 6
    //this->processedDataBuffer_seg6 = new uint16_t[sampleSize];
    this->fftInput_seg6 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg6 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg6 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg6, this->fftOutput_seg6, FFTW_FORWARD,  FFTW_ESTIMATE);

    //allocate segment 7
    //this->processedDataBuffer_seg7 = new uint16_t[sampleSize];
    this->fftInput_seg7 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (segmentLength));
    this->fftOutput_seg7 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2*(segmentLength/2 + 1)));
    this->fftPlan_seg7 = fftw_plan_dft_1d((sampleSize/8), this->fftInput_seg7, this->fftOutput_seg7, FFTW_FORWARD,  FFTW_ESTIMATE);

}