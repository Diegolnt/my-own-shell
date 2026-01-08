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



## DISCLAIMER:
1. This project was entirely made by hand. No AI was used to write or ask for solutions. All in order to learn everything
needed to become a better programmer.
2. My native language is Spanish, but this is programmed in English with no AI all made by myself. 


