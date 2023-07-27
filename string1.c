#include "sshell.h"

/**
 * _strcpy - copy a sring to the destination buffer.
 * @dsn: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination.
 */
char *_strcpy(char *dsn, const char *src)
{
	size_t k;

	for (k = 0; src[k] != '\0'; k++)
		dsn[k] = src[k];
	dsn[k] = '\0';
	return (dsn);
}

/**
 * _strlen - Returns the length of a string
 * @pr: pointer to the xters string
 *
 * Return: the xter string length
 */
int _strlen(const char *pr)
{
	int lgt = 0;

	if (!pr)
		return (lgt); /*length*/
	for (lgt = 0; pr[lgt]; lgt++)
		;
	return (lgt);
}

/**
 * _strcat - Fx to concantenate two strings
 * @dsn: A pointer to the destination string
 * @src: A pointer to the source string
 *
 * Return: pointer to the dest string
 */
char *_strcat(char *dsn, const char *src)
{
	const char *srt;
	char *dst;

	srt =  src;
	dst = dsn;

	while (*srt != '\0')
		*dst++ = *srt++;
	*dst = '\0';

	while (*dst != '\0')
		dst++;

	return (dsn);
}

/**
 * _strncat - Concantenate two strings from copied source.
 * @dsn: A pointer to the destination string
 * @src: A pointer to the source string
 * @bts: the number of bytes to copy from the source.
 *
 * Return: A pointer to the destination string
 */
char *_strncat(char *dsn, const char *src, size_t bts)
{
	size_t dsl = _strlen(dsn);
	size_t z;

	for (z = 0; z < bts && src[z] != '\0'; z++)
		dsn[dsl + z] = src[z];
	dsn[dsl + z] = '\0';

	return (dsn);
}
