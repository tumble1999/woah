#This file is created by Tumble1999 (https://github.com/tumble1999)


#APTPKG_INCLUDE_DIR
#APTPKG_LIBRARY

if(UNIX)
	find_path(APTPKG_INCLUDE_DIR
	NAMES apt-pkg/dpkgpm.h
	PATH /usr/include
	)
	find_library(APTPKG_LIBRARY
	NAMES libapt-pkg.so
	PATH /usr/lib
	)
endif()


if(DEFINED APTPKG_INCLUDE_DIR)
	if(DEFINED APTPKG_LIBRARY)
		set(APTPKG_FOUND TRUE)
	else()
		set(APTPKG_FOUND FALSE)
	endif()
else()
	set(APTPKG_FOUND FALSE)
endif()