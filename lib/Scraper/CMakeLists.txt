option(SCRAPER_BUILD_SHARED_LIBS "build Scraper as a shared library" OFF)

if (SCRAPER_BUILD_SHARED_LIBS)
    add_library(Scraper SHARED)
else()
    add_library(Scraper STATIC)
endif()

target_sources(Scraper
    PRIVATE

	Error.c
	Memory.c

	String.c
    List.c

    Basis.c
	Combinator.c
	Parser.c
    Invoker.c
)

target_include_directories(Scraper
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

include(GNUInstallDirs)

# install lib
install(TARGETS Scraper
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# install *.h
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# debug
set(CMAKE_C_FLAGS "-g3 -O0")
