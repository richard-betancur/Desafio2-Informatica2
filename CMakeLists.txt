cmake_minimum_required(VERSION 3.16)

project(Desafio2-informatica2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Desafio2-informatica2
    main.cpp
    almacenamiento.h
    almacenamiento.cpp
    solicitudamistad.cpp
    solicitudamistad.h
    usuario.h
    usuario.cpp
    redsocial.h
    redsocial.cpp
    )

include(GNUInstallDirs)
install(TARGETS Desafio2-informatica2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
