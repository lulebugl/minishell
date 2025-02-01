# Minishell

## TODOS
- ask what it termios and how it is useful 
```
tcgetattr(0, &term);
term.c_lflag &= ~ECHOCTL;
tcsetattr(0, TCSANOW, &term);
```
- fix heredoc before cmd and redirections before cmd

## Notes and Learnings
(Add your notes and key learnings here as you progress)

## Resources to Add
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
https://github.com/Swoorup/mysh?tab=readme-ov-file


