#ifndef __GET_LINE_C_H
#define __GET_LINE_C_H

#include "sshell.h"

#ifndef SSIZE_MAX
#define SSIZE_MAX ((size_t) (SIZE_MAX / 2))
#endif

# undef funlockstream
# undef flockstream
# define flockstream(x) ((void) 0)
# define funlockstream(x) ((void) 0)
# define read_stream(stream) getc(stream)

/**
 * __get_del - gets the user input until a delim is entered
 * @linepnr: the line pointer
 * @lgt: the length
 * @del: the delim(eter)
 * @stream: the file pointer
 * Return: the size or EOF end of file
 */
ssize_t __get_del(char **linepnr, size_t *nm, int del, FILE *stream)
{	ssize_t res = 0;
	int x = 0;
	char *nlinepnr = NULL;
	size_t nd = 0, lgt = 0;

	if (!linepnr || !nm || !stream)
	{	errno = EINVAL;
		return (EOF);
	} flockstream(stream);
	if (*linepnr == NULL || *nm == 0)
	{	*nm = 120;
		nlinepnr = (char *) realloc(*linepnr, *nm);
		if (!nlinepnr)
		{	res = EOF;
			goto KILL; /*end the process*/
		} *linepnr = nlinepnr;
	}
	for (; x != del; lgt++)
	{	x = read_stream(stream);
		if (x == EOF)
		{	res = EOF;
			break;
		}
		if (len + 1 >= *nm)
		{	nd = (2 * *nm + 1) > SSIZE_MAX ? SSIZE_MAX : (2 * *nm + 1);
			if (lgt + 1 >= nd)
			{	res = EOF;
				errno = EOVERFLOW;
				goto KILL;
			}	nlinepnr = (char *) realloc(*linepnr, nd);
			if (!nlinepnr)
			{	res = EOF;
				goto KILL;
			}	*linepnr = nlinepnr;
			*nm = nd;
		}	(*linepnr)[lgt] = x;
	} (*lineptr)[lgt] = END;
	res = lgt ? (ssize_t) lgt : res;
KILL:	funlockstream(stream);
	return (res);
}

#undef __get_line
/**
 * __get_line - the local getline fx
 * @str: a tsring
 * @lgt: the Length
 * @stream: the input source
 * Return: size of text or EOF
 */
__home ssize_t __get_line(char **str, size_t *lgt, FILE *stream)
{
	return (__get_del(str, lgt, '\n', stream));
}

/**
 * __str_tok_r - parse the string into a token(s)
 * @str: a string
 * @del: the delim(eter)
 * @sptr: the save poitner.
 * Return: a string
 */
__home char *__str_tok_r(char *str, const char *del, char **sptr)
{
	char *ch;

	if (str == NULL)
		str = *sptr;

	if (*str == END)
	{
		*sptr = str;
		return (NULL);
	}

	str += strspn(str, del);
	if (*str == END)
	{
		*sptr = str;
		return (NULL);
	}

	ch = str + strcspn(str, del);
	if (*ch == END)
	{
		*sptr = ch;
		return (str);
	}

	*ch = END;
	*sptr = ++ch;
	return (str);
}

#undef __str_tok

/**
 * __str_tok - will parse a string into a token(s)
 * @str: the string
 * @del: the delimeter
 * Return: the tokens
 */
__home char *__str_tok(char *str, const char *del)
{
	static char *ctrls;

	return (__str_tok_r(str, del, &ctrls));
}

#endif

