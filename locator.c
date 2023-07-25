#include "sshell.h"

/**
 * get_location - locates a cmd in a PATH
 * @cmd: command to locate
 *
 * Return: On error occurs or the command missing - NULL.
 *         Elsse - the full path name of cmd.
 */
char *get_location(char *cmd)
{
	char **ph, *tp;
	struct stat st;
	list_t *dirs, *hd;

	ph = _getenv("PATH");
	if (!ph || !(*ph))
		return (NULL);

	dirs = get_path_dir(*ph + 5);
	hd = dirs;

	while (dirs)
	{
		tp = malloc(_strlen(dirs->dct) + _strlen(cmd) + 2);
		if (!tp)
			return (NULL);

		_strcpy(tp, dirs->dct);
		_strcat(tp, "/");
		_strcat(tp, cmd);

		if (stat(tp, &st) == 0)
		{
			free_list(hd);
			return (tp);
		}

		dirs = dirs->next;
		free(tp);
	}

	free_list(hd);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces with current working dir.
 * @ph: list of directories separated by colon
 *
 * Return: A copy of path replaced with the current working directory.
 */
char *fill_path_dir(char *ph)
{	int k, lgt = 0;
	char *ph1, *cur;

	cur = *(_getenv("PWD")) + 4;
	for (k = 0; ph[k]; k++)
	{
		if (ph[k] == ':')
		{
			if (ph[k + 1] == ':' || k == 0 || ph[k + 1] == '\0')
				lgt += _strlen(cur) + 1;
			else
				lgt++;
		}
		else
			lgt++;
	}
	ph1 = malloc(sizeof(char) * (lgt + 1));
	if (!ph1)
		return (NULL);
	ph1[0] = '\0';
	for (k = 0; ph[k]; k++)
	{
		if (ph[k] == ':')
		{
			if (k == 0)
			{
				_strcat(ph, cur);
				_strcat(ph1, ":");
			}
			else if (ph[k + 1] == ':' || ph[k + 1] == '\0')
			{
				_strcat(ph1, ":");
				_strcat(ph1, cur);
			}
			else
				_strcat(ph1, ":");
		}
		else
			_strncat(ph1, &ph[k], 1);
	}	return (ph1);
}

/**
 * get_path_dir - Tokenizes a list of dirs into a linked list.
 * @ph: colon-separated list of directories.
 *
 * Return: pointer to initialized linked list
 */
list_t *get_path_dir(char *pth)
{
	int idx;
	char **dirs, *path1;
	list_t *hd = NULL;

	path1 = fill_path_dir(pth);
	if (!path1)
		return (NULL);
	dirs = _strtok(path1, ":");
	free(path1);
	if (!dirs)
		return (NULL);

	for (idx = 0; dirs[idx]; idx++)
	{
		if (add_node_end(&hd, dirs[idx]) == NULL)
		{
			free_list(hd);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (hd);
}

