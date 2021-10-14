# Scraper
Parser Combinator Library in C

## build
```sh
$ git clone https://github.com/rot-E/Scraper.git
$ cd Scraper
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
```c
#include <Scraper.h>
```
See [`examples/mpltok/*`](https://github.com/rot-E/Scraper/tree/main/examples/mpltok)

# License
&emsp;[`AGPLv3`](https://www.gnu.org/licenses/agpl-3.0.html)
