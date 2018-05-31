//
// Created by chris on 5/15/18.
//

#include "VisualizerConfig.h"

VisualizerConfig::VisualizerConfig(std::string fileName, int sampleSize, int defaultVisualizer)
    : fileName(fileName), sampleSize(sampleSize), defaultVisualizer(defaultVisualizer)
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

int VisualizerConfig::getDefaultVisualizer() {
    return this->defaultVisualizer;
}

void VisualizerConfig::setDefaultVisualizer(int value) {
    this->defaultVisualizer = value;
}