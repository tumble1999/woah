cmake_minimum_required(VERSION 3.18)
project(woah VERSION 0.0.0)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/dep")



execute_process (
    COMMAND bash -c "git log --oneline --all|wc -l|tr '\n' ' '"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE REVISION
)
add_compile_definitions(WOAH_VERSION="${CMAKE_PROJECT_VERSION}.${REVISION}")

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "apt, dpkg, apt-file")
set(CPACK_PACKAGE_CONTACT tumble1999)
set(CPACK_PACKAGE_DESCRIPTION "yay inspired wrapper for apt")

add_subdirectory(dep)
add_subdirectory(src)
