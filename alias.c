#include "sshell.h"

void print_alias(alias_a *alias);
char **replace_aliases(char **par);
void set_alias(char *vname, char *val);

/**
 * builtin_alias - a built in command
 * that prints all aliases
 * @args: arguments array.
 * @front: pointer to the start of arguments.
 *
 * Return: If an error occurs return -1.
 *         else return 0.
 */
int builtin_alias(char **par, __silent char **sta)
{
	alias_a *tmp = aliases;
	int u, rt = 0; /*i, ret*/
	char *val;

	if (!par[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->nxt;
		}
		return (rt);
	}
	for (u = 0; par[u]; u++)
	{
		tmp = aliases;
		val = _strchr(par[u], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(par[u], tmp->nm) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->nxt;
			}
			if (!tmp)
				rt = create_error(par + u, 1);
		}
		else
			set_alias(par[u], val);
	}
	return (rt);
}

/**
 * set_alias - set an existing alias with a new value
 * @vname: the alias name
 * @val: the value of the alias.
 */
void set_alias(char *vname, char *val)
{
	alias_a *tmp = aliases;
	int lgt, p, q;
	char *nval;

	*val = '\0';
	val++;
	lgt = _strlen(val) - _strspn(val, "'\"");
	nval = malloc(sizeof(char) * (lgt + 1));
	if (!nval)
		return;
	for (p = 0, q = 0; val[p]; p++)
	{
		if (val[p] != '\'' && val[p] != '"')
			nval[q++] = val[p];
	}
	nval[q] = '\0';
	while (tmp)
	{
		if (_strcmp(vname, tmp->nm) == 0)
		{
			free(tmp->val);
			tmp->val = nval;
			break;
		}
		tmp = tmp->nxt;
	}
	if (!tmp)
		add_alias_end(&aliases, vname, nval);
}

/**
 * print_alias - Fx that prints an alias
 * @alias: the pointer to the alias
 */
void print_alias(alias_a *alias)
{
	char *astr; /*alias string*/
	int lgt = _strlen(alias->nm) + _strlen(alias->val) + 4;

	astr = malloc(sizeof(char) * (lgt + 1));
	if (!astr)
		return;
	_strcpy(astr, alias->nm);
	_strcat(astr, "='");
	_strcat(astr, alias->val);
	_strcat(astr, "'\n");

	write(STDOUT_FILENO, astr, lgt);
	free(astr);
}
/**
 * replace_aliases - Checks the args and replaces any alias that matches
 * @args: a 2-D pointer to the args
 *
 * Return: a 2-D pointer to the args.
 */
char **replace_aliases(char **par)
{
	alias_a *tmp;
	int m; /*i*/
	char *nval; /*new_value*/

	if (_strcmp(par[0], "alias") == 0)
		return (par);
	for (m = 0; par[m]; m++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(par[m], tmp->nm) == 0)
			{
				nval = malloc(sizeof(char) * (_strlen(tmp->val) + 1));
				if (!nval)
				{
					free_args(par, par);
					return (NULL);
				}
				_strcpy(nval, tmp->val);
				free(par[m]);
				par[m] = nval;
				m--;
				break;
			}
			tmp = tmp->nxt;
		}
	}

	return (par);
}
