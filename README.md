
# bobcat-cli

A lightweight command-line tool that mimics the basic functionality of `cat`, designed for efficient file streaming. `bobcat-cli` processes multiple files and standard input, printing their contents sequentially to the standard output. It’s built with performance and simplicity in mind, making it memory-efficient and fast.

### Key Features:
- Processes files in the order provided in the command line.
- Handles standard input when no file is specified or when `-` is used.
- Efficient memory usage with a maximum of 1MB allocated at any time.
- Supports seamless file input and output using low-level Linux system calls (`read` and `write`).
- Provides error messages for files that cannot be opened or read.

## Installation

### Prerequisites

You need a Linux system with a C compiler (e.g., GCC or Clang) and `make` installed to compile the program.

### Steps to Build:

1. Clone this repository:
   ```bash
   git clone git@github.com:vaishi01/bobcat-cli.git
   cd bobcat-cli
   ```

2. Compile the program:
   ```bash
   make
   ```

This will produce the `bobcat` executable.

### Formatting Code

You can format the code using `clang-format` by running:
```bash
make format
```

## Usage

The `bobcat-lite` command is invoked with zero or more file operands. The program reads the specified files sequentially and outputs their content to the standard output.

### Syntax:
```bash
./bobcat [file1 file2 ...]
```

- If no files are specified or if `-` is provided as a file operand, it reads from the standard input.

### Examples:

1. Print the contents of a single file:
   ```bash
   ./bobcat file1.txt
   ```

2. Print the contents of multiple files:
   ```bash
   ./bobcat file1.txt file2.txt
   ```

3. Read from standard input and print:
   ```bash
   ./bobcat -
   ```

4. Print the contents of multiple files, alternating with input from standard input:
   ```bash
   ./bobcat file1.txt - file2.txt
   ```

   In this example, `bobcat` will print the contents of `file1.txt`, read from standard input until EOF (`Ctrl+D`), then print `file2.txt`.

## Functionality

- **Efficient I/O:** `bobcat-lite` uses the low-level `read(2)` and `write(2)` system calls to handle file input/output. This makes it lightweight and fast for handling large files.
  
- **Memory Efficiency:** The tool uses buffered file input/output with a maximum buffer size of 1MB, ensuring it remains space-efficient even with large inputs.

- **Error Handling:** If an invalid file is passed, `bobcat-lite` will continue processing the remaining files and return a non-zero exit status to indicate an error.

## Error Handling

- If a file does not exist or cannot be read, `bobcat-lite` will print an error message to `stderr` in the format:
  ```bash
  bobcat: <filename>: No such file or directory
  ```

- After encountering an error, the tool will continue to process the remaining files and will exit with a status > 0.


## License

This project is licensed under the MIT License.
