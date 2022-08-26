
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was sentry-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(SENTRY_BACKEND crashpad)
set(SENTRY_TRANSPORT curl)

if(SENTRY_BACKEND STREQUAL "crashpad")
	if(OFF)
		find_package(crashpad REQUIRED)
	else()
		include("${CMAKE_CURRENT_LIST_DIR}/sentry_crashpad-targets.cmake")
	endif()
endif()

include("${CMAKE_CURRENT_LIST_DIR}/sentry-targets.cmake")

if(SENTRY_TRANSPORT STREQUAL "curl" AND NOT ON)
	find_package(CURL REQUIRED)
	set_property(TARGET sentry::sentry APPEND
		PROPERTY INTERFACE_LINK_LIBRARIES ${CURL_LIBRARIES})
endif()
