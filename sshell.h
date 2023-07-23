#ifndef _SSHELL_H_
#define _SSHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcnt1.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define END_OF_FILE -2
#define EXIT -3

#define __home __attribute__((weak))
#define __silent __attribute__((__unused__))
#define END '\0'

typedef int mask_int;
typedef char mask_char;

#undef ifs
#undef fors
#undef elses

#define ifs if
#define fors for
#define elses else

extern char **environ;

/**
 * struct alias_a - the new struct defining the aliases
 * @nm: the name given to the alias
 * @val: the val given to the alias
 * @nxt: pointer to the other struct alias
 */
typedef struct alias_a
{
	char *nm;
	char *val;
	struct alias_a *nxt;
} alias_a;


