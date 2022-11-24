#include <Arduino.h>
#include "LightSystemTask.h"

LightSystemTask::LightSystemTask(Led *led, PirImpl *pir, LightSensor *lightSensor) {
    this->led = led;
    this->pir = pir;
    this->lightSensor = lightSensor;
}

void LightSystemTask::init(int period) {
    Task::init(period);
    state = false;
}

void LightSystemTask::tick() {
    
}

void LightSystemTask::getTaskName() {
    Serial.println("LightSystemTask");
}

void LightSystemTask::notified(int notify) {
    Serial.println("LightSystemTask notified");
    if(notify > PEPREALARM){
        this->setActive(false);
    }else{
        this->setActive(true);
    }
}
