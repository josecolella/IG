HEADERS = \
  user_code.h
  
SOURCES = \
  user_code.cc \
  practica.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

