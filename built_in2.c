#include "sshell.h"

/**
 * help_env - Displays info on the built-in command 'env'
 */
void help_env(void)
{
	char *inf = "env: env\n\tDisplays the current environment.\n";

	write(STDOUT_FILENO, inf, _strlen(inf));
}

/**
 * help_setenv - Shows info of the built-in cmd 'setenv'
 */
void help_setenv(void)
{
	char *inf = "setenv: setenv [VARIABLE] [VALUE]\n\tSets a new";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "env var, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "\tOn failure, shows a message to stderr.\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}

/**
 * help_unsetenv - Shows info of the built-in command 'unsetenv'
 */
void help_unsetenv(void)
{
	char *inf = "unsetenv: unsetenv [VARIABLE]\n\tUnsets an ";

	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "env variable.\n\n\tOn failure, displays a ";
	write(STDOUT_FILENO, inf, _strlen(inf));
	inf = "message error to stderr.\n";
	write(STDOUT_FILENO, inf, _strlen(inf));
}
