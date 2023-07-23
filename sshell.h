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



