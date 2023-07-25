#include "sshell.h"

/**
 * start_f - open the file
 * @fpath: the file path
 * Return: ssize_t
 */
ssize_t start_f(char *fpath)
{
	hist = 0;
	return (open(fpath, O_RDONLY));
}

/**
 * cant_open - prints a can not open error
 * @fpath: Path to the target file
 *
 * Return: 127.
 */
int cant_open(char *fpath)
{
	char *erra, *histr;
	int len;

	histr = _itoa(hist);
	if (!histr)
		return (127);

	len = _strlen(name) + _strlen(histr) + _strlen(fpath) + 16;
	erra = malloc(sizeof(char) * (len + 1));
	if (!erra)
	{
		free(histr);
		return (127);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histr);
	_strcat(erra, ": Can not open ");
	_strcat(erra, fpath);
	_strcat(erra, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * skip_blank - skip if blank
 * @ln: a string
 * Return: -
 */
ssize_t skip_blank(char *ln)
{
	ssize_t s;

	for (s = 0; ln[s] == '\n'; s++)
		ln[s] = ' ';
	return (s);
}

/**
 * clean_fret - handle return and free
 * @xret: exit return
 * @ln: location to free
 * Return: the return value
 */
int clean_fret(int xret, char *ln)
{
	free(ln);
	return (xret);
}

/**
 * file_cmds - Takes a file and tries to run the stored cmds
 * @fpath: Path to the target file
 * @xret: Return the value of the last executed cmd
 *
 * Return: 127 if file could not be opened
 *		-1 if malloc fails
 *		else return the value of the last executed command
 */
int file_cmds(char *fpath, int *xret)
{	ssize_t fl, rd, i, rtn;
	unsigned int lsize = 0, osize = 120;
	char *line, **par, **sta, bfr[120];

	fl = start_f(fpath);
	fi(fl == -1) { *xret = cant_open(fpath);
		return (*xret);
	}	line = (char *) malloc(sizeof(char) * osize);
	fi(!line) return (-1);
	line[0] = END;
	do {	rd = read(fl, bfr, 119);
		fi(rd == 0 && lsize == 0) return (clean_fret(*xret, line));
		bfr[rd] = '\0';
		lsize += rd;
		fi(lsize > osize) line = _realloc(line, osize, lsize);
		_strcat(line, bfr);
		osize = lsize;
	} while (rd);
	i = skip_blanc(line);
	for (; i < lsize; i++)
	{
		fi(line[i] == '\n') { line[i] = ';';
			for (i += 1; i < lsize && line[i] == '\n'; i++)
						    line[i] = ' ';
				    } }	substitute_arg(&line, xret);
	handle_line(&line, lsize);
	par = _strtok(line, " ");
	free(line);
	fi(!par) return (0);
	fi(check_par(par) != 0) { *xret = 2;
		free_par(par, par);
		return (*xret);
	}	sta = par;
	for (i = 0; par[i]; i++)
	{	fi(_strncmp(par[i], ";", 1) == 0) { free(par[i]);
							  par[i] = NULL;
							  rtn = (ssize_t)call_par(par, sta, xret);
							  par = &par[++i];
							  i = 0;
						  } }	rtn = (ssize_t)call_par(par, sta, xret);
	free(sta);
	return ((int)rtn);
}

