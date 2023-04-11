QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

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
    coherence.cpp \
    heartwave.cpp \
    lights.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    mediator.cpp \
    mockheartrate.cpp \
    qcustomplot.cpp

HEADERS += \
    coherence.h \
    heartwave.h \
    lights.h \
    log.h \
    mainwindow.h \
    mediator.h \
    mockheartrate.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Downloads/comp3004team3-master/res/buttons/backButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/chargeButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/downButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/leftButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/menuButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/okButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/powerButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/rightButton.svg \
    ../../Downloads/comp3004team3-master/res/buttons/upButton.svg \
    ../../team3/res/buttons/backButton.svg \
    ../../team3/res/buttons/chargeButton.svg \
    ../../team3/res/buttons/downButton.svg \
    ../../team3/res/buttons/leftButton.svg \
    ../../team3/res/buttons/menuButton.svg \
    ../../team3/res/buttons/okButton.svg \
    ../../team3/res/buttons/powerButton.svg \
    ../../team3/res/buttons/rightButton.svg \
    ../../team3/res/buttons/upButton.svg

RESOURCES += \
    resources.qrc
