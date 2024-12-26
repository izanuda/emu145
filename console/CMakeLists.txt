cmake_minimum_required(VERSION 3.16)

project(console LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Local header files here ONLY
SET(TARGET_H
	cascade.h
	chargemem.h
	cmcu13.h
	k145_com.h
)

# Local source files here
SET(TARGET_SRC
	cascade.cpp
	chargemem.cpp
	cmcu13.cpp
	k145_com.cpp
	main.cpp
)

add_executable(console ${TARGET_SRC} ${TARGET_H})

include(GNUInstallDirs)
install(TARGETS console
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
