# This script locates the CSFML library
# ------------------------------------
#
# Usage
# -----
#
# When you try to locate the CSFML libraries, you must specify which modules you want to use (system, window, graphics, network, audio, main).
# If none is given, the CSFML_LIBRARIES variable will be empty and you'll end up linking to nothing.
# example:
#   find_package(CSFML COMPONENTS graphics window system) # find the graphics, window and system modules
#
# You can enforce a specific version, either MAJOR.MINOR or only MAJOR.
# If nothing is specified, the version won't be checked (i.e. any version will be accepted).
# example:
#   find_package(CSFML COMPONENTS ...)     # no specific version required
#   find_package(CSFML 2 COMPONENTS ...)   # any 2.x version
#   find_package(CSFML 2.4 COMPONENTS ...) # version 2.4 or greater
#
# By default, the dynamic libraries of CSFML will be found. To find the static ones instead,
# you must set the CSFML_STATIC_LIBRARIES variable to TRUE before calling find_package(CSFML ...).
# Since you have to link yourself all the CSFML dependencies when you link it statically, the following
# additional variables are defined: CSFML_XXX_DEPENDENCIES and SFML_DEPENDENCIES (see their detailed
# description below).
# In case of static linking, the SFML_STATIC macro will also be defined by this script.
# example:
#   set(SFML_STATIC_LIBRARIES TRUE)
#   find_package(SFML 2 COMPONENTS network system)
#
# On Mac OS X if SFML_STATIC_LIBRARIES is not set to TRUE then by default CMake will search for frameworks unless
# CMAKE_FIND_FRAMEWORK is set to "NEVER" for example. Please refer to CMake documentation for more details.
# Moreover, keep in mind that SFML frameworks are only available as release libraries unlike dylibs which
# are available for both release and debug modes.
#
# If CSFML is not installed in a standard path, you can use the CSFML_ROOT CMake (or environment) variable
# to tell CMake where CSFML is.
#
# Output
# ------
#
# This script defines the following variables:
# - For each specified module XXX (system, window, graphics, network, audio, main):
#   - CSFML_XXX_LIBRARY_DEBUG:   the name of the debug library of the xxx module (set to CSFML_XXX_LIBRARY_RELEASE is no debug version is found)
#   - CSFML_XXX_LIBRARY_RELEASE: the name of the release library of the xxx module (set to CSFML_XXX_LIBRARY_DEBUG is no release version is found)
#   - CSFML_XXX_LIBRARY:         the name of the library to link to for the xxx module (includes both debug and optimized names if necessary)
#   - CSFML_XXX_FOUND:           true if either the debug or release library of the xxx module is found
#   - CSFML_XXX_DEPENDENCIES:    the list of libraries the module depends on, in case of static linking
# - CSFML_LIBRARIES:    the list of all libraries corresponding to the required modules
# - CSFML_FOUND:        true if all the required modules are found
# - CSFML_INCLUDE_DIR:  the path where CSFML headers are located (the directory containing the CSFML/Config.hpp file)
# - CSFML_DEPENDENCIES: the list of libraries CSFML depends on, in case of static linking
#
# example:
#   find_package(CSFML 2 COMPONENTS system window graphics audio REQUIRED)
#   include_directories(${CCSFML_INCLUDE_DIR})
#   add_executable(myapp ...)
#   target_link_libraries(myapp ${CSFML_LIBRARIES})

# define the CSFML_STATIC macro if static build was chosen
if(CSFML_STATIC_LIBRARIES)
    add_definitions(-DCSFML_STATIC)
endif()

# define the list of search paths for headers and libraries
set(FIND_CSFML_PATHS
    ${CSFML_ROOT}
    $ENV{CSFML_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)

# find the CSFML include directory
find_path(CSFML_INCLUDE_DIR CSFML/Config.hpp
          PATH_SUFFIXES include
          PATHS ${FIND_CSFML_PATHS})

# check the version number
set(CSFML_VERSION_OK TRUE)
if(CSFML_FIND_VERSION AND CSFML_INCLUDE_DIR)
    # extract the major and minor version numbers from CSFML/Config.hpp
    # we have to handle framework a little bit differently:
    if("${CSFML_INCLUDE_DIR}" MATCHES "CSFML.framework")
        set(CSFML_CONFIG_HPP_INPUT "${CSFML_INCLUDE_DIR}/Headers/Config.hpp")
    else()
        set(CSFML_CONFIG_HPP_INPUT "${CSFML_INCLUDE_DIR}/CSFML/Config.hpp")
    endif()
    FILE(READ "${CSFML_CONFIG_HPP_INPUT}" CSFML_CONFIG_HPP_CONTENTS)
    STRING(REGEX REPLACE ".*#define CSFML_VERSION_MAJOR ([0-9]+).*" "\\1" CSFML_VERSION_MAJOR "${CSFML_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define CSFML_VERSION_MINOR ([0-9]+).*" "\\1" CSFML_VERSION_MINOR "${CSFML_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define CSFML_VERSION_PATCH ([0-9]+).*" "\\1" CSFML_VERSION_PATCH "${CSFML_CONFIG_HPP_CONTENTS}")
    if (NOT "${CSFML_VERSION_PATCH}" MATCHES "^[0-9]+$")
        set(CSFML_VERSION_PATCH 0)
    endif()
    math(EXPR CSFML_REQUESTED_VERSION "${CSFML_FIND_VERSION_MAJOR} * 10000 + ${CSFML_FIND_VERSION_MINOR} * 100 + ${CSFML_FIND_VERSION_PATCH}")

    # if we could extract them, compare with the requested version number
    if (CSFML_VERSION_MAJOR)
        # transform version numbers to an integer
        math(EXPR CSFML_VERSION "${CSFML_VERSION_MAJOR} * 10000 + ${CSFML_VERSION_MINOR} * 100 + ${CSFML_VERSION_PATCH}")

        # compare them
        if(CSFML_VERSION LESS CSFML_REQUESTED_VERSION)
            set(CSFML_VERSION_OK FALSE)
        endif()
    else()
        # CSFML version is < 2.0
        if (CSFML_REQUESTED_VERSION GREATER 10900)
            set(CSFML_VERSION_OK FALSE)
            set(CSFML_VERSION_MAJOR 1)
            set(CSFML_VERSION_MINOR x)
            set(CSFML_VERSION_PATCH x)
        endif()
    endif()
endif()

# find the requested modules
set(CSFML_FOUND TRUE) # will be set to false if one of the required modules is not found
foreach(FIND_CSFML_COMPONENT ${CSFML_FIND_COMPONENTS})
    string(TOLOWER ${FIND_CSFML_COMPONENT} FIND_CSFML_COMPONENT_LOWER)
    string(TOUPPER ${FIND_CSFML_COMPONENT} FIND_CSFML_COMPONENT_UPPER)
    set(FIND_CSFML_COMPONENT_NAME sfml-${FIND_CSFML_COMPONENT_LOWER})

    # no suffix for sfml-main, it is always a static library
    if(FIND_CSFML_COMPONENT_LOWER STREQUAL "main")
        # release library
        find_library(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE
                     NAMES ${FIND_CSFML_COMPONENT_NAME}
                     PATH_SUFFIXES lib64 lib
                     PATHS ${FIND_CSFML_PATHS})

        # debug library
        find_library(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG
                     NAMES ${FIND_CSFML_COMPONENT_NAME}-d
                     PATH_SUFFIXES lib64 lib
                     PATHS ${FIND_CSFML_PATHS})
    else()
        # static release library
        find_library(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_RELEASE
                     NAMES ${FIND_CSFML_COMPONENT_NAME}-s
                     PATH_SUFFIXES lib64 lib
                     PATHS ${FIND_CSFML_PATHS})

        # static debug library
        find_library(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_DEBUG
                     NAMES ${FIND_CSFML_COMPONENT_NAME}-s-d
                     PATH_SUFFIXES lib64 lib
                     PATHS ${FIND_CSFML_PATHS})

        # dynamic release library
        find_library(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_RELEASE
                     NAMES ${FIND_CSFML_COMPONENT_NAME}
                     PATH_SUFFIXES lib64 lib
                     PATHS ${FIND_CSFML_PATHS})

        # dynamic debug library
        find_library(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_DEBUG
                     NAMES ${FIND_CSFML_COMPONENT_NAME}-d
                     PATH_SUFFIXES lib64 lib
                     PATHS ${FIND_CSFML_PATHS})

        # choose the entries that fit the requested link type
        if(CSFML_STATIC_LIBRARIES)
            if(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_RELEASE)
                set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_RELEASE})
            endif()
            if(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_DEBUG)
                set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_DEBUG})
            endif()
        else()
            if(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_RELEASE)
                set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_RELEASE})
            endif()
            if(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_DEBUG)
                set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_DEBUG})
            endif()
        endif()
    endif()

    if (CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG OR CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE)
        # library found
        set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_FOUND TRUE)

        # if both are found, set CSFML_XXX_LIBRARY to contain both
        if (CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG AND CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE)
            set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY debug     ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG}
                                                          optimized ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE})
        endif()

        # if only one debug/release variant is found, set the other to be equal to the found one
        if (CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG AND NOT CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE)
            # debug and not release
            set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG})
            set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY         ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG})
        endif()
        if (CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE AND NOT CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG)
            # release and not debug
            set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE})
            set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY       ${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE})
        endif()
    else()
        # library not found
        set(CSFML_FOUND FALSE)
        set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_FOUND FALSE)
        set(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY "")
        set(FIND_CSFML_MISSING "${FIND_CSFML_MISSING} CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY")
    endif()

    # mark as advanced
    MARK_AS_ADVANCED(CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY
                     CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_RELEASE
                     CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DEBUG
                     CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_RELEASE
                     CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_STATIC_DEBUG
                     CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_RELEASE
                     CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY_DYNAMIC_DEBUG)

    # add to the global list of libraries
    set(CSFML_LIBRARIES ${CSFML_LIBRARIES} "${CSFML_${FIND_CSFML_COMPONENT_UPPER}_LIBRARY}")
endforeach()

# in case of static linking, we must also define the list of all the dependencies of CSFML libraries
if(CSFML_STATIC_LIBRARIES)

    # detect the OS
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(FIND_CSFML_OS_WINDOWS 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(FIND_CSFML_OS_LINUX 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        set(FIND_CSFML_OS_FREEBSD 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(FIND_CSFML_OS_MACOSX 1)
    endif()

    # start with an empty list
    set(CSFML_DEPENDENCIES)
    set(FIND_CSFML_DEPENDENCIES_NOTFOUND)

    # macro that searches for a 3rd-party library
    macro(find_sfml_dependency output friendlyname)
        # No lookup in environment variables (PATH on Windows), as they may contain wrong library versions
        find_library(${output} NAMES ${ARGN} PATHS ${FIND_CSFML_PATHS} PATH_SUFFIXES lib NO_SYSTEM_ENVIRONMENT_PATH)
        if(${${output}} STREQUAL "${output}-NOTFOUND")
            unset(output)
            set(FIND_CSFML_DEPENDENCIES_NOTFOUND "${FIND_CSFML_DEPENDENCIES_NOTFOUND} ${friendlyname}")
        endif()
    endmacro()

    # sfml-system
    list(FIND CSFML_FIND_COMPONENTS "system" FIND_CSFML_SYSTEM_COMPONENT)
    if(NOT ${FIND_CSFML_SYSTEM_COMPONENT} EQUAL -1)

        # update the list -- these are only system libraries, no need to find them
        if(FIND_CSFML_OS_LINUX OR FIND_CSFML_OS_FREEBSD OR FIND_CSFML_OS_MACOSX)
            set(CSFML_SYSTEM_DEPENDENCIES "pthread")
        endif()
        if(FIND_CSFML_OS_LINUX)
            set(CSFML_SYSTEM_DEPENDENCIES ${CSFML_SYSTEM_DEPENDENCIES} "rt")
        endif()
        if(FIND_CSFML_OS_WINDOWS)
            set(CSFML_SYSTEM_DEPENDENCIES "winmm")
        endif()
        set(CSFML_DEPENDENCIES ${CSFML_SYSTEM_DEPENDENCIES} ${CSFML_DEPENDENCIES})
    endif()

    # sfml-network
    list(FIND CSFML_FIND_COMPONENTS "network" FIND_CSFML_NETWORK_COMPONENT)
    if(NOT ${FIND_CSFML_NETWORK_COMPONENT} EQUAL -1)

        # update the list -- these are only system libraries, no need to find them
        if(FIND_CSFML_OS_WINDOWS)
            set(CSFML_NETWORK_DEPENDENCIES "ws2_32")
        endif()
        set(CSFML_DEPENDENCIES ${CSFML_NETWORK_DEPENDENCIES} ${CSFML_DEPENDENCIES})
    endif()

    # sfml-window
    list(FIND CSFML_FIND_COMPONENTS "window" FIND_CSFML_WINDOW_COMPONENT)
    if(NOT ${FIND_CSFML_WINDOW_COMPONENT} EQUAL -1)

        # find libraries
        if(FIND_CSFML_OS_LINUX OR FIND_CSFML_OS_FREEBSD)
            find_sfml_dependency(X11_LIBRARY "X11" X11)
            find_sfml_dependency(XRANDR_LIBRARY "Xrandr" Xrandr)
        endif()

        if(FIND_CSFML_OS_LINUX)
            find_sfml_dependency(UDEV_LIBRARIES "UDev" udev libudev)
        endif()

        # update the list
        if(FIND_CSFML_OS_WINDOWS)
            set(CSFML_WINDOW_DEPENDENCIES ${CSFML_WINDOW_DEPENDENCIES} "opengl32" "winmm" "gdi32")
        elseif(FIND_CSFML_OS_LINUX)
            set(CSFML_WINDOW_DEPENDENCIES ${CSFML_WINDOW_DEPENDENCIES} "GL" ${X11_LIBRARY} ${XRANDR_LIBRARY} ${UDEV_LIBRARIES})
        elseif(FIND_CSFML_OS_FREEBSD)
            set(CSFML_WINDOW_DEPENDENCIES ${CSFML_WINDOW_DEPENDENCIES} "GL" ${X11_LIBRARY} ${XRANDR_LIBRARY} "usbhid")
        elseif(FIND_CSFML_OS_MACOSX)
            set(CSFML_WINDOW_DEPENDENCIES ${CSFML_WINDOW_DEPENDENCIES} "-framework OpenGL -framework Foundation -framework AppKit -framework IOKit -framework Carbon")
        endif()
        set(CSFML_DEPENDENCIES ${CSFML_WINDOW_DEPENDENCIES} ${CSFML_DEPENDENCIES})
    endif()

    # sfml-graphics
    list(FIND CSFML_FIND_COMPONENTS "graphics" FIND_CSFML_GRAPHICS_COMPONENT)
    if(NOT ${FIND_CSFML_GRAPHICS_COMPONENT} EQUAL -1)

        # find libraries
        find_sfml_dependency(FREETYPE_LIBRARY "FreeType" freetype)
        find_sfml_dependency(JPEG_LIBRARY "libjpeg" jpeg)

        # update the list
        set(CSFML_GRAPHICS_DEPENDENCIES ${FREETYPE_LIBRARY} ${JPEG_LIBRARY})
        set(CSFML_DEPENDENCIES ${CSFML_GRAPHICS_DEPENDENCIES} ${CSFML_DEPENDENCIES})
    endif()

    # sfml-audio
    list(FIND CSFML_FIND_COMPONENTS "audio" FIND_CSFML_AUDIO_COMPONENT)
    if(NOT ${FIND_CSFML_AUDIO_COMPONENT} EQUAL -1)

        # find libraries
        find_sfml_dependency(OPENAL_LIBRARY "OpenAL" openal openal32)
        find_sfml_dependency(OGG_LIBRARY "Ogg" ogg)
        find_sfml_dependency(VORBIS_LIBRARY "Vorbis" vorbis)
        find_sfml_dependency(VORBISFILE_LIBRARY "VorbisFile" vorbisfile)
        find_sfml_dependency(VORBISENC_LIBRARY "VorbisEnc" vorbisenc)
        find_sfml_dependency(FLAC_LIBRARY "FLAC" FLAC)

        # update the list
        set(CSFML_AUDIO_DEPENDENCIES ${OPENAL_LIBRARY} ${FLAC_LIBRARY} ${VORBISENC_LIBRARY} ${VORBISFILE_LIBRARY} ${VORBIS_LIBRARY} ${OGG_LIBRARY})
        set(CSFML_DEPENDENCIES ${CSFML_DEPENDENCIES} ${CSFML_AUDIO_DEPENDENCIES})
    endif()

endif()

# handle errors
if(NOT CSFML_VERSION_OK)
    # CSFML version not ok
    set(FIND_CSFML_ERROR "CSFML found but version too low (requested: ${CSFML_FIND_VERSION}, found: ${CSFML_VERSION_MAJOR}.${CSFML_VERSION_MINOR}.${CSFML_VERSION_PATCH})")
    set(CSFML_FOUND FALSE)
elseif(CSFML_STATIC_LIBRARIES AND FIND_CSFML_DEPENDENCIES_NOTFOUND)
    set(FIND_CSFML_ERROR "CSFML found but some of its dependencies are missing (${FIND_CSFML_DEPENDENCIES_NOTFOUND})")
    set(CSFML_FOUND FALSE)
elseif(NOT CSFML_FOUND)
    # include directory or library not found
    set(FIND_CSFML_ERROR "Could NOT find CSFML (missing: ${FIND_CSFML_MISSING})")
endif()
if (NOT CSFML_FOUND)
    if(CSFML_FIND_REQUIRED)
        # fatal error
        message(FATAL_ERROR ${FIND_CSFML_ERROR})
    elseif(NOT CSFML_FIND_QUIETLY)
        # error but continue
        message("${FIND_CSFML_ERROR}")
    endif()
endif()

# handle success
if(CSFML_FOUND AND NOT CSFML_FIND_QUIETLY)
    message(STATUS "Found CSFML ${CSFML_VERSION_MAJOR}.${CSFML_VERSION_MINOR}.${CSFML_VERSION_PATCH} in ${CSFML_INCLUDE_DIR}")
endif()
