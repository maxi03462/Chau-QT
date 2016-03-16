#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T12:24:56
#
#-------------------------------------------------

QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chau
TEMPLATE = app


SOURCES += main.cpp\
        chau.cpp \
    nuevo.cpp \
    nuevomotivo.cpp \
    visualizar_lista.cpp

HEADERS  += chau.h \
    nuevo.h \
    nuevomotivo.h \
    visualizar_lista.h

FORMS    += chau.ui \
    nuevo.ui \
    nuevomotivo.ui \
    visualizar_lista.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

