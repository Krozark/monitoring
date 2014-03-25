set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

#ROOT files
set(ROOT_SRC
    ${SRCROOT}/Cpu.cpp
    ${SRCROOT}/Physical.cpp
    ${SRCROOT}/sys.cpp
    ${SRCROOT}/Virtual.cpp
)
set(ROOT_HEADER
    ${INCROOT}/Cpu.hpp
    ${INCROOT}/Physical.hpp
    ${INCROOT}/sys.hpp
    ${INCROOT}/Virtual.hpp
)
set(ROOT_FILES
    ${ROOT_HEADER}
    ${ROOT_SRC}
)

#FILES
set(FILES_HEADER
    ${ROOT_HEADER}
)
set(FILES_SRC
    ${ROOT_SRC}
)

#SHARED lib
add_library(${CMAKE_PROJECT_NAME} SHARED ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION lib
)


#static lib
add_library(${CMAKE_PROJECT_NAME}-static STATIC ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-static
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(${CMAKE_PROJECT_NAME}-static ${LIBS})
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-static
    DESTINATION lib
)

## EXAMPLES
if(BUILD_EXAMPLES)
    add_executable(${CMAKE_PROJECT_NAME}-test main.cpp ${FILES_HEADER} ${FILES_SRC})
	target_link_libraries(${CMAKE_PROJECT_NAME}-test ${LIBS})
    add_executable(${CMAKE_PROJECT_NAME}-info info.cpp ${FILES_HEADER} ${FILES_SRC})
	target_link_libraries(${CMAKE_PROJECT_NAME}-info ${LIBS})
endif()

#header
#INSTALL(FILES ${INCROOT}
#    DESTINATION include
#    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
#)

file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION include/${CMAKE_PROJECT_NAME} )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/${CMAKE_PROJECT_NAME} )


########################################################################
# Create uninstall target
########################################################################
CONFIGURE_FILE(
    "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake"
)
