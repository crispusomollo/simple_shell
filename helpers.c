#include "sshell.h"

/**
 * get_args - get a cmd from the std input
 * @buf: buffer to store the cmd
 * @xret: The return value of the last cmd
 *
 * Return: If an error occurs return NULL.
 *         Else a pointer to the stored cmd
 */
char *get_args(char *buf, int *xret)
{
	size_t s = 0;
	ssize_t rd;
	char *prompt1 = "$ ";

	if (buf)
		free(buf);

	rd = _getline(&buf, &s, STDIN_FILENO);
	if (rd == -1)
		return (NULL);
	if (rd == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt1, 2);
		return (get_args(buf, xret));
	}

	buf[rd - 1] = '\0';
	substitute_arg(&buf, xret);
	handle_line(&buf, rd);

	return (buf);
}

/**
 * call_args - partition ops from cmds and call them
 * @par: array of arguments.
 * @sta: pointer to the start of arguments.
 * @xret: return value of the parent process command.
 *
 * Return: The return value of the previous executed cmd
 */
int call_args(char **par, char **sta, int *xret)
{	int rt, idx;

	if (!par[0])
		return (*xret);
	for (idx = 0; par[idx]; idx++)
	{
		if (_strncmp(par[idx], "||", 2) == 0)
		{	free(par[idx]);
			par[idx] = NULL;
			par = replace_aliases(par);
			rt = run_args(par, sta, xret);
			if (*xret != 0)
			{	par = &par[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; par[idx]; idx++)
					free(par[idx]);
				return (rt);
			}
		}
		else if (_strncmp(par[idx], "&&", 2) == 0)
		{	free(par[idx]);
			par[idx] = NULL;
			par = replace_aliases(par);
			rt = run_args(par, sta, xret);
			if (*xret == 0)
			{	par = &par[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; par[idx]; idx++)
					free(par[idx]);
				return (rt);
			}
		}
	}	par = replace_aliases(par);
	rt = run_args(par, sta, xret);
	return (rt);
}

/**
 * run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = exec(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}

