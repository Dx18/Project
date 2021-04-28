cmake_minimum_required(VERSION 3.16)
project(Project VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Common sources
set(SOURCES
        unit/Unit.cpp
        unit/BasicArmor.cpp
        unit/BasicFirearmWeapon.cpp
        unit/BasicLaserWeapon.cpp

        unit/soldier/Soldier.cpp
        unit/soldier/armor/standard/SoldierStandardArmor.cpp
        unit/soldier/armor/standard/SoldierStandardArmorFactory.cpp
        unit/soldier/armor/composite/SoldierCompositeArmor.cpp
        unit/soldier/armor/composite/SoldierCompositeArmorFactory.cpp
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
        unit/drone/armor/standard/DroneStandardArmor.cpp
        unit/drone/armor/standard/DroneStandardArmorFactory.cpp
        unit/drone/armor/composite/DroneCompositeArmor.cpp
        unit/drone/armor/composite/DroneCompositeArmorFactory.cpp
        unit/drone/weapon/firearm/DroneFirearmMachineGun.cpp
        unit/drone/weapon/firearm/DroneFirearmWeaponFactory.cpp
        unit/drone/weapon/laser/DroneLaserMachineGun.cpp
        unit/drone/weapon/laser/DroneLaserWeaponFactory.cpp
        unit/drone/DroneBuilder.cpp

        headquarters_model/HeadquartersModel.cpp
        headquarters_model/Resources.cpp
        headquarters_model/armory/Armory.cpp
        headquarters_model/tech/TechLevel.cpp
        headquarters_model/tech/Tech.cpp

        config/Config.cpp
        config/GameConfig.cpp
        config/INIConfigStructureReader.cpp

        frontend/IFrontendEvents.cpp
        frontend/IEvent.cpp
        frontend/Input.cpp
        frontend/InputEvent.cpp

        frontend/terminal/ColorPair.cpp
        frontend/terminal/CharData.cpp
        frontend/terminal/IRenderSurfaceRead.cpp
        frontend/terminal/IRenderSurfaceWrite.cpp
        frontend/terminal/RenderSurfaceBase.cpp
        frontend/terminal/RenderSurfaceRegion.cpp
        frontend/terminal/RenderSurfaceRegionConst.cpp
        frontend/terminal/ITerminalRenderer.cpp
        frontend/terminal/ITerminalInput.cpp
        frontend/terminal/TerminalEvents.cpp
        frontend/terminal/CursesTerminalFrontend.cpp
        frontend/terminal/TextureReader.cpp
        frontend/terminal/TerminalResources.cpp

        widget/terminal/TerminalContext.cpp
        widget/terminal/TextWidget.cpp
        widget/terminal/SelectionListWidget.cpp
        widget/terminal/SelectionBoxWidget.cpp
        widget/terminal/GridContainerWidget.cpp
        widget/terminal/game/SoldierEquipmentWidget.cpp
        widget/terminal/game/DroneEquipmentWidget.cpp

        object_database/UnitInfo.cpp
        object_database/WeaponClassInfo.cpp
        object_database/WeaponTechInfo.cpp
        object_database/ArmorTechInfo.cpp
        object_database/WeaponInfo.cpp
        object_database/ArmorInfo.cpp)

# Sources for main executable
set(MAIN_SOURCES main.cpp ${SOURCES})

# Main executable
add_executable(Project ${MAIN_SOURCES})

# Linking main executable with `ncurses`
target_link_libraries(Project ${CURSES_LIBRARIES})

# Documentation target
set(DOC_COMMAND SOURCE_DIR=${CMAKE_SOURCE_DIR} doxygen ${CMAKE_SOURCE_DIR}/Doxyfile)
add_custom_target(doc COMMAND ${DOC_COMMAND})
