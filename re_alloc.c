#include "sshell.h"

/**
 * _realloc - Re_allocates a mem block using malloc and free.
 * @pntr: pointer to the mem  allocated previously.
 * @osize: size in bytes of the allocated space for pntr.
 * @nsize: size in bytes for the new mem block.
 *
 * Return: If nsize == osize return pntr.
 *         If nsize == 0 and pntr is not NULL return NULL.
 *         Otherwise return a pointer to the mem block.
 */
void *_realloc(void *pntr, unsigned int osize, unsigned int nsize)
{
	void *memb;
	char *pntr1, *flr;
	unsigned int idx;

	if (nsize == osize)
		return (pntr);

	if (pntr == NULL)
	{
		memb = malloc(nsize);
		if (memb == NULL)
			return (NULL);

		return (memb);
	}

	if (nsize == 0 && pntr != NULL)
	{
		free(pntr);
		return (NULL);
	}

	pntr1 = pntr;
	memb = malloc(sizeof(*pntr1) * nsize);
	if (memb == NULL)
	{
		free(pntr);
		return (NULL);
	}

	flr = memb;

	for (idx = 0; idx < osize && idx < nsize; idx++)
		flr[idx] = *pntr1++;

	free(pntr);
	return (memb);
}

/**
 * assign_lptr - Reassigns lptr var for _getline.
 * @lptr: A buffer to store an input string.
 * @sn: The size of lptr.
 * @buf: string to assign to lineptr.
 * @sb: The size of buffer.
 */
void assign_lptr(char **lptr, size_t *sn, char *buf, size_t sb)
{
	if (*lptr == NULL)
	{
		if (sb > 120)
			*sn = sb;
		else
			*sn = 120;
		*lptr = buf;
	}
	else if (*sn < sb)
	{
		if (sb > 120)
			*sn = sb;
		else
			*sn = 120;
		*lptr = buf;
	}
	else
	{
		_strcpy(*lptr, buf);
		free(buf);
	}
}

/**
 * _getline - Reads input from a user.
 * @lptr: buffer to store the input
 * @s: size of lptr.
 * @str: a stream to read from
 *
 * Return: number of bytes read.
 */
ssize_t _getline(char **lptr, size_t *s, FILE *str)
{
	static ssize_t inp;
	ssize_t rt;
	char ch = 'x', *buf;
	int rh;

	if (inp == 0)
		fflush(str);
	else
		return (-1);
	inp = 0;

	buf = malloc(sizeof(char) * 120);
	if (!buf)
		return (-1);

	while (ch != '\n')
	{	rh = read(STDIN_FILENO, &ch, 1);
		if (rh == -1 || (rh == 0 && inp == 0))
		{
			free(buf);
			return (-1);
		}
		if (rh == 0 && inp != 0)
		{
			inp++;
			break;
		}

		if (inp >= 120)
			buf = _realloc(buf, inp, inp + 1);

		buf[inp] = ch;
		inp++;
	}	buf[inp] = '\0';
	assign_lptr(lptr, s, buf, inp);
	rt = inp;
	if (rh != 0)
		inp = 0;
	return (rt);
}
