cmake_minimum_required(VERSION 3.16)
project(Helpdesk VERSION 0.1 LANGUAGES CXX) # [cite: 90]

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets) # [cite: 175]

add_executable(Helpdesk
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    ticketdialog.cpp ticketdialog.h ticketdialog.ui
)

target_link_libraries(Helpdesk PRIVATE Qt6::Widgets) # [cite: 182]
