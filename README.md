#msh &middot; [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/levensta/msh/blob/master/LICENSE)
--
msh – maxishell is a light reproduction of Bourne Shell (bash).

![msh-test](https://media.giphy.com/media/AId9i2zooNa9MTq3yK/giphy.gif)

##Features that has been implement
- History.
- Search and launch the right executable (based on the **PATH** variable or by usingrelative or absolute path).
- Builtins functions:
	- `cd` with only a relative or absolute path.
	- `pwd` with no options.
	- `echo` with `-n` option.
	- `export` with no options.
	- `unset` with no options.
	- `env` with no options.
	- `exit` with no options.
	- `history` with no options.
- Redirections:
	- `<` redirect input.
	- `>` redirect output.
	- `>>`redirect output with append mode.
- Pipes `|` the output of each command in the pipeline is connected via a pipe to theinput of the next command.
- Environment variables (**$** followed by characters) expand to their values.
- `$?` expands to the exit status of the most recently executed foreground pipeline.
- Signals work like in bash. When interactive:
	- `Ctrl + C` will print a new prompt on a newline.
	- `Ctrl + D` will exit the shell.
	- `Ctrl + \` will do nothing.
