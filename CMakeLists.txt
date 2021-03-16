cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Common sources
set(SOURCES
        unit/Unit.cpp unit/IWeapon.cpp unit/IArmor.cpp

        unit/soldier/Soldier.cpp
        unit/soldier/armor/SoldierStandardArmor.cpp
        unit/soldier/armor/SoldierCompositeArmor.cpp
        unit/soldier/weapon/ISoldierMachineGun.cpp
        unit/soldier/weapon/ISoldierPistol.cpp
        unit/soldier/weapon/ISoldierShotgun.cpp
        unit/soldier/weapon/ISoldierSniperRifle.cpp
        unit/soldier/weapon/ISoldierWeaponFactory.cpp
        unit/soldier/SoldierBuilder.cpp

        unit/drone/Drone.cpp
        unit/drone/armor/DroneStandardArmor.cpp
        unit/drone/weapon/IDroneMachineGun.cpp
        unit/drone/weapon/IDroneWeaponFactory.cpp
        unit/drone/DroneBuilder.cpp)

# Sources for main executable
set(MAIN_SOURCES main.cpp ${SOURCES})

# Main executable
add_executable(Project ${MAIN_SOURCES})

# Documentation target
set(DOC_COMMAND SOURCE_DIR=${CMAKE_SOURCE_DIR} doxygen ${CMAKE_SOURCE_DIR}/Doxyfile)
add_custom_target(doc COMMAND ${DOC_COMMAND})