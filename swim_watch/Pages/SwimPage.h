// TextPage

#ifndef SWIM_PAGE_H
#define SWIM_PAGE_H


#include <Page.h>
#include <TextWidget.h>
#include "VibratorMotor.h"

#define VIBRATOR_MOTOR_PIN            32


class SwimPage: public Page
{
public:
    SwimPage();

    void init();
    void begin();
    void end();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

protected:

private:
    TextWidget _menuStartStop;
    VibratorMotor _vibratorMotor;

};


#endif          // SWIM_PAGE_H
