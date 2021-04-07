cmake_minimum_required(VERSION 3.16)
project(Project VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Common sources
set(SOURCES
        unit/Unit.cpp
        unit/BasicArmor.cpp
        unit/BasicFirearmWeapon.cpp
        unit/BasicLaserWeapon.cpp

        unit/soldier/Soldier.cpp
        unit/soldier/armor/SoldierStandardArmor.cpp
        unit/soldier/armor/SoldierCompositeArmor.cpp
        unit/soldier/weapon/firearm/SoldierFirearmMachineGun.cpp
        unit/soldier/weapon/firearm/SoldierFirearmWeaponFactory.cpp
        unit/soldier/weapon/firearm/SoldierFirearmPistol.cpp
        unit/soldier/weapon/firearm/SoldierFirearmShotgun.cpp
        unit/soldier/weapon/firearm/SoldierFirearmSniperRifle.cpp
        unit/soldier/weapon/laser/SoldierLaserMachineGun.cpp
        unit/soldier/weapon/laser/SoldierLaserWeaponFactory.cpp
        unit/soldier/weapon/laser/SoldierLaserPistol.cpp
        unit/soldier/weapon/laser/SoldierLaserShotgun.cpp
        unit/soldier/weapon/laser/SoldierLaserSniperRifle.cpp
        unit/soldier/SoldierBuilder.cpp

        unit/drone/Drone.cpp
        unit/drone/armor/DroneStandardArmor.cpp
        unit/drone/weapon/firearm/DroneFirearmMachineGun.cpp
        unit/drone/weapon/firearm/DroneFirearmWeaponFactory.cpp
        unit/drone/weapon/laser/DroneLaserMachineGun.cpp
        unit/drone/weapon/laser/DroneLaserWeaponFactory.cpp
        unit/drone/DroneBuilder.cpp

        config/Config.cpp
        config/GameConfig.cpp
        config/INIConfigStructureReader.cpp

        frontend/IFrontendEvents.cpp
        frontend/IEvent.cpp
        frontend/Input.cpp)

# Sources for main executable
set(MAIN_SOURCES main.cpp ${SOURCES})

# Main executable
add_executable(Project ${MAIN_SOURCES})

# Documentation target
set(DOC_COMMAND SOURCE_DIR=${CMAKE_SOURCE_DIR} doxygen ${CMAKE_SOURCE_DIR}/Doxyfile)
add_custom_target(doc COMMAND ${DOC_COMMAND})