#include "sshell.h"

/**
 * _getenv - get the env var from the PATH.
 * @vbl: The name of the env variable.
 *
 * Return: If the env var does not exist return NULL.
 *         else return a pointer to the env variable.
 */
char **_getenv(const char *vbl)
{
	int idx, lgt; /*index, len*/

	lgt = _strlen(vbl);
	for (idx = 0; environ[idx]; idx++)
	{
		if (_strncmp(vbl, environ[idx], lgt) == 0)
			return (&environ[idx]);
	}

	return (NULL);
}

/**
 * _copyenv - creates another copy to the env.
 *
 * Return: NULL if an error occurs.
 *         else return a pointer to the copy.
 */
char **_copyenv(void)
{
	char **nenv;
	size_t i;
	int idx;

	for (i = 0; environ[i]; i++)
		;

	nenv = malloc(sizeof(char *) * (i + 1));
	if (!nenv)
		return (NULL);

	for (idx = 0; environ[idx]; idx++)
	{
		nenv[idx] = malloc(_strlen(environ[idx]) + 1);

		if (!nenv[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(nenv[idx]);
			free(nenv);
			return (NULL);
		}
		_strcpy(nenv[idx], environ[idx]);
	}
	nenv[idx] = NULL;

	return (nenv);
}

/**
 * free_env - Frees the copy of the environment
 */
void free_env(void)
{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		free(environ[idx]);
	free(environ);
}
