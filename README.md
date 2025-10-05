# LinXel

**LinXel** is a lightweight, command-line tool for performing basic linear algebra operations. LinXel makes matrix computations simple, fast, and visually appealing.

## Features

- Create and manipulate matrices and vectors  
- Perform operations like addition, subtraction, multiplication, and inversion  
- Calculate determinants and other fundamental linear algebra routines  
- OpenGL visualization of matrix operations  
- Easy-to-use CLI interface with argument parsing via Argtable  

## Tech Stack

- **Language:** C  
- **Build Tool:** Makefile  
- **Libraries:**  
  - [Argtable](https://www.argtable.org/) — CLI argument parsing  
  - [OpenGL](https://www.opengl.org/) —  visualization and gpu benchmarking  

## Installation (Linux Only)

Clone the repository:

```bash
git clone https://github.com/pixelatedseraph/linxel.git
cd linxel
make 
