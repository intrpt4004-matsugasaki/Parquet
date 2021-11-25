# Parquet
Compiler Creation Support Library in C
- Basic Types (String, List) : ( [header](https://github.com/rot-E/Parquet/tree/main/include/Parquet/Base/) [source](https://github.com/rot-E/Parquet/tree/main/lib/Parquet/Base/) [examples](https://github.com/rot-E/Parquet/tree/main/examples/Base/) )
- Parser Combinator : ( [header](https://github.com/rot-E/Parquet/tree/main/include/Parquet/ParserCombinator/) [source](https://github.com/rot-E/Parquet/tree/main/lib/Parquet/ParserCombinator/)  [examples](https://github.com/rot-E/Parquet/tree/main/examples/ParserCombinator/) )
- AST
- Assembly Code Generation (x64 Linux GNU Assembler, COMET-II CASL-II)
- Executable Binary Preparation : ( [header](https://github.com/rot-E/Parquet/tree/main/include/Parquet/ExecBinPreparer.h) [source](https://github.com/rot-E/Parquet/tree/main/lib/Parquet/ExecBinPreparer.c)  [examples](https://github.com/rot-E/Parquet/tree/main/examples/ExecBinPreparer/) )
  - requires: **`as` `ld`**

## build
requires: **`git` `cmake` `make` `gcc`**
<br><br>

```sh
$ git clone https://github.com/rot-E/Parquet.git
$ cd Parquet
$ mkdir build && cd build
$ cmake ..
$ make -j
```

## install
```sh
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/.local
$ make install -j
```

## build examples
```sh
$ make examples -j
$ examples/mpltok ../examples/ParserCombinator/mpltok/sum_err.mpl
$ examples/mpltok ../examples/ParserCombinator/mpltok/sum.mpl
```

# Usage
Tokenise: [`examples/ParserCombinator/mpltok/*`](https://github.com/rot-E/Parquet/tree/main/examples/ParserCombinator/mpltok)

Parse: [`examples/ParserCombinator/mplprs/*`](https://github.com/rot-E/Parquet/tree/main/examples/ParserCombinator/mplprs)

# License
&emsp;[`AGPLv3`](https://www.gnu.org/licenses/agpl-3.0.html)
