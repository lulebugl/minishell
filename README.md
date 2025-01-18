# Minishell

## weird commands to tests
```
echo >| test.txt
echo > | test.txt
ls |
exit > test.txt
echo >< test.txt
```

## Notes and Learnings
(Add your notes and key learnings here as you progress)

## Resources to Add
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
https://github.com/Swoorup/mysh?tab=readme-ov-file
https://github.com/mli42/at42minishell

### Project Structure
```
minishell/
├── src/
│   ├── main.c
│   ├── parsing/
│   ├─── io.c
│   ├── execution/
│   ├── builtins/
│   └── utils/
├── include/
│   └── minishell.h
├── libft/
├── Makefile
└── README.md
```

### Basic Shell Operations
- [ ] Display prompt for new commands
- [ ] Working command history
- [ ] Execute commands from PATH or absolute/relative paths
- [ ] Handle single quotes (') - prevent metacharacter interpretation
- [ ] Handle double quotes (") - prevent metacharacter interpretation except for $
- [ ] Signal handling (ctrl-C, ctrl-D, ctrl-\)

### Built-in Commands
- [ ] echo (with -n option)
- [ ] cd (with relative/absolute paths)
- [ ] pwd (no options)
- [ ] export (no options)
- [ ] unset (no options)
- [ ] env (no options/arguments)
- [ ] exit (no options)

### Redirections
- [ ] < (input redirection)
- [ ] > (output redirection)
- [ ] << (heredoc)
- [ ] >> (append output)

### Advanced Features
- [ ] Pipes (|)
- [ ] Environment variables ($VAR)
- [ ] Exit status ($?)

### Error Handling
- [ ] Handle syntax errors
- [ ] Handle command not found
- [ ] Handle permission errors

## Resources

### Key Functions to Study
- readline: Command line input

