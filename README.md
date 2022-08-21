# Parquet
[![Build](https://github.com/intrpt4004-matsugasaki/Parquet/actions/workflows/build.yml/badge.svg)](https://github.com/intrpt4004-matsugasaki/Parquet/actions/workflows/build.yml)
[![](https://img.shields.io/badge/license-AGPLv3-blue?style=flat-square&logo=gnu)](LICENSE)

Compiler Creation Support Library in C (C23 / GNU extension)
- Basic Types (String, List) : ( [header](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/include/Parquet/Base/) [source](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/lib/Parquet/Base/) [examples](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/examples/Base/) )
- PEG Parser Combinator : ( [header](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/include/Parquet/ParserCombinator/) [source](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/lib/Parquet/ParserCombinator/) [examples](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/examples/ParserCombinator/) )
- AST
- Assembly Code Generation (x64 Linux GNU Assembler, COMET-II CASL-II)
- Executable Binary Preparation : ( [header](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/include/Parquet/ExecBinaryPreparer.h) [source](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/lib/Parquet/ExecBinaryPreparer.c) [examples](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/examples/ExecBinaryPreparer/) )&emsp;
  - dependencies: **`Binutils`**

# Build
dependencies: **`Git` `CMake` `Make` `GCC (GCC-11)`**
<br><br>

```sh
$ git clone https://github.com/intrpt4004-matsugasaki/Parquet.git
$ cd Parquet
$ mkdir build && cd build
$ cmake ..
$ make -j
```

## build examples & run
[![Build-examples](https://github.com/intrpt4004-matsugasaki/Parquet/actions/workflows/build-examples.yml/badge.svg)](https://github.com/intrpt4004-matsugasaki/Parquet/actions/workflows/build-examples.yml)
```sh
$ make examples -j
$ examples/mpltok ../examples/ParserCombinator/mpltok/sum_err.mpl
$ examples/mplprs ../examples/ParserCombinator/mplprs/sum.mpl
```

# Install
```sh
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/.local
$ make install -j
```

# Usage
Tokeniser: [`examples/ParserCombinator/mpltok/*`](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/examples/ParserCombinator/mpltok)

Parser: [`examples/ParserCombinator/mplprs/*`](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/examples/ParserCombinator/mplprs)

Semantic Analyser: [`examples/ParserCombinator/mplsema/*`](https://github.com/intrpt4004-matsugasaki/Parquet/tree/main/examples/ParserCombinator/mplsema) [work-in-progress]

Compiler:
  - [`examples/ParserCombinator/mplc/*`]() [not-yet-started]
  - [Sedna](https://github.com/intrpt4004-matsugasaki/Sedna) [work-in-progress]
  - [Eris](https://github.com/intrpt4004-matsugasaki/Eris) [not-yet-started]

# License
[![](https://img.shields.io/badge/license-AGPLv3-blue?style=for-the-badge&logo=gnu)](LICENSE)

&emsp;[`AGPLv3`](LICENSE)
