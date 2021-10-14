add_custom_target(examples)
add_dependencies(examples
	Error
	Memory

	String
	List

	AnyChar3-6-12
	DeclVar

	MPL
	mpltok
	mplprs
	#mplc
)

add_executable(Error other/Error.c)
target_link_libraries(Error
    Scraper
)

add_executable(Memory other/Memory.c)
target_link_libraries(Memory
    Scraper
)

add_executable(String other/String.c)
target_link_libraries(String
    Scraper
)

add_executable(List other/List.c)
target_link_libraries(List
    Scraper
)

add_executable(AnyChar3-6-12 AnyChar3-6-12.c)
target_link_libraries(AnyChar3-6-12
    Scraper
)

add_executable(DeclVar DeclVar.c)
target_link_libraries(DeclVar
    Scraper
)

add_executable(MPL MPL.c)
target_link_libraries(MPL
    Scraper
)

add_executable(mpltok mpltok/mpltok.c mpltok/MPLLexer.c mpltok/Token.c)
target_link_libraries(mpltok
    Scraper
)

add_executable(mplprs mplprs/mplprs.c mplprs/MPLParser.c mplprs/Token.c)
target_link_libraries(mplprs
    Scraper
)

#add_executable(mplc mplc/mplc.c mplc/MPLParser.c mplc/Token.c)
#target_link_libraries(mplc
#    Scraper
#)

# debug
set(CMAKE_C_FLAGS "-g3 -O0")
