#include "sshell.h"
/*This is the main program*/

/**
 * sig_handler - generates a prompt upon a signal.
 * @sgn: the signal.
 */
void sig_handler(int sgn)
{
	char *prompt1 = "\n$ "; /*new prompt*/

	(void)sgn;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, prompt1, 3);
}

/**
 * exec - execute a cmd in a linked process
 * @args: arguments array
 * @front: the pointer to the start of args
 *
 * Return: If an error occurs - a corresponding error code.
 *         Otherwise return the exit value of the last cmd.
 */
int exec(char **args, char **front)
{	pid_t child_pid;
	int st, flg = 0, rt = 0; /*status,flag,ret*/
	char *cmd = args[0]; /*command*/

	if (cmd[0] != '/' && cmd[0] != '.')
	{	flg = 1;
		cmd = get_location(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			rt = (create_error(args, 126));
		else
			rt = (create_error(args, 127));
	}
	else
	{	child_pid = fork();
		if (child_pid == -1)
		{
			if (flg)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{	execve(cmd, args, environ);
			if (errno == EACCES)
				rt = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(rt);
		}
		else
		{	wait(&st);
			rt = WEXITSTATUS(st);
		}
	}
	if (flg)
		free(cmd);
	return (rt);
}

/**
 * main - will run a simple unix command interpreter
 * @argc: the no. of args supplied to the program.
 * @argv: array of pointers to the arguments.
 *
 * Return: value of the last executed cmd.
 */
int main(int argc, char *argv[])
{	int rt = 0, ret;
	int *xrt = &ret;
	char *prompt1 = "$ ", *nline = "\n"; /*prompt,new_line*/

	nm = argv[0];
	histr = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);
	*xrt = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{	rt = file_cmds(argv[1], xrt);
		free_env();
		free_alias_list(aliases);
		return (*xrt);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (rt != END_OF_FILE && rt != EXIT)
			rt = handle_args(xrt);
		free_env();
		free_alias_list(aliases);
		return (*xrt);
	}
	while (1)
	{	write(STDOUT_FILENO, prompt1, 2);
		rt = handle_args(xrt);
		if (rt == END_OF_FILE || rt == EXIT)
		{
			if (rt == END_OF_FILE)
				write(STDOUT_FILENO, nline, 1);
			free_env();
			free_alias_list(aliases);
			exit(*xrt);
		}
	}
	free_env();
	free_alias_list(aliases);
	return (*xrt);
}

