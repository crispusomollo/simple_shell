#include "sshell.h"

/**
 * token_len - Locates delim index marking the end of first
 *             token contained in a string
 * @str: string to be searched.
 * @del: delimiter character.
 *
 * Return: delim index marking the end of initial token
 *         pointed to by str.
 */
int token_len(char *str, char *del)
{
	int idx = 0, len = 0;

	while (*(str + idx) && *(str + idx) != *del)
	{
		len++;
		idx++;
	}

	return (len);
}

/**
 * count_tokens - Counts number of delimited words
 * @str: string to be searched
 * @del: delimiter character
 *
 * Return: number of words contained within str
 */
int count_tokens(char *str, char *del)
{
	int idx, len = 0, tokens = 0;

	for (idx = 0; *(str + idx); idx++)
		len++;

	for (idx = 0; idx < len; idx++)
	{
		if (*(str + idx) != *del)
		{
			tokens++;
			idx += token_len(str + idx, del);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string
 * @str1: a string
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *str1, char *delim)
{
	char **pntr;
	int idx = 0, tokens, td, alphbts, lm;

	tokens = count_tokens(str1, delim);
	if (tokens == 0)
		return (NULL);

	pntr = malloc(sizeof(char *) * (tokens + 2));
	if (!pntr)
		return (NULL);

	for (td = 0; td < tokens; td++)
	{
		while (str1[idx] == *delim)
			index++;

		alphbts = token_len(str1 + idx, delim);

		pntr[td] = malloc(sizeof(char) * (alphbts + 1));
		if (!pntr[td])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(pntr[idx]);
			free(pntr);
			return (NULL);
		}

		for (lm = 0; lm < alphbts; lm++)
		{
			pntr[td][lm] = str1[idx];
			idx++;
		}

		pntr[td][lm] = '\0';
	}
	pntr[td] = NULL;
	pntr[td + 1] = NULL;

	return (pntr);
}
