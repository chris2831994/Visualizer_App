//
// Created by chris on 5/15/18.
//

#include "SimpleConfigService.h"
#include <iostream>
using namespace std;

SimpleConfigService::SimpleConfigService(int sampleSize, std::string fifoPath){
    this->config = new VisualizerConfig(fifoPath, 44100, 25);
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
    cout << "Vis Fps :   " << config->getFpsCount() << endl;
}