#include "sshell.h"

/**
 * help_cd - Shows info of the built-in cmd 'cd'
 */
void help_cd(void)
{
	char *inf = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = " proceed to the DIRECTORY.\n\n\tIf no argument provided, the ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "cmd is interprated as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = " provided, the cmd is interprated as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "\tThe env vars PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "after changing the directory.\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}

/**
 * help_alias - Shows info about the built-in cmd 'alias'
 */
void help_alias(void)
{
	char *inf = "alias: alias [NAME[='VALUE'] ...]\n\tHandles the aliases.\n";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "\n\talias: Shows the list of all aliases, in ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "the format NAME='VALUE'.\n\talias name [name1 ...]:displays";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = " the aliases name, name1, and so on. In the ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Explains";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}

/**
 * help_help - Shows info of the built-in cmd 'help'
 */
void help_help(void)
{
	char *inf = "help: help\n\tView all possible built-in commands.\n";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "\n      help [BUILTIN NAME]\n\tGet specific info on each ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "of the built-in commands.\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}

/**
 * help_exit - Shows info on the built-in cmd 'exit'
 */
void help_exit(void)
{
	char *inf = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "STATUS arg is the integer used to terminate the process.";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = " If no parameter is provided, the cmd is interprated as";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = " exits now 0.\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}

/**
 * help_all - Populates all the available built-in commands.
 */
void help_all(void)
{
	char *inf = "Shell\nThese commands are explained as below.\n";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "Type 'help' to view this list.\nType 'help name' to learn ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "more about the fx 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}
