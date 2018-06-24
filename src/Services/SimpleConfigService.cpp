//
// Created by chris on 5/15/18.
//

#include "SimpleConfigService.h"
#include <iostream>
using namespace std;

SimpleConfigService::SimpleConfigService(int sampleSize, std::string fifoPath){
    this->config = new VisualizerConfig(fifoPath, sampleSize, 1);
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
    cout << "DefaultVis :   " << config->getDefaultVisualizer() << endl;
}