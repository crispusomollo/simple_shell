#include "sshell.h"

/**
 * error_env - Generates an error message for builtin_env
 * @par: array of arguments
 *
 * Return: the error message string
 */
char *error_env(char **par)
{
	char *erra, *histr;
	int lnt;

	histr = _itoa(hist);
	if (!histr)
		return (NULL);

	par--;
	lnt = _strlen(name) + _strlen(histr) + _strlen(par[0]) + 45;
	erra = malloc(sizeof(char) * (lnt + 1));
	if (!erra)
	{
		free(histr);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histr);
	_strcat(erra, ": ");
	_strcat(erra, par[0]);
	_strcat(erra, ": Cannot add/remove from the environment\n");

	free(histr);
	return (erra);
}

/**
 * error_1 - Create error message for the builtin_alias
 * @par: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **par)
{
	int len;
	char *erra;

	len = _strlen(name) + _strlen(par[0]) + 13;
	erra = malloc(sizeof(char) * (len + 1));
	if (!erra)
		return (NULL);

	_strcpy(erra, "alias: ");
	_strcat(erra, par[0]);
	_strcat(erra, " not found\n");

	return (erra);
}

/**
 * error_2_exit - create error message for the builtin_exit
 * @par: array of args passed to the command
 *
 * Return: error message string
 */
char *error_2_exit(char **par)
{
	char *erra, *histr;
	int lnt;

	histr = _itoa(hist);
	if (!histr)
		return (NULL);

	lnt = _strlen(name) + _strlen(histr) + _strlen(par[0]) + 27;
	erra = malloc(sizeof(char) * (lnt + 1));
	if (!erra)
	{
		free(histr);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histr);
	_strcat(erra, ": exit: Illegal number: ");
	_strcat(erra, par[0]);
	_strcat(erra, "\n");

	free(histr);
	return (erra);
}

/**
 * error_2_cd - create error message for the builtin_cd
 * @par: array of args passed to the command
 *
 * Return: an error message string.
 */
char *error_2_cd(char **par)
{
	char *erra, *histr;
	int len;

	histr = _itoa(hist);
	if (!histr)
		return (NULL);

	if (par[0][0] == '-')
		par[0][2] = '\0';
	len = _strlen(name) + _strlen(histr) + _strlen(par[0]) + 24;
	erra = malloc(sizeof(char) * (len + 1));
	if (!erra)
	{
		free(histr);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histr);
	if (par[0][0] == '-')
		_strcat(erra, ": cd: This option is not allowed ");
	else
		_strcat(erra, ": cd: Cannot cd to ");
	_strcat(erra, par[0]);
	_strcat(erra, "\n");

	free(histr);
	return (erra);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @par: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **par)
{
	char *erra, *histr;
	int lnt;

	histr = _itoa(hist);
	if (!histr)
		return (NULL);

	lnt = _strlen(name) + _strlen(histr) + _strlen(par[0]) + 33;
	erra = malloc(sizeof(char) * (lnt + 1));
	if (!erra)
	{
		free(histr);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histr);
	_strcat(erra, ": Syntax error: \"");
	_strcat(erra, par[0]);
	_strcat(erra, "\" Unexpected error\n");

	free(histr);
	return (erra);
}
