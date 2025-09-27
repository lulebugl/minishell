# Minishell

A small Unix-like shell written in C for the 42 curriculum. It supports command parsing into an AST, pipelines, logical operators, grouping with parentheses, word expansion (tilde, variables, wildcards), heredocs with variable expansion and the standard set of shell builtins.

![Minishell screenshot](https://raw.githubusercontent.com/lulebugl/lulebugl/main/.github/images/minishell.png)

## Overview

- Parses input into tokens and builds an AST supporting `|`, `&&`, `||`, `(`, `)`, and I/O redirections.
- Executes pipelines as a single unit; flushes the pipeline at logical operators.
- Expands words: tilde (`~`), environment variables (including `$?`), wildcard `*` (only in current directory), and handles quotes.
- Implements heredocs with variable expansion.
- Provides prompt details: path (with `~`), `SHLVL`, and Git branch.

## Requirements

- `make`
- `readline` development headers
  - macOS: `brew install readline`
  - Linux (Debian/Ubuntu): `sudo apt-get install libreadline-dev`

## Build and Run

```bash
# Standard build
make

# Debug build (ASan, extra debug flags)
make MODE=debug

# Rebuild
make re

# Clean objects / binary
make clean
make fclean

# Run
make run
or
./minishell
```

If macOS Homebrew is installed under `/opt/homebrew`, you may need to update the `READLINE_*` paths in `Makefile` or export the flags:
```bash
export LDFLAGS="-L/opt/homebrew/opt/readline/lib"
export CPPFLAGS="-I/opt/homebrew/opt/readline/include"
```

## Features

- **Parsing/AST**
  - Pipes `|`, logical AND `&&`, logical OR `||`, parentheses grouping `( … )`
  - I/O redirections: `<`, `>`, `>>`, heredoc `<<`
  - Syntax validation: balanced quotes and parentheses, redirection sanity checks
- **Execution**
  - Pipelines with proper `pipe(2)` and `fork(2)` orchestration
  - `PATH` lookup and absolute/relative execution
  - Correct exit codes (126 permission, 127 not found, 130 on SIGINT)
- **Expansion**
  - `~` expansion
  - `$VAR` and `$?` expansion (status)
  - Quote rules: single quotes disable expansion, double quotes allow it
  - `*` wildcard expansion in arguments
- **Heredoc**
  - Reads until delimiter; expands `$VAR` and `$?` within heredoc lines

## Custom Builtins

- **cd**: change directory
- **echo**: echo arguments (supports typical usage)
- **env**: print environment
- **exit**: exit shell with status
- **export**: set/update environment variables
- **pwd**: print working directory
- **unset**: remove environment variables

## Usage Examples

- **Simple command**
```bash
ls -la
```

- **Pipes**
```bash
cat file.txt | grep foo | wc -l
```

- **Redirections**
```bash
grep foo < in.txt > out.txt
echo "hello" >> log.txt
```

- **Heredoc with expansion**
```bash
cat << EOF
User: $USER
Status: $?
EOF
```

- **Logical operators**
```bash
make && ./minishell
false || echo "Recovered"
```

- **Grouping with parentheses**
```bash
( echo a && echo b ) || echo "group failed"
```

- **Quoting and expansion**
```bash
echo "$HOME"       # expands
echo '$HOME'       # literal
```

- **Wildcard expansion**
```bash
echo *.c
```

## Limitations and Notes

- Wildcards:
  - `*` in arguments is supported, but:
    - Wildcards in other directories (e.g., `src/*.c`) are not implemented.
    - Wildcards in redirection filenames are not implemented.
- Heredoc:
  - Always performs variable expansion in heredoc content (quoted delimiters to disable expansion are not supported).
- Job control (`&`, fg/bg), command substitution, and variable assignment syntax are out of scope.
- readline history sometimes breaks the ui but still works

## Acknowledgments

- Built as part of the 42 curriculum.

## Authors

- maxweert — [GitHub profile](https://github.com/mweerts)
- llebugle — [GitHub profile](https://github.com/llebugle)
