#include "sshell.h"

ssize_t get_new_len(char *ln);
void logical_ops(char *ln, ssize_t *nlen);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @ln: pointer to a line read from standard input
 * @rd: length of the line
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **ln, ssize_t rd)
{
	char *oline, *nline;
	char prev, curr, next;
	size_t p, q;
	ssize_t nlen;

	nlen = get_new_len(*ln);
	if (nlen == rd - 1)
		return;
	nline = malloc(nlen + 1);
	if (!nline)
		return;
	p = 0;
	oline = *ln;
	for (p = 0; oline[p]; p++)
	{
		curr = oline[p];
		next = oline[p + 1];
		if (p != 0)
		{
			prev = oline[p - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					nline[q++] = ' ';
					nline[q++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					nline[q++] = ';';
					nline[q++] = ' ';
					continue;
				}
				if (prev != ' ')
					nline[q++] = ' ';
				nline[q++] = ';';
				if (next != ' ')
					nline[q++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					nline[q++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					nline[q++] = '&';
					nline[q++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					nline[q++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					nline[q++] = '|';
					nline[q++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (p != 0 && oline[p - 1] != ' ')
				nline[q++] = ' ';
			nline[q++] = ';';
			if (next != ' ' && next != ';')
				nline[q++] = ' ';
			continue;
		}
		nline[q++] = oline[p];
	}
	nline[q] = '\0';

	free(*ln);
	*ln = nline;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @ln: The line to check.
 *
 * Return: new length of the line
 *
 * Description: Reduce short lines with '#' comments with '\0'.
 */

ssize_t get_new_len(char *ln)
{
	size_t s;
	ssize_t nlen = 0;
	char curr, next;

	for (s = 0; ln[s]; s++)
	{
		curr = ln[s];
		next = ln[s + 1];
		if (curr == '#')
		{
			if (s == 0 || ln[s - 1] == ' ')
			{
				ln[s] = '\0';
				break;
			}
		}
		else if (s != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && ln[s - 1] != ' ' && ln[s - 1] != ';')
				{
					nlen += 2;
					continue;
				}
				else if (ln[s - 1] == ';' && next != ' ')
				{
					nlen += 2;
					continue;
				}
				if (ln[s - 1] != ' ')
					nlen++;
				if (next != ' ')
					nlen++;
			}
			else
				logical_ops(&ln[s], &nlen);
		}
		else if (curr == ';')
		{
			if (s != 0 && ln[s - 1] != ' ')
				nlen++;
			if (next != ' ' && next != ';')
				nlen++;
		}
		nlen++;
	}
	return (nlen);
}
/**
 * logical_ops - Checks for logical operators "||" or "&&".
 * @ln: pointer to the xter to check in the line
 * @nlen: pointer to nlen in get_new_len fx
 */
void logical_ops(char *ln, ssize_t *nlen)
{
	char prev, curr, next;

	prev = *(ln - 1);
	curr = *ln;
	next = *(ln + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*nlen)++;
		else if (prev == '&' && next != ' ')
			(*nlen)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*nlen)++;
		else if (prev == '|' && next != ' ')
			(*nlen)++;
	}
}

