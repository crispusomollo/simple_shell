#include "sshell.h"

/**
 * free_args - frees up memory taken by args
 * @par: a pointer  containing cmds/args
 * @sta: pointer to the start of the args
 */
void free_args(char **par, char **sta)
{
	size_t s;

	for (s = 0; par[s] || par[s + 1]; s++)
		free(par[s]);

	free(sta);
}

/**
 * get_pid - gets the current process ID
 * Description: opens the stat file
 *
 * Return: On sucess return ID else NULL on fail
 */
char *get_pid(void)
{
	size_t s = 0;
	char *buf;
	ssize_t fl;

	fl = open("/proc/self/stat", O_RDONLY);
	if (fl == -1)
	{
		perror("Can not read the file");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(fl);
		return (NULL);
	}
	read(fl, buf, 120);
	while (buf[s] != '')
		s++;
	buf[s] = '\0';

	close(fl);
	return (buf);
}

/**
 * get_env_value - gets corresponding value to an env var
 * @bg: env variable to search
 * @lgt: length of the env variable to search for
 *
 * Return: if var not found return an empty string
 * else return value of the env variable
 *
 * Description: Variables store in format VARIABLE=VALUE
 */
char *get_env_value(char *bg, int lgt)
{
	char **vaddr;
	char *tmp, *rep = NULL, *var;

	var = malloc(lgt + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, bg, lgt);

	vadrr = _getenv(var);
	free(var);

	if (vaddr)
	{
		tmp = *vaddr;
		while (*tmp != '=')
			tmp++;
		tmp++;
		rep = malloc(_strlen(tmp) + 1);
		if (rep)
			_strcpy(rep, tmp);
	}
	return (rep);
}

/**
 * substitute_arg - handles a variable representation
 * @ln: pointer with the cmd and args
 * @xret: pointer to the return value of last command
 *
 * Description: replaces $$ with the current PID,
 * $? with the value of the executed program
 */
void substitute_arg(char **ln, int *xret)
{int p, q = 0, lgt;
	char *rep = NULL, *oline = NULL, *nline;

	oline = *ln;

	for (p = 0; oline[p]; p++)
	{
		if (oline[p] == '$' && oline[p + 1] &&
				oline[p + 1] != '')
		{
			if (oline[p + 1] == '$')
			{rep = get_pid();
				q = p + 2;
			}
			else if (oline[p + 1] == '?')
			{rep = _itoa(*xret);
				q = p + 2;
			}
			else if (oline[p + 1])
			{
				for (q = p + 1; oline[q] && oline[q] != '$' && oline[q] != ' ';)
					q++;
				lgt = q - (p + 1);
				rep = get_env_value(&oline[p + 1], lgt);
			}
			nline = malloc(p + _strlen(rep) + _strlen(&oline[q]) + 1);
			if (!ln)
				return;
			nline[0] = '\0';
			_strncat(nline, oline, p);
			if (rep)
			{	_strcat(nline, rep);
				free(rep);
				rep = NULL;
			}	_strcat(nline, &oline[q]);
			free(oline);
			*ln = nline;
			oline = nline;
			p = -1;
		}
	}
}
