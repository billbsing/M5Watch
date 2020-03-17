#include <M5StickC.h>

#include "PageManager.h"
#include "TextPage.h"

PageManager pageManager;
TextPage homePage("Home");
TextPage resetPage("Reset");

void setup() {
    pageManager.add(&homePage);
    pageManager.add(&resetPage);
}


void loop() {
    M5.BtnA.read();
    if ( M5.BtnA.isPressed() ) {
        pageManager.next();
    }
    delay(500);
}
