# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = memento

CONFIG += sailfishapp

SOURCES += src/memento.cpp \
    src/tasklist.cpp \
    src/ordering.cpp \
    src/listcollection.cpp \
    src/listwrapper.cpp

OTHER_FILES += qml/memento.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/memento.changes.in \
    rpm/memento.spec \
    rpm/memento.yaml \
    translations/*.ts \
    memento.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/memento-de.ts

HEADERS += \
    src/item.h \
    src/common.h \
    src/tasklist.h \
    src/ordering.h \
    src/listcollection.h \
    src/listwrapper.h

