QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
        tst_flashcardstest.cpp \
        ../card.cpp \
        ../cli.cpp \
        ../deck.cpp \
        ../deckmanager.cpp \
        ../utils.cpp

HEADERS += \
    ../card.hh \
    ../cli.hh \
    ../deck.hh \
    ../deckmanager.hh \
    ../utils.hh
