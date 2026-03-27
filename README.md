# 🐚 Minishell: As beautiful as a shell

> *“A mini-shell project from the 42 cursus. Writing a shell is a rite of passage: it teaches you how processes work, how file descriptors are managed, and how the terminal interacts with the kernel.”*

---

## 🎯 About The Project

**Minishell** is a project in the 42 curriculum designed to recreate a simplified version of `bash`. At its core, a shell is just a command-line interpreter: it reads input from the user, parses it, finds the corresponding executables, and runs them while managing system environment variables, signals, and open file descriptors.

By building Minishell, we dived deep into Unix architecture, specifically mastering:
- **Process creation and synchronization** (`fork`, `execve`, `waitpid`).
- **Inter-Process Communication (IPC)** via `pipe`.
- **File redirection** and managing File Descriptors (FDs).
- **Abstract Syntax Trees (AST) / Tokenization** to parse user input robustly.
- **Signal handling** mimicking standard `bash` behavior.

---

## ✨ Features

Our Minishell aims to clone standard Bash behavior as accurately as possible. The primary implemented features include:

### 🔄 Execution & Navigation
- Prompts the user with a custom read-line interactive shell.
- Finds and executes system binaries using the `$PATH` variable or absolute/relative paths.
- Proper exit status codes representation (`$?`).

### 🛠 Built-in Commands
Implements the core built-in commands natively inside our process:
- `echo` (with `-n` option).
- `cd` (with relative/absolute paths).
- `pwd` (prints current working directory).
- `export` (adds/updates environment variables).
- `unset` (removes environment variables).
- `env` (prints the environment).
- `exit` (exits the shell with a specific status code).

### 🔀 Pipes and Redirections
- Standard pipes (`|`) allowing the output of one command to chain as the input to the next.
- Input redirection (`<`).
- Output redirection (`>`) truncating the file.
- Append redirection (`>>`).
- Here-documents (`<<`) triggering an interactive prompt for multiline input using a specific delimiter.

### 📡 Variables & Signals
- Environment variables expansion (e.g., `echo $USER` or `$?`).
- Proper handling of single quotes (`'`) and double quotes (`"`).
- Global signal handling (intercepting `ctrl-C`, `ctrl-D`, and `ctrl-\`).

---

## 🚀 Installation & Usage

### Prerequisites
- Needs `gcc` or `cc` and `make`.
- The `readline` library (usually pre-installed on Linux; requires `brew install readline` on macOS).

### Build

Clone the repository and compile the project using the provided `Makefile`.

```bash
git clone https://github.com/BadrELG/Minihell.git
cd Minihell
make
```

### Run
Launch the executable to start the prompt.

```bash
./minishell
```
From here, you are inside your Custom Shell! 

```bash
minishell> ls -la | grep "src" > output.txt
minishell> cat output.txt
minishell> echo "Hello 42!" >> output.txt
minishell> exit
```

---

## 🏗️ Architecture

1. **Lexer & Tokenizer:** Reads raw input (using `readline`) and slices it into comprehensive tokens (WORD, PIPE, REDIRECTION, etc.), identifying quotes and syntax logic.
2. **Expander:** Runs through the tokens replacing environment variables (e.g., `$USER` becomes `badr`).
3. **Parser:** Validates grammar rules and converts the tokens into an actionable execution structure / command nodes (`t_cmd`).
4. **Executor:** The brain of the shell. Sets up the pipelines (`pipe()`), replicates standard FDs (`dup2()`), forks the children (`fork()`), and executes (`execve()`), then waits for results to set exit records.

---

## 👨‍💻 Author

- Badr ([@BadrELG](https://github.com/BadrELG))

---
*If you find this repo useful or interesting, feel free to drop a ⭐!*