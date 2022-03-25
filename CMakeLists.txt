cmake_minimum_required(VERSION 3.21)
project(CheltuieliFamilie C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall -Wextra)

add_executable(CheltuieliFamilie
        Cheltuiala.c
        Cheltuiala.h
        Functii.c
        Functii.h
        Lista.c
        Lista.h
        Main.c
        Teste.c
        Teste.h
        UI.c
        UI.h errors.h ctrl.c ctrl.h)
