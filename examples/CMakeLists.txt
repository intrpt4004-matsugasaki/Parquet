add_custom_target(examples)
add_dependencies(examples
	Error
	Memory
	String
	List

	AnyChar3-6-12
	StringNoneOf
	DeclVar
	SeqParse
	MPL
	mpltok
	mplprs

	CreateExecutable
)

add_executable(Error Base/Error.c)
target_link_libraries(Error
    Parquet
)

add_executable(Memory Base/Memory.c)
target_link_libraries(Memory
    Parquet
)

add_executable(String Base/String.c)
target_link_libraries(String
    Parquet
)

add_executable(List Base/List.c)
target_link_libraries(List
    Parquet
)

add_executable(AnyChar3-6-12 ParserCombinator/AnyChar3-6-12.c)
target_link_libraries(AnyChar3-6-12
    Parquet
)

add_executable(StringNoneOf ParserCombinator/StringNoneOf.c)
target_link_libraries(StringNoneOf
    Parquet
)

add_executable(DeclVar ParserCombinator/DeclVar.c)
target_link_libraries(DeclVar
    Parquet
)

add_executable(SeqParse ParserCombinator/SeqParse.c)
target_link_libraries(SeqParse
    Parquet
)

add_executable(MPL ParserCombinator/MPL.c)
target_link_libraries(MPL
    Parquet
)

add_executable(mpltok ParserCombinator/mpltok/mpltok.c ParserCombinator/mpltok/MPLLexer.c)
target_link_libraries(mpltok
    Parquet
)

add_executable(mplprs ParserCombinator/mplprs/mplprs.c ParserCombinator/mplprs/MPLParser.c ParserCombinator/mplprs/MPLLexer.c ParserCombinator/mplprs/Printer.c)
target_link_libraries(mplprs
    Parquet
)

add_executable(CreateExecutable ExecBinaryPreparer/CreateExecutable.c)
target_link_libraries(CreateExecutable
    Parquet
)
