//
// Created by chris on 5/15/18.
//

#include "VisualizerConfig.h"

VisualizerConfig::VisualizerConfig(std::string fileName, int sampleRate, uint8_t fpsCount)
    : fileName(fileName), sampleSize(sampleSize), sampleRate(sampleRate), fpsCount(fpsCount)
{
    sampleSize = sampleRate / fpsCount;
}

int VisualizerConfig::getSampleSize(){
    return this->sampleSize;
}

std::string VisualizerConfig::getFileName(){
    return this->fileName;
}

void VisualizerConfig::setFileName(std::string value){
    this->fileName = value;
}

int VisualizerConfig::getSampleRate() {
    return this->sampleRate;
}

void VisualizerConfig::setSampleRate(int value){
    this->sampleRate = value;
    this->sampleSize = (sampleRate / fpsCount);
}

void VisualizerConfig::setFpsCount(uint8_t value) {
    this->fpsCount = value;
    this->sampleSize = (sampleRate / fpsCount);
}

uint8_t VisualizerConfig::getFpsCount(){
    return fpsCount;
}