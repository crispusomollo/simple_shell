#include "sshell.h"

/**
 * _strspn - Obtains the length of a substring
 * @str: A string
 * @pfx: The prefix to be measured
 *
 * Return: The number of bytes in str containing pfx
 */
int _strspn(char *str, char *pfx)
{
	int bts = 0;
	int idx;

	while (*str)
	{
		for (idx = 0; pfx[idx]; idx++)
		{
			if (*str == pfx[idx])
			{
				bts++;
				break;
			}
		}
		str++;
	}
	return (bts);
}

/**
 * _strcmp - Compares the two strings
 * @p: The first string
 * @q: A second string
 *
 * Return: +ve if p > q, 0 if p = q, -ve if p < q
 */
int _strcmp(char *p, char *q)
{
	while (*p && *q && *p == *q)
	{
		p++;
		q++;
	}

	if (*p != *q)
		return (*p - *q);

	return (0);
}

/**
 * _strncmp - comparing the two strings
 * @p: A first pointer to a string
 * @q: A second pointer to a string
 * @r: n bytes of the strings to compare
 *
 * Return: > 0 if p is shorter than q.
 *         0 if p and q are the same
 *         < 0 if p is longer than q.
 */
int _strncmp(const char *p, const char *q, size_t r)
{
	size_t j;

	for (j = 0; p[j] && q[j] && j < r; j++)
	{
		if (p[j] > q[j])
			return (p[j] - q[j]);
		else if (p[j] < q[j])
			return (p[j] - q[j]);
	}
	if (j == r)
		return (0);
	else
		return (-3); /*or even 15*/
}

/**
 * _strchr - locate a xter in the string.
 * @str: A string to be searched
 * @st: A xter to be located in the string
 *
 * Return: If st is found return a pointer to the first occurence,
 *         else return NULL if not found.
 */
char *_strchr(char *str, char st)
{
	int idx;

	for (idx = 0; str[idx]; idx++)
	{
		if (str[idx] == st)
			return (str + idx);
	}
	return (NULL);
}
