QT       += core gui
QT += webenginewidgets
QT +=network
QT +=testlib
QT +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG(debug, debug|release):{
LIBS+=-LE:/OpenCV/opencv/build/x64/vc15/lib\
-lopencv_world430d
}else:CONFIG(release, debug|release):{
LIBS+=-LE:/OpenCV/opencv/build/x64/vc15/lib\
-lopencv_world430
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acquisition/betinfo.cpp \
    acquisition/betinformation.cpp \
    acquisition/mymsg.cpp \
    acquisition/pceggsdatabase.cpp \
    algorithm/pceggssvm.cpp \
    main.cpp \
    tools/networkcookie.cpp \
    window/formlogin.cpp \
    window/formpredict.cpp \
    window/mainwindow.cpp \
    window/subform.cpp

HEADERS += \
    acquisition/betinfo.h \
    acquisition/betinformation.h \
    acquisition/mymsg.h \
    acquisition/pceggsdatabase.h \
    algorithm/pceggssvm.h \
    global.h \
    tools/networkcookie.h \
    window/formlogin.h \
    window/formpredict.h \
    window/mainwindow.h \
    window/subform.h

FORMS += \
    formlogin.ui \
    formpredict.ui \
    mainwindow.ui

INCLUDEPATH+=E:/OpenCV/opencv/build/include/opencv2
INCLUDEPATH+=E:/OpenCV/opencv/build/include



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
