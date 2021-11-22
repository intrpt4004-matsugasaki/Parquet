option(Parquet_BUILD_SHARED_LIBS "build Parquet as a shared library" OFF)

if (PARQUET_BUILD_SHARED_LIBS)
    add_library(Parquet SHARED)
else()
    add_library(Parquet STATIC)
endif()

target_sources(Parquet
    PRIVATE

    Parquet/Base/Error.c
    Parquet/Base/Memory.c
    Parquet/Base/String.c
    Parquet/Base/List.c

    Parquet/ParserCombinator/Parser.c
    Parquet/ParserCombinator/Basis.c
	Parquet/ParserCombinator/Combinator.c
	Parquet/ParserCombinator/Parsers.c
    Parquet/ParserCombinator/Invoker.c

    Parquet/ExecutableBinaryPreparer.c
)

target_include_directories(Parquet
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

include(GNUInstallDirs)

# install lib
install(TARGETS Parquet
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
