/*

    M5Watch

*/

#ifndef MEDIA_WATCH_H
#define MEDIA_WATCH_H



#include "PageId.h"
#include "EventId.h"
#include <Settings.h>
#include <SerialDebug.h>
#include <EventQueue.h>
#include <PowerStatus.h>
#include <WifiManager.h>

extern Settings settings;
extern SerialDebug debug;
extern EventQueue eventQueue;
extern PowerStatus powerStatus;
extern WifiManager wifiManager;

#endif                  // MEDIA_WATCH_H
