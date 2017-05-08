# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Shipwrecked

HEADERS = \
   $$PWD/game_functions.h \
   $$PWD/physics.h \
   $$PWD/players.h \
   $$PWD/sdl_functions.h \
    test.h

SOURCES = \
   $$PWD/game_functions.c \
   $$PWD/physics.c \
   $$PWD/players.c \
   $$PWD/sdl_functions.c \
   $$PWD/main.c

LIBS += -lSDL2 -lSDL2_image

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 
