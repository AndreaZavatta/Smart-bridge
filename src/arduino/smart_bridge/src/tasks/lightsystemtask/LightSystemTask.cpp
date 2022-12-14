#include <Arduino.h>
#include "LightSystemTask.h"
#include "global.h"

LightSystemTask::LightSystemTask(LedTask *led, PirImpl *pir, LightSensor *lightSensor) {
    this->led = led;
    this->pir = pir;
    this->lightSensor = lightSensor;
    time = 0;
}

void LightSystemTask::init(int period) {
    Task::init(period);
    lightTurnedOn = false;
}

void LightSystemTask::tick() {
    this->led->setActive(true);
    if (!lightTurnedOn && pir->isMotionDetected() && lightSensor->getLight() < LIGHTLEVEL) {
        led->setStrategy(new StrategyOn());
        lightTurnedOn = true;
        time = millis();
    } else if (lightTurnedOn && ((!pir->isMotionDetected() && millis() - time > 4000) || lightSensor->getLight() > LIGHTLEVEL)) {
        led->setStrategy(new StrategyOff());
        lightTurnedOn = false;
    }
    
}

void LightSystemTask::notified(int notify) {
    notification = notify;
    if(notify == ALARM){
        lightTurnedOn = false;
        led->setStrategy(new StrategyOff());
        this->setActive(false);
        Serial.println("SYSTEM OFF ");
    }else{
        this->setActive(true);
        if(digitalRead(led->getPin())){
            Serial.println("ON ");
        }else{
            Serial.println("OFF ");
        }
    }
}
