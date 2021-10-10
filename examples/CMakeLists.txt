add_custom_target(examples)
add_dependencies(examples
	Error
	Memory

	String

	AnyChar3

	#Identifier
)

add_executable(Error Error.c)
target_link_libraries(Error
    Scraper
)

add_executable(Memory Memory.c)
target_link_libraries(Memory
    Scraper
)

add_executable(String String.c)
target_link_libraries(String
    Scraper
)

add_executable(AnyChar3 AnyChar3.c)
target_link_libraries(AnyChar3
    Scraper
)

add_executable(Identifier Identifier.c)
target_link_libraries(Identifier
    Scraper
)
