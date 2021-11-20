# Parquet
Compiler Creation Support Library in C
- Basic Types (String, List): [*.h](https://github.com/rot-E/Parquet/tree/main/include/Parquet/Base/) [*.c](https://github.com/rot-E/Parquet/tree/main/lib/Parquet/Base/)
- Parser Combinator: [*.h](https://github.com/rot-E/Parquet/tree/main/include/Parquet/ParserCombinator/) [*.c](https://github.com/rot-E/Parquet/tree/main/lib/Parquet/ParserCombinator/)
- AST
- Assembly code Generation
- Executable binary Preparation

## build
requires: **`git` `cmake` `make` `gcc` `as` `ld`**
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
$ examples/mpltok ../examples/mpltok/sum_err.mpl
$ examples/mpltok ../examples/mpltok/sum.mpl
```

# Usage
Tokenise: [`examples/mpltok/*`](https://github.com/rot-E/Parquet/tree/main/examples/mpltok)

Parse: [`examples/mplprs/*`](https://github.com/rot-E/Parquet/tree/main/examples/mplprs)

# License
&emsp;[`AGPLv3`](https://www.gnu.org/licenses/agpl-3.0.html)
