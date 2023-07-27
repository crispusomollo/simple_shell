#include "sshell.h"

/**
 * builtin_env - print the current env.
 * @par: arguments parameters.
 * @sta: a pointer to the start of args.
 *
 * Return: -1 on error, 0 on success.
 *
 * Description: prints one variable per line
 */
int builtin_env(char **par, __silent char **sta)
{
	int idx; /*index*/
	char ch = '\n';

	if (!environ)
		return (-1);

	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], _strlen(environ[idx]));
		write(STDOUT_FILENO, &ch, 1);
	}

	(void)par;
	return (0);
}

/**
 * builtin_setenv - add or modify an env variable to the PATH.
 * @par: an array of arguments
 * @sta: a pointer to the start of arguments.
 * Description: par[1] - name of the new or existing PATH variable.
 *              par[2] - value to set the new or changed variable to.
 *
 * Return: 0 on success, else on error return -1.
 */
int builtin_setenv(char **par, __silent char **sta)
{
	char **envar = NULL, **nenv, *nval;
	size_t w; /*size*/
	int idx;

	if (!par[0] || !par[1])
		return (create_error(par, -1));

	nval = malloc(_strlen(par[0]) + 1 + _strlen(par[1]) + 1);
	if (!nval)
		return (create_error(par, -1));
	_strcpy(nval, par[0]);
	_strcat(nval, "=");
	_strcat(nval, par[1]);

	envar = _getenv(par[0]);
	if (envar)
	{
		free(*envar);
		*envar = nval;
		return (0);
	}
	for (w = 0; environ[w]; w++)
		;

	nenv = malloc(sizeof(char *) * (w + 2));
	if (!nenv)
	{
		free(nval);
		return (create_error(par, -1));
	}

	for (idx = 0; environ[idx]; idx++)
		nenv[idx] = environ[idx];

	free(environ);
	environ = nenv;
	environ[idx] = nval;
	environ[idx + 1] = NULL;

	return (0);
}

/**
 * builtin_unsetenv - Remove an env variable from the PATH.
 * @par: arguments parameters.
 * @sta: pointer to the start of the arguments.
 * Description: par[0] is the PATH variable to remove.
 *
 * Return: On suceess return 0, else on error return -1.
 */
int builtin_unsetenv(char **par, __silent char **sta)
{
	char **envar, **nenv;
	size_t z; /*size*/
	int idx1, idx2;

	if (!par[0])
		return (create_error(par, -1));
	envar = _getenv(par[0]);
	if (!envar)
		return (0);

	for (z = 0; environ[z]; z++)
		;

	nenv = malloc(sizeof(char *) * z);
	if (!nenv)
		return (create_error(par, -1));

	for (idx1 = 0, idx2 = 0; environ[idx1]; idx1++)
	{
		if (*envar == environ[idx1])
		{
			free(*envar);
			continue;
		}
		nenv[idx2] = environ[idx1];
		idx2++;
	}
	free(environ);
	environ = nenv;
	environ[z - 1] = NULL;

	return (0);
}
