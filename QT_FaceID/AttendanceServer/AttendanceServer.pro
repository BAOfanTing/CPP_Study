QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    attendancewindow.cpp \
    qfaceobject.cpp \
    register_ui.cpp

HEADERS += \
    attendancewindow.h \
    qfaceobject.h \
    register_ui.h

FORMS += \
    attendancewindow.ui \
    register_ui.ui


#windows 平台添加头文件和库
INCLUDEPATH += E:\Environment\opencv452\include
INCLUDEPATH += E:\Environment\opencv452\include\opencv2
INCLUDEPATH += E:\Environment\SeetaFace2\include
INCLUDEPATH += E:\Environment\SeetaFace2\include\seeta
LIBS += E:\Environment\opencv452\x64\mingw\lib\libopencv*
LIBS += E:\Environment\SeetaFace2\lib\libSeeta*


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
