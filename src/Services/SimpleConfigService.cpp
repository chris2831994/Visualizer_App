//
// Created by chris on 5/15/18.
//

#include "SimpleConfigService.h"

SimpleConfigService::SimpleConfigService() {

    this->config = new VisualizerConfig();

}

SimpleConfigService::~SimpleConfigService() {
    delete(this->config);
}

VisualizerConfig * SimpleConfigService::getConfig() {
    return this->getConfig();
}