project(marco)

SET(CMAKE_CXX_FLAGS_DEBUG "-lpthread")
SET(CMAKE_CXX_FLAGS_RELEASE "-lpthread")
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

find_package(Boost 1.40.0 REQUIRED system)

add_executable(${PROJECT_NAME} ${SRC_LIST})


target_link_libraries (${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin/${PROJECT_NAME})

set(SYSTEMD_TARGET_DIR "/etc/systemd/system" CACHE PATH "Path to systemd units")
set(SYSTEMD_SOURCE_DIR "${CMAKE_SOURCE_DIR}/systemd")

configure_file(${SYSTEMD_SOURCE_DIR}/${PROJECT_NAME}.service ${PROJECT_BINARY_DIR}/systemd/${PROJECT_NAME}.service)

install(FILES ${PROJECT_BINARY_DIR}/systemd/${PROJECT_NAME}.service DESTINATION ${SYSTEMD_TARGET_DIR})


