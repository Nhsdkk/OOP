cmake_minimum_required(VERSION 3.10)

set(SubProjectName "lab_6")

add_library(${SubProjectName}_npc
        src/npc/BaseNpc.cpp
        src/npc/BaseNpc.h

        src/npc/Elf.cpp
        src/npc/Elf.h
        src/npc/Thief.cpp
        src/npc/Thief.h
        src/npc/Squirrel.cpp
        src/npc/Squirrel.h
)

add_library(${SubProjectName}_utils
        src/utils/JsonObject.cpp
        src/utils/JsonObject.h
        src/utils/Point.cpp
        src/utils/Point.h
        src/utils/ISerializable.cpp
        src/utils/ISerializable.h
        src/utils/Vec2D.cpp
        src/utils/Vec2D.h
)

add_library(${SubProjectName}_logger
        src/logger/ILogger.cpp
        src/logger/ILogger.h
        src/logger/FileLogger.cpp
        src/logger/FileLogger.h
        src/logger/ConsoleLogger.cpp
        src/logger/ConsoleLogger.h
)

add_library(${SubProjectName}_backup
        src/backup/BackupHandler.cpp
        src/backup/BackupHandler.h
)

add_library(${SubProjectName}_lib
        src/Field.cpp
        src/Field.h
)

add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_npc PRIVATE ${SubProjectName}_utils ${SubProjectName}_logger)
target_link_libraries(${SubProjectName}_logger PRIVATE ${SubProjectName}_utils)
target_link_libraries(${SubProjectName}_backup PRIVATE ${SubProjectName}_utils)

target_link_libraries(${SubProjectName}_lib PRIVATE ${SubProjectName}_npc ${SubProjectName}_logger ${SubProjectName}_backup)

target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(${SubProjectName}_tests tests/tests.cpp)
target_link_libraries(${SubProjectName}_tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND ${SubProjectName}_tests)