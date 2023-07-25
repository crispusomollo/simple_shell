#ifndef _STR_TOOLS_H
#define _STR_TOOLS_H

#include "sshell.h"

/**
 * _strlen - the length of the string
 * @str: the string
 *
 * Return: the length of string
 */
__home int _strlen(char *str)
{
	int n = 0;

	while (*(str + n) != '\0')
	{
		n++;
	}

	return (n);
}

/**
 * _strncmp - compares 2 strings with a specific length
 * @str1: the first string
 * @str2: a second string
 * @lgt: the length
 *
 * Return: the xters difference (where 0 means equal)
 */
__home int _strncmp(char *str1, char *str2, int lgt)
{
	int x = 1;

	while (x <= lgt)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		x++;
	}
	return (0);
}

/**
 * _strcmp - compares the two given strings
 * @st1: the first string
 * @st2: a second string
 *
 * Return: the xters difference (where 0 means equal)
 */
__home int _strcmp(char *st1, char *st2)
{
	while (*st1 == *st2)
	{
		if (*st1 == '\0')
			return (0);
		st1++;
		st2++;
	}
	return (*st1 - *st2);
}

/**
 * _strconcat - copy a string then return a pointer to the array
 * @str1: the first string
 * @str2: a second string
 *
 * Return: a pointer to the array or NULL
 */
__home char *_strconcat(char *str1, char *str2)
{
	int w = 0, x = 0, y = 0, z = 0;
	char *ch;

	if (str1 == NULL)
		str1 = "";
	if (str2 == NULL)
		str2 = "";

	while (*(str1 + w))
		w++;

	while (*(str2 + x))
		x++;

	ch = malloc(sizeof(char) * (w + x + 3));
	if (ch == NULL)
		return (NULL);

	for (y = 0; y < w; y++)
	{
		*(ch + y) = *(str1 + y);
	}

	for (z = 0; z <= x; z++)
	{
		*(ch + y + z) = *(str2 + z);
	}

	return (ch);
}

/**
 * _strdup - return a pointer to the allocated mem space
 * @stn: a string
 *
 * Return: a pointer to a memory space or NULL
 */
__home char *_strdup(char *stn)
{
	int lgt, x;
	chr *ch;

	if (!stn)
		return (NULL);

	lgt = _strlen(stn);
	ch = malloc(sizeof(char) * lgt + 1);

	if (!ch)
		return (NULL);

	for (x = 0; x < lgt; x++)
		ch[x] = stn[x];
	ch[x] = END;

	return (ch);
}

#endif
