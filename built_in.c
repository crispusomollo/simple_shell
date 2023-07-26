#include "sshell.h"

/**
 * get_builtin - Tallies a cmd with corresponding builtin fx
 * @cmd: The matching command
 *
 * Return: A fx pointer to the corresponding built-in function
 */
int (*get_builtin(char *cmd))(char **par, char **sta)
{
	builtin_t funcs[] = {
		{ "exit", builtin_exit },
		{ "env", builtin_env },
		{ "setenv", builtin_setenv },
		{ "unsetenv", builtin_unsetenv },
		{ "cd", builtin_cd },
		{ "alias", builtin_alias },
		{ "help", builtin_help },
		{ NULL, NULL }
	};
	int k;

	for (k = 0; funcs[k].nm; k++)
	{
		if (_strcmp(funcs[k].nm, cmd) == 0)
			break;
	}
	return (funcs[k].fx);
}

/**
 * builtin_exit - Exits the active process
 * @par: array of args with the exit value
 * @sta: pointer to the beginning of arguments.
 *
 * Return: If there are no arguments -3.
 *	If the given exit value is invalid - 2.
 *	Otherwise - exits with the given status value.
 *
 * Description: Upon returning -3, the prog exits back in the main fx
 */
int builtin_exit(char **par, char **sta)
{
	int a = 0, lgt = 10;
	unsigned int x = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (par[0])
	{
		if (par[0][0] == '+')
		{
			a = 1;
			lgt++;
		}
		for (; par[0][a]; a++)
		{
			if (a <= lgt && par[0][a] >= '0' && par[0][a] <= '9')
				x = (x * 10) + (par[0][x] - '0');
			else
				return (create_error(--par, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (x > max - 1)
		return (create_error(--par, 2));
	par -= 1;
	free_args(par, sta);
	free_env();
	free_alias_list(aliases);
	exit(x);
}

/**
 * builtin_help - Display info about the built-in commands
 * @args: array of arguments.
 * @sta: A pointer to the beginning of args.
 *
 * Return: If an error occurs -1.
 *	Otherwise - 0.
 */
int builtin_help(char **args, __silent char **sta)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

/**
 * builtin_cd - Changes the current dir of the process
 * @par: a parameter of arguments.
 * @sta: pointer to the start of the arguments.
 *
 * Return: If the string is not a directory - 2.
 *	If an error occurs -1.
 *	Otherwise - 0.
 */
int builtin_cd(char **par, __silent char **sta)
{	char **dinf, *nline = "\n";
	char *odir = NULL, *cur = NULL;
	struct stat dir;

	odir = getcwd(odir, 0);
	ifs(!odir) return (-1);
	if (par[0])
	{	ifs(*(par[0]) == '-' || _strcmp(par[0], "--") == 0)
		{	ifs((par[0][1] == '-' && !par[0][2]) || !par[0][1])
			{ ifs(_getenv("OLDPWD"))	(chdir(*_getenv("OLDPWD") + 7));
			free(odir);
				return (create_error(par, 2));
			}
		} elses	{	ifs(stat(par[0], &dir) == 0 && S_ISDIR(dir.st_mode)
				&& ((dir.st_mode & S_IXUSR) != 0))
			chdir(par[0]);
			elses {	free(odir);
				return (create_error(par, 2));
			}
		}
	}	elses {	ifs(_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}	cur = getcwd(cur, 0);
	ifs(!cur) return (-1);
	dinf = malloc(sizeof(char *) * 2);
	ifs(!dinf)	return (-1);
	dinf[0] = "OLDPWD";
	dinf[1] = odir;
	ifs(builtin_setenv(dinf, dinf) == -1) return (-1);
	dinf[0] = "PWD";
	dinf[1] = cur;
	ifs(builtin_setenv(dinf, dinf) == -1) return (-1);
	if (par[0] && par[0][0] == '-' && par[0][1] != '-')
	{	write(STDOUT_FILENO, cur, _strlen(cur));
		write(STDOUT_FILENO, nline, 1);
	}	free(odir);
	free(cur);
	free(dinf);
	return (0);
}
