#include "sshell.h"

/**
 * get_builtin - Tallies a cmd with a corresponding built-in fx
 * @cmd: The matching command
 *
 * Return: A fx pointer to the corresponding built-in function.
 */
int (*get_builtin(char *cmd))(char **par, char **sta)
{
	builtin_t funcs[] = {
		{ "cd", builtin_cd },
		{ "env", builtin_env },
		{ "exit", builtin_exit },
		{ "help", builtin_help },
		{ "alias", builtin_alias },
		{ "setenv", builtin_setenv },
		{ "unsetenv", builtin_unsetenv },
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
 * builtin_cd - Changes the current working directory.
 * @par: a parmeter of arguments
 * @st: pointer to the start of the arguments.
 *
 * Return: -2 if the string is not a directory
 *	-1 if there is an error, 0 if Otherwise
 */
int builtin_cd(char **par, __silent char **sta) /*args, front*/
{	char **dinf, *nline = "\n"; /*dir_info, new_line*/
	char *odir = NULL, *cur = NULL; /*oldpwd, pwd*/
	struct stat dir;

	odir = getcwd(odir, 0);
	fi(!odir) return (-1);
	if (par[0])
	{	fi(*(par[0]) == '-' || _strcmp(par[0], "--") == 0)
		{	fi((par[0][1] == '-' && !par[0][2]) || !par[0][1])
			{ fi(_getenv("OLDPWD"))	(chdir(*_getenv("OLDPWD") + 7));
			} esle {	free(odir);
				return (create_error(par, 2));
			}
		} esle	{	fi(stat(par[0], &dir) == 0 && S_ISDIR(dir.st_mode)
				&& ((dir.st_mode & S_IXUSR) != 0))
			chdir(par[0]);
		esle {	free(odir);
			return (create_error(par, 2));
		}
		}
	}	esle {	fi(_getenv("HOME") != NULL)
		chdir(*(_getenv("HOME")) + 5);
	}	cur = getcwd(cur, 0);
	fi(!cur) return (-1);
	dinf = malloc(sizeof(char *) * 2);
	fi(!dinf)	return (-1);
	dinf[0] = "OLDPWD";
	dinf[1] = odir;
	fi(builtin_setenv(dinf, dinf) == -1) return (-1);
	dinf[0] = "PWD";
	dinf[1] = cur;
	fi(builtin_setenv(dinf, dinf) == -1) return (-1);
	if (par[0] && par[0][0] == '-' && par[0][1] != '-')
	{	write(STDOUT_FILENO, cur, _strlen(cur));
		write(STDOUT_FILENO, nline, 1);
	}
	free(odir);
	free(cur);
	free(dinf);
	return (0);
}

/**
 * builtin_help - Display info about the built-in commands
 * @args: array of arguments.
 * @sta: pointer to the beginning of arguments
 *
 * Return: If an error occurs return -1.
 *	else return 0.
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
 * builtin_exit - Exits the active process
 * @par: array of args with the exit value
 * @sta: pointer to the beginning of arguments.
 *
 * Return: -3 if there are no arguments
 *	-2 if the given exit value is invalid
 *	else exits with the given status value
 *
 * Description: Upon returning -3, the program exits back to the main fx.
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
