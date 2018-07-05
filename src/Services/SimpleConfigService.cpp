//
// Created by chris on 5/15/18.
//

#include "SimpleConfigService.h"
#include <iostream>
using namespace std;

SimpleConfigService::SimpleConfigService(int sampleRate, std::string fifoPath, uint8_t fps){
    this->config = new VisualizerConfig(fifoPath, sampleRate, fps);
}

SimpleConfigService::~SimpleConfigService() {
    delete(this->config);
}

VisualizerConfig * SimpleConfigService::getConfig() {
    return this->config;
}

void SimpleConfigService::writeConfig(){
    cout << "SimpleConfigService config : " << endl;
    cout << "FifoFile :     " << config->getFileName() << endl;
    cout << "SampleSize :   " << config->getSampleSize() << endl;
    cout << "SampleRate :   " << config->getSampleRate() << endl;
    cout << "Vis Fps :      " << (int)config->getFpsCount() << endl;
}