cmake_minimum_required(VERSION 3.16)
project(Helpdesk VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Helpdesk
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    ticketdialog.cpp ticketdialog.h ticketdialog.ui
    tickettablemodel.cpp tickettablemodel.h
    ticketrepository.cpp ticketrepository.h
    ticket.h
)

target_link_libraries(Helpdesk PRIVATE Qt6::Widgets)
