cmake_minimum_required(VERSION 3.16)
project(VSSReferee VERSION 2.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find required packages
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network OpenGL)
find_package(Protobuf REQUIRED)
find_package(OpenGL REQUIRED)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/lib)
set(CMAKE_OBJECT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/obj)

# Set Qt-specific directories
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_MOC_DIR ${CMAKE_BINARY_DIR}/tmp/moc)
set(CMAKE_UIC_DIR ${CMAKE_BINARY_DIR}/tmp/moc)
set(CMAKE_RCC_DIR ${CMAKE_BINARY_DIR}/tmp/rc)

# Compile protobuf files
file(GLOB PROTO_FILES "proto/include/*.proto")
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/proto_output/include)

add_library(proto_msgs)

protobuf_generate(
    TARGET proto_msgs
    LANGUAGE cpp
    IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/include
    PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto_output/include
    APPEND_PATH
    PROTOS ${PROTO_FILES}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/proto_output
)

# Set definitions
add_compile_definitions(QT_DEPRECATED_WARNINGS=1)
add_compile_definitions(APP_VERSION="${PROJECT_VERSION}")
add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}")

# Source files
set(SOURCES
    main.cpp
    src/constants/constants.cpp
    src/recorder/recorder.cpp
    src/refereecore.cpp
    src/soccerview/fieldview/fieldview.cpp
    src/soccerview/fieldview/gltext/gltext.cpp
    src/soccerview/soccerview.cpp
    src/utils/types/angle/angle.cpp
    src/utils/types/field/field.cpp
    src/utils/types/object/object.cpp
    src/utils/types/placedata/placedata.cpp
    src/utils/types/position/position.cpp
    src/utils/types/velocity/velocity.cpp
    src/utils/utils.cpp
    src/world/entities/entity.cpp
    src/utils/exithandler/exithandler.cpp
    src/utils/text/text.cpp
    src/utils/timer/timer.cpp
    src/utils/timer/simulationtime.cpp
    src/world/entities/referee/checkers/ballplay/checker_ballplay.cpp
    src/world/entities/referee/checkers/checker.cpp
    src/world/entities/referee/checkers/goalie/checker_goalie.cpp
    src/world/entities/referee/checkers/halftime/checker_halftime.cpp
    src/world/entities/referee/checkers/stoppedball/checker_stuckedball.cpp
    src/world/entities/referee/checkers/twoattackers/checker_twoattackers.cpp
    src/world/entities/referee/checkers/twodefenders/checker_twodefenders.cpp
    src/world/entities/referee/referee.cpp
    src/world/entities/replacer/replacer.cpp
    src/world/entities/vision/filters/loss/lossfilter.cpp
    src/world/entities/vision/filters/noise/noisefilter.cpp
    src/world/entities/vision/filters/kalman/kalmanfilter.cpp
    src/world/entities/vision/filters/kalman/matrix/matrix.cpp
    src/world/entities/vision/filters/kalman/state/kalmanstate.cpp
    src/world/entities/vision/vision.cpp
    src/world/world.cpp
)

# UI files
set(FORMS
    src/soccerview/soccerview.ui
)

# Resources
set(RESOURCES
    rsc/resources.qrc
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${FORMS} ${RESOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include src)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    proto_msgs
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::OpenGL
    ${Protobuf_LIBRARIES}
    OpenGL::GL
    OpenGL::GLU
)
