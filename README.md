# randwrite
* Use `xoshiro256++` PRNG to generate random numbers in C with a header-only library.
* Write random bytes to a binary file using the CLI tool.

## Build
* Build with command below or run `rwcli.bat`
```sh
gcc rwcli.c -o rwcli.exe -O3 -s
```
## Usage
### CLI
* To write 10 random 64 bit numbers (80 random bytes) to specified path `myfileee`, run:
```sh
./rwcli 10 -o myfileee
```
### Header-Only Library
```c
#define RANDWRITE_IMPLEMENTATION
#include "randwrite.h"

#include <stdio.h>
#include <time.h>

int main(void)
{
    xo_state rng = {0};
    srand_xo(&rng, time(0));

    printf("Random number: %lld \n", (int64_t)rand_xo(&rng));

    return 0;
}
```
## Details
* The CLI tool currently doesn't write "numbers" to a file, it writes randomized bytes directly. This allows easy reinterpration of the same random data e.g. as u64's or as i64's as u32's.
* Xoshiro256++ PRNG's state is initialized using `splitmax64` PRNG to satisfy xoshiro256++ no-zero's requirement. The splitmax64 PRNG's state itself is currently only seeded with `time(0)`.
* When the CLI receives a command to e.g. write `100` random numbers to a file, it internally malloc's `100 * 8` bytes to create a buffer that can hold the requested amount of 64 bit numbers.
# TODO
* Add "number" writing instead of byte writing, specified via flag.
    * Add float writing support. (culling invalid floats?)
* Initialize splitmax64 with a stronger seed.
