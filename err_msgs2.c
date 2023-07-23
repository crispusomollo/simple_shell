#include "sshell.h"

/**
 * error_126 - Creates error message for 'denied permissions'
 * @par: arguments parameters
 *
 * Return: error message string
 */
char *error_126(char **par)
{
	char *erra, *histr;
	int lgt;

	histr = _itoa(hist);
	if (!histr)
		return (NULL);

	lgt = _strlen(name) + _strlen(histr) + _strlen(par[0]) + 24;
	erra = malloc(sizeof(char) * (lgt + 1));
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
	_strcat(erra, ": Permission is denied\n");

	free(histr);
	return (erra);
}

/**
 * error_127 - create error message for 'command not found'
 * @par: arguments parameters
 *
 * Return: error string message
 */
char *error_127(char **par)
{
	char *erra, *histr;
	int lnt;

	histr = _itoa(hist);
	if (!histr)
		return (NULL);

	lnt = _strlen(name) + _strlen(histr) + _strlen(par[0]) + 16;
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
	_strcat(erra, ": not found\n");

	free(hist_str);
	return (erra);
}
