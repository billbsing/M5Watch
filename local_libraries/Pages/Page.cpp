#include <Page.h>
#include <PageManager.h>

Page::Page(PageManager *manager):
_manager(manager),
_index(0),
_isVisible(false) {

}

void Page::drawPage() {
    if (_isVisible) {
        _manager->drawPage();
    }
}
