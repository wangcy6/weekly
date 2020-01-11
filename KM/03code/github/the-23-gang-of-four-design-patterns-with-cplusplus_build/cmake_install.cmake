# Install script for directory: /home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/创建型模式/AbstractFactory/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/创建型模式/Builder/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/创建型模式/Factory/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/创建型模式/Prototype/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/创建型模式/Singleton/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Proxy/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Flyweight/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Adapter/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Composite/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Bridge/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Facade/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/结构型模式/Decorator/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Visitor/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Interpreter/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Command/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Strategy/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Observer/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/State/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/ChainofResponsibility/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Memento/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Template/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Mediator/cmake_install.cmake")
  INCLUDE("/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/行为模式/Iterator/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/code/weekly/KM/03code/github/the-23-gang-of-four-design-patterns-with-cplusplus_build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
