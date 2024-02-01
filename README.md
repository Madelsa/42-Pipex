# Pipex

The `Pipex` project is a 42 School project that involves the creation of a simple shell program capable of simulating the functionality of the shell by using a series of processes and pipes. The project aims to reinforce the understanding of Unix processes, pipes, file descriptors, and command execution.

## Table of Contents

- [Description](#description)
- [Examples](#examples)
- [Usage](#usage)

## Description

The `Pipex` project requires students to create a program that mimics the behavior of the shell by executing two commands and redirecting the output of the first command to the input of the second command. The project introduces concepts such as processes, pipes, and file descriptors.

## Examples

Here is an example demonstrating the usage of `pipex`:

  ```bash
  ./pipex infile "ls -l" "grep pipex" outfile
  ```
  `For Bonus:`
  ```bash
  ./pipex_bonus file1 "ls -l" "grep pipex" "wc -l" file2
  ```
  `OR:`
  ```bash
  ./pipex_bonus here_doc stop cat  "wc -l"  file2
  ```   

## Usage

1. Clone the repository:

   ```bash
   https://github.com/Madelsa/42-Pipex.git
   ```
   
2. Change into the project directory:

   ```bash
   cd 42-pipex
   ```

3. Compile the program:

   ```bash
   make
   ```
   `For Bonus:`
   ```bash
   make bonus
   ```

4. Now you can run `Pipex` as shown in [Examples](#examples)
