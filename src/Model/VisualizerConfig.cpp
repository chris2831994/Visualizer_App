//
// Created by chris on 5/15/18.
//

#include "VisualizerConfig.h"

VisualizerConfig::VisualizerConfig(std::string fileName, int sampleSize)
    : fileName(fileName), sampleSize(sampleSize)
{}

int VisualizerConfig::getSampleSize(){
    return this->sampleSize;
}

void VisualizerConfig::setSampleSize(int value){
    this->sampleSize = value;
}

std::string VisualizerConfig::getFileName(){
    return this->fileName;
}

void VisualizerConfig::setFileName(std::string value){
    this->fileName = value;
}