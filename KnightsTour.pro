TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    qboard.cpp \
    driver2.cpp

HEADERS += \
    node.h \
    LinkedStack.h \
    coord.h \
    board.h \
    pQueue.h \
    pnode.h \
    qboard.h

