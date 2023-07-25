#include "sshell.h"

/**
 * lgt - Counts the length of a number given
 * @num: number to be measured
 *
 * Return: length of the digit
 */
int lgt(int nmb)
{
	unsigned int nbr;
	int lnt = 1;

	if (nmb < 0)
	{
		lnt++;
		nbr = nmb * -1;
	}
	else
	{
		nbr = nmb;
	}
	while (nbr > 9)
	{
		lnt++;
		nbr /= 10;
	}

	return (lnt);
}

/**
 * _itoa - Function that converts an int to string
 * @nbr: The integer to be converted
 *
 * Return: a converted string
 */
char *_itoa(int nbr)
{
	char *bfr;
	int lnt = lgt(nbr);
	unsigned int nmb;

	bfr = malloc(sizeof(char) * (lnt + 1));
	if (!bfr)
		return (NULL);

	bfr[lnt] = '\0';

	if (nbr < 0)
	{
		nmb = nbr * -1;
		bfr[0] = '-';
	}
	else
	{
		nmb = nbr;
	}

	lnt--;
	do {
		bfr[lnt] = (nmb % 10) + '0';
		nmb /= 10;
		lnt--;
	} while (nmb > 0);

	return (bfr);
}


/**
 * create_error - Outputs an error message to stderr
 * @par: arguments parameters
 * @err: the error value
 *
 * Return: The error value.
 */
int create_error(char **par, int err)
{
	char *erra;

	switch (err)
	{
		case -1:
			erra = error_env(par);
			break;
		case 1:
			erra = error_1(par);
			break;
		case 2:
			if (*(par[0]) == 'e')
				erra = error_2_exit(++par);
			else if (par[0][0] == ';' || par[0][0] == '&' || par[0][0] == '|')
				erra = error_2_syntax(par);
			else
				erra = error_2_cd(par);
			break;
		case 126:
			erra = error_126(par);
			break;
		case 127:
			erra = error_127(par);
			break;
	}
	write(STDERR_FILENO, erra, _strlen(erra));

	if (erra)
		free(erra);
	return (err);

}
