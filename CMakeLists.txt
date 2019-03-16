cmake_minimum_required(VERSION 3.13)
project(PracticeStuff)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(PracticeStuff
        CompileTimeError.h
        CreatorLib.h
        Creators.h
        main.cpp
        PartialTemplateSpecialization.h
        NiftyContainer.h
        TypeToTypeMapping.h
        TypeSelection.h TypeLists.h)
