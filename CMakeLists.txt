cmake_minimum_required (VERSION 2.6)

project (decayWithSpinTest)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb -std=c++11")

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.hh)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${Geant4_INCLUDE_DIR})

add_executable(runSim ${PROJECT_SOURCE_DIR}/runSim.cc ${sources} ${headers})

target_link_libraries (runSim ${Geant4_LIBRARIES})

set(SCRIPTS
  vis.mac
  do1.mac
  )

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
