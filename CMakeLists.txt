#*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
#This source file is part of the
#   ___                 __    __ _ _    _
#  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
# //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
#/ \_// (_| | | |  __/  \  /\  /| |   <| |
#\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
#      |___/
#      Tutorial Framework
#      http://www.ogre3d.org/tikiwiki/
#-----------------------------------------------------------------------------
#*/
cmake_minimum_required(VERSION 2.6)

project(Game)


if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

set(HDRS
	Game.h
	../breslingameserver/GameServer.h
	../breslinlistenserver/ListenServer.h
	../breslinclient/Client.h
)

set(SRCS
	Game.cpp
	../breslingameserver/GameServer.cpp
	../breslinlistenserver/ListenServer.cpp
	Main.cpp
	../breslinclient/Client.cpp
)



add_executable(Game WIN32 ${HDRS} ${SRCS})


