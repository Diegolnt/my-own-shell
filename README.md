# My-Own-Shell.

---

Author: Diego Echeverría
Date: January 2026
Language: C (17) 
System: Unix/Linux

---

## Description

This program implements a basic Unix shell that allows the user to execute commands from the OS.
The Shell supports:

- **External Commands**: Basically any available program that's in the PATH of our system (ex: 'ls', 'cat', 'grep')
- **Internal Commands (Builtins)**: 'cd', 'exit', 'help'
- **Argument Parsing**: Capable of receiving spaces, tabs and multiple aruguments.

### ¿What is a Shell?

In simple terms a shell is an interpreter that communicates us with the Kernel of our OS.
It does the following:
1. Receives user input
2. Parses the input
3. Executes it
4. Displays results
5. Waits for next command/input

---

## Compilation and Execution

### Compilate the program

```bash
gcc main.c -o myshell -Wall
```

**Used flags**
- '-o myshell': Name of the resulting executable
- '-Wall': Allows warnings (good practice)

### Execute the Shell

```bash
./myshell
```

### Exit Shell

```bash
<>: exit
```

or simply press 'Ctrl + C'

---

## Code Arquitecture

```
┌─────────────────────────────────────────────┐
│              MAIN LOOP                      │
│  1. Read user line                          │
│  2. Parse Arguments                         │
│  3. Execute Command                         │
│  4. Free Memory                             │
│  5. Repeat                                  │
└─────────────────────────────────────────────┘
                     │
                     ▼
         ┌───────────────────────┐
         │  shell_execute()      │
         │  (Principal Router)   │
         └───────────────────────┘
                     │
        ┌────────────┴────────────┐
        ▼                         ▼
┌───────────────┐        ┌────────────────┐
│   Builtins    │        │    External    │
│  (cd, exit)   │        │ (ls, cat, etc) │
└───────────────┘        └────────────────┘
                                 │
                                 ▼
                         ┌───────────────┐
                         │ shell_launch()│
                         │ fork + execvp │
                         └───────────────┘
```

---

## Notes

These are some things to take note, that are not simple at first glance

**getline()**:
- If line == NULL and buffsize == 0, getline() asigns memory automatically
- Returns -1 at EOF or error
- The pointer line is modified by getline() to point to the asigned memory
- **Important**: The call needs to be freed (free(line)) later

**Difference with fgets()**:
- fgets requires a pre-asigned bufer size.

Ex:
```c
char buffer[1024];
fgets(buffer,1024,stdin);
```
**strtok()**:
- Statefull function, mantains an internal state. Remembers where it began and where it ended, so when called again with 'NULL' argument it changes the pointer of where it ended to where it began.
- Modifies original array.
- Why do we set tokens[position] to 'NULL'? 'Because execvp()' expects a NULL-terminated array.

**Explanation of `(*builtin_func[i])(args)`**:

This is an indirect function call via a pointer to a function.

Remember the declaration:
```c
int (*builtin_func[]) (char **) = { &shell_cd, &shell_exit, &shell_help };
```

Breaking down the call:
```c
builtin_func[i]          // 1. Get the function pointer at index 'i'
(*builtin_func[i])       // 2. Dereference the pointer (access the actual function)
(*builtin_func[i])(args) // 3. Call the function passing 'args' (which is char **)
```

Or how I view it:

```c
// If i = 0 (command "cd")

builtin_func[0]           // Equivalent to: &shell_cd  (Memory address)
(*builtin_func[0])        // Equivalent to: shell_cd   (The function itself)
(*builtin_func[0])(args)  // Equivalent to: shell_cd(args)
                          // Where args is of type char **
```

**WIFEXITED() and WIFSIGNALED()**:

These macros are used in `shell_launch()` to check how a child process terminated:

```c
while (!WIFEXITED(status) && !WIFSIGNALED(status));
```

- `WIFEXITED(status)`: Returns true if the child process terminated normally (via exit() or return)
- `WIFSIGNALED(status)`: Returns true if the child process was terminated by a signal (e.g., SIGKILL, SIGSEGV)

The parent process waits until one of these conditions is met, ensuring the child has fully finished.

**EXIT_FAILURE**:

This is a standard macro defined in `<stdlib.h>` with value 1, used to indicate abnormal program termination:

```c
exit(EXIT_FAILURE);  // Equivalent to exit(1)
```

We use it when `execvp()` fails, signaling to the parent process that something went wrong.


## DISCLAIMER:
1. This project was entirely made by hand. No AI was used to write or ask for solutions. All in order to learn everything
needed to become a better programmer.
2. My native language is Spanish, but this is programmed in English with no AI all made by myself.
