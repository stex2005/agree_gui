##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(agree_gui)

###########################
add_compile_options(-std=c++11)

####################
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_PREFIX_PATH "/opt/5.12.4/gcc_64/lib/cmake/")


include_directories(${PYTHONHOME}/include)
include_directories(${PYTHONHOME}/Lib/site-packages/numpy/core/include)
link_directories(${PYTHONHOME}/libs)

add_definitions(-DMATPLOTLIBCPP_PYTHON_HEADER=Python.h)


##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(
    catkin
    REQUIRED COMPONENTS
    roscpp
    std_msgs
    message_generation


 )

find_package(PythonLibs 2.7)

find_package(Boost REQUIRED COMPONENTS system)




add_message_files(
    DIRECTORY
    msg
    FILES
    agree_esmacat_command.msg
    agree_emg_status.msg
    )

generate_messages(
    DEPENDENCIES
    roscpp std_msgs
    )


catkin_package(
    LIBRARIES agree_gui
    CATKIN_DEPENDS roscpp std_msgs)

include_directories(${catkin_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything.

##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically
# included via the dependency call in package.xml
#rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
#SET(CMAKE_AUTOUIC ON)



find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport Sql )
#find_package(Qt5 COMPONENTS Multimedia REQUIRED)
#find_package(Qt5 COMPONENTS MultimediaWidgets REQUIRED)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/agree_gui/*.hpp include/agree_gui/*.h)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5PrintSupport_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}






    )



##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

#set( QT_SOURCES
#    src/main.cpp
#    src/main_window.cpp
#    src/qnode.cpp
#    src/login.cpp
#    src/paginaprincipale.cpp
#    src/sc_assistivo.cpp
#    include/agree_gui/main_window.hpp
#    include/agree_gui/qnode.hpp
#    include/agree_gui/login.h
#    include/agree_gui/paginaprincipale.h
#    include/agree_gui/sc_assitivo.h
#    )

##############################################################################
# Binaries
##############################################################################

add_executable(agree_gui ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})



#######
target_include_directories(agree_gui PRIVATE ${PYTHON_INCLUDE_DIRS})
get_filename_component(THIS_APP_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message(STATUS "Example application, ${THIS_APP_NAME}, is ready to build")



target_link_libraries(agree_gui ${QT_LIBRARIES} ${catkin_LIBRARIES} ${PYTHON_LIBRARIES}
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Sql




    )

target_link_libraries(agree_gui matio)
#target_link_libraries(agree_gui
#    Qt5::Multimedia
#    Qt5::MultimediaWidgets
#)


install(TARGETS agree_gui RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})





################
#add_subdirectory(include/agree_gui)



