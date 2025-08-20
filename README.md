<p align="center">
   <img src="https://github.com/user-attachments/assets/7d564981-cb81-43e7-819a-25ffcfc5bd72" width="40%" height="40%"/>
</p>

# 🐚 C - Simple Shell Project

##### TOP


## 📘 Project Description
This project is a custom implementation of a UNIX shell, developed as part of a low-level programming curriculum. The shell replicates basic behavior of `/bin/sh`, supporting command execution, environment management, and process control. It is designed to deepen understanding of system calls, process creation, and shell architecture.


## 📑 Table of Contents

- [Learning Objectives](#-learning-objectives)
- [Requirements](#-requirements)
- [Allowed Functions and System Calls](#-allowed-functions-and-system-calls)
- [Features](#-features)
- [Compilation](#️-compilation)
- [Installation](#-installation)
- [Memory Leak](#-memory-leak)
- [Recommended Development Process](#-recommended-development-process)
- [Flowchart](#-flowchart)
- [Code Snippet](#-code-snippet)
- [Demo](#-demo)
- [Authors](#-authors)
- [License](#-license)

## 🎯 [Learning Objectives](#-learning-objectives)
By the end of this project, you should be able to explain:
- Who designed the original UNIX operating system
- Who wrote the first UNIX shell
- Who invented the B programming language (predecessor to C)
- Who Ken Thompson is
- How a shell works
- What a `pid` and `ppid` are
- How to manipulate the current process's environment
- The difference between a function and a system call
- How to create processes
- The three prototypes of `main`
- How the shell uses `PATH` to locate programs
- How to execute another program using `execve`
- How to suspend a process until a child terminates
- What EOF (end-of-file) means

## 🛠 [Requirements](#-requirements)
- Allowed editors: `vi`, `vim`, `emacs`
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)

[⬆](https://github.com/loicleguen/holbertonschool-simple_shell/blob/Loic/README.md#top)

## ✅ [Allowed Functions and System Calls](#-allowed-functions-and-system-calls)

All functions from `string.h` are permitted.

Additional allowed system calls and functions:
- `access` (man 2 access)
- `chdir`  (man 2 chdir)
- `close`  (man 2 close)
- `closedir`  (man 3 closedir)
- `execve` execve (man 2 execve)
- `exit`  (man 3 exit)
- `_exit`  (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork`  (man 2 fork)
- `free`  (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill`  (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir`  (man 3 opendir)
- `perror` (man 3 perror)
- `printf`  (man 3 printf)
- `fprintf` (man 3 fprintf)
- `vfprintf`  (man 3 vfprintf)
- `sprintf` (man 3 sprintf)
- `putchar` (man 3 putchar)
- `read`  (man 2 read)
- `readdir`  (man 3 readdir)
- `signal`  (man 2 signal)
- `stat`  (__xstat) (man 2 stat)
- `lstat`  (__lxstat) (man 2 lstat)
- `fstat`  (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait`  (man 2 wait)
- `waitpid`  (man 2 waitpid)
- `wait3`  (man 2 wait3)
- `wait4` (man 2 wait4)
- `write`  (man 2 write)

---

## 🚀 [Features](#-features)

- **Interactive and non-interactive shell modes**
  The shell supports both real-time user input and piped/scripted command execution.

- **Command parsing and execution**
  User input is tokenized and interpreted to execute valid commands.

- **Environment variable access**
  The shell can read and use environment variables such as `PATH`.

- **Built-in commands**
  - `exit`: Terminates the shell session
  - `env`: Displays the current environment variables

- **Error handling with custom program name**
  Errors are displayed with the shell’s executable name (`argv[0]`) for clarity.

- **PATH resolution for external commands**
  Commands are located using the system’s `PATH` variable, allowing execution of programs without specifying full paths.

[⬆](https://github.com/loicleguen/holbertonschool-simple_shell/blob/Loic/README.md#top)

## ⚙️ [Compilation](#️-compilation)

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
```

## 📥 [Installation](#-installation)

### 1. Clone the repository

Clone the repository by running the following command:

```bash
git clone https://github.com/loicleguen/holbertonschool-simple_shell.git
cd your-repo-name
```
Replace `YourUsername/your-repo-name` with the actual path to this repository.

### 2. Execute the man page

We provide a script to execute the custom man page fo our Simple SHell.

Run the following command:

```bash
man ./man_1__simple_shell.1
```

[⬆](https://github.com/loicleguen/holbertonschool-simple_shell/blob/Loic/README.md#top)

## 🚿 [Memory Leak](#-memory-leak)

Check the memory leak with the following command:

```bash
valgrind --leak-check=full ./shell
```

Output:

```bash
==4192== LEAK SUMMARY:
==4192==    definitely lost: 0 bytes in 0 blocks
==4192==    indirectly lost: 0 bytes in 0 blocks
==4192==      possibly lost: 0 bytes in 0 blocks
==4192==    still reachable: 1,144 bytes in 2 blocks
==4192==         suppressed: 0 bytes in 0 blocks
==4192== Reachable blocks (those to which a pointer was found) are not shown.
==4192== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==4192==
==4192== For lists of detected and suppressed errors, rerun with: -s
==4192== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


## 🔁 [Recommended Development Process](#-recommended-development-process)

1. **Implement command parser**
   Tokenize user input to identify commands and arguments.

2. **Add execution logic using `fork` and `execve`**
   Create child processes to execute commands using system calls.

3. **Handle environment and PATH resolution**
   Use environment variables to locate executable files.

4. **Add built-in commands**
   Implement internal commands like `exit` and `env`.

5. **Test both interactive and non-interactive modes**
   Validate shell behavior with direct input and piped/scripted commands.

6. **Optimize and refactor**
   Improve code readability, modularity, and performance.

7. **Ensure Betty style compliance**
   Follow the Betty coding style for consistency and readability.

[⬆](https://github.com/loicleguen/holbertonschool-simple_shell/blob/Loic/README.md#top)

## 📊 [Flowchart](#-flowchart)

<div align="center">

<img src="https://github.com/loicleguen/holbertonschool-simple_shell/blob/Loic/Images/Flowchart-simple-shell.drawio%20(1).png"/>

</div>

## 💻 [Code Snippet](#-code-snippet)
## ⏯ [Demo](#-demo)

https://github.com/user-attachments/assets/49b0a129-14ef-436f-afed-5e70c8d37dc1


[⬆](https://github.com/loicleguen/holbertonschool-simple_shell/blob/Loic/README.md#top)


## 👥 [Authors](#-authors)

<div align="center">

| Author | Role | GitHub | Email |
|--------|------|--------|-------|
| **Loïc Le Guen** | Lead Developer | [@loicleguen](https://github.com/loicleguen) | 11510@holbertonstudents.com |
| **Florian Hadjar** | Co-Developer | [@Boubouche1709](https://github.com/Boubouche1709) | 10482@holbertonstudents.com |
| **Guillaume Watelet** | Co-Develeper | [@Lagui117](https://github.com/Lagui117) | 10565@holbertonstudents.com |

</div>

## 📝 [License](#-license)

This project is part of the curriculum at Holberton School and is intended for educational purposes only.
