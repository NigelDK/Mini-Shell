# minishell
Validated on 13-05-2021.


The objective of this project is to create a simple shell.

- With the Makefile you will compile the program called minishell.
- Our minishell has:
  * command history
  * builtin commands (no options): echo (with -n), cd, pwd, export, unset, env, exit
  * ’ and " inhibit interpretation of a sequence of characters in accordance to the real shell
  * redirections <, >, <<
  * pipes
  * command seperator ;
  * envorinment variables
  * $?
  * signals: ctrl-C, ctrl-D, ctrl-\
  * single line commands only
