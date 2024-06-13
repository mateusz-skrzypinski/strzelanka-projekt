TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Bullet.cpp \
        Character.cpp \
        Chronobreak.cpp \
        Dash.cpp \
        Fireball.cpp \
        Guns.cpp \
        Monster.cpp \
        Skills.cpp \
        Zap.cpp \
        main.cpp \
        menu.cpp \
        shop_menu.cpp \
        start_menu.cpp \
        trud_menu.cpp

INCLUDEPATH += "C:\Users\skrzy\Documents\SFML-2.6.1\include"
LIBS += -L"C:/Users/skrzy/Documents/SFML-2.6.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

DISTFILES += \
    img/Fireball.png \
    img/Zap.png \
    strzelanka-projekt.pro.user

HEADERS += \
    include/Bullet.h \
    include/Character.h \
    include/Chronobreak.h \
    include/Dash.h \
    include/Fireball.h \
    include/Guns.h \
    include/Monster.h \
    include/Skills.h \
    include/Zap.h \
    include/menu.h \
    include/shop_menu.h \
    include/start_menu.h \
    include/trud_menu.h \
    start.h
