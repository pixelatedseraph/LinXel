# LinXel

**LinXel** is a lightweight, command-line tool for performing basic linear algebra operations. LinXel makes matrix computations simple, fast, and visually appealing.

## Features

- Create and manipulate matrices and vectors  
- Perform operations like addition, subtraction, multiplication, and inversion  
- Calculate determinants and other fundamental linear algebra routines  
- OpenGL visualization of matrix operations  
- Easy-to-use CLI interface with argument parsing via Argtable  

## Tech Stack

- **Language:** C & C++
- **Build Tool:** Makefile, CMAKE  
- **Libraries:**  
  - [Argtable](https://www.argtable.org/) — CLI argument parsing  
  - [SYCL](https://www.khronos.org/sycl/) — gpu benchmarking  

## Installation (Linux)

Clone the repository:

```bash
git clone https://github.com/pixelatedseraph/linxel.git
cd linxel
make run
```
## To use
```bash
./linxel --help
Uses :
 [-hp] [-g <m * n>]... [-s <idx>]... [-o <op>] [-r <rep>]

Options:
  -g, --generate=<m * n>    generate upto 5 matrices of any size by comma-separated list (eg 2x2,3x3,4x4) 
  -s, --select=<idx>        select from the list of matrices by comma-separated indicies (eg 1,2,3) 
  -o, --operate=<op>        choose operation: biops(add,sub,product,hadamard,elemwise_div,matrix_equal) uniops(trans,det,inv,spr,trace,norm,rank,power,cond) 
  -h, --help                Lists out all flags available 
  -p, --print               prints all the generated matrices
  -r, --repeat=<rep>        repeats the operation (1-100000) 
```
## Example
```bash
./linxel -g 2x3,3x3 -s 1,2 -o product
First Matrix  
6.00 10.00 6.00 
2.00 1.00 4.00 
---------------------------------------------
Second Matrix 
0.00 6.00 3.00 
1.00 8.00 7.00 
5.00 3.00 7.00 
---------------------------------------------
The resultant matrix by product: 
40.00 134.00 130.00 
21.00 32.00 41.00 
```
More features coming soon...
