QT += core
QT -= gui

CONFIG += c++14

TARGET = LB_3_Inventory_Qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    computer.cpp \
    date.cpp \
    embedded_gsm.cpp \
    gsm_device.cpp \
    inventory_device.cpp \
    mobile_phone.cpp \
    server_computer.cpp \
    devicefactory.cpp \
    html_device_reporter.cpp \
    my_utility.cpp \
    report_manager.cpp \
    device_reporter.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    computer.h \
    date.h \
    embedded_gsm.h \
    gsm_device.h \
    inventory_device.h \
    mobile_phone.h \
    server_computer.h \
    devicefactory.h \
    device_reporter.h \
    html_device_reporter.h \
    my_utility.h \
    report_manager.h
