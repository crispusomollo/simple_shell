#ifndef _SSHELL_H_
#define _SSHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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

/* Global environemnt usage */
extern char **environ;

/**
 * struct alias_s - the new struct defining the aliases
 * @nm: the name given to the alias
 * @val: the value given to the alias
 * @nxt: the pointer to the other struct alias_a
 */
typedef struct alias_s
{
	char *nm;
	char *val;
	struct alias_s *next;
} alias_t;

/**
 * struct builtin_s - the new struct type defining the built-in commands
 * @nm: the name of the built-in command
 * @fx: the function pointer to the built-in command fx.
 */
typedef struct builtin_s
{
	char *nm;
	int (*fx)(char **par, char **sta);
} builtin_t;

/**
 * struct list_s - the struct type defining a linked list
 * @dct: the directory path
 * @next: the pointer to another struct list_s
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/* Linkedlist Global aliases */
mask_int hist;
mask_char *name;
alias_t *aliases;

/* The Main Helpers */
char *_itoa(int num);
char *get_location(char *cmd);
char **_strtok(char *line, char *del);
int execute(char **par, char **sta);
list_t *get_path_dir(char *pth);
ssize_t _getline(char **linepnr, size_t *nm, FILE *stream);
void *_realloc(void *pnr, unsigned int o_size, unsigned int n_size);
void free_list(list_t *head);

/* The Input Helpers */
int check_args(char **args);
int handle_args(int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
char **replace_aliases(char **args);
char *get_args(char *line, int *exe_ret);
void free_args(char **args, char **front);
void handle_line(char **line, ssize_t read);
void substitute_arg(char **args, int *exe_ret);

/* The String functions */
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int _strspn(char *s, char *accept);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strncat(char *dst, const char *src, size_t n);
char *_strcpy(char *dst, const char *src);
char *_strcat(char *dst, const char *src);
char *_strchr(char *st, char ch);

/* The Built-ins Commands */
int builtin_exit(char **par, char **sta);
int builtin_cd(char **par, __silent char **sta);
int builtin_env(char **par, __silent char **sta);
int builtin_help(char **par, __silent char **sta);
int builtin_alias(char **par, __silent char **sta);
int builtin_setenv(char **par, __silent char **sta);
int builtin_unsetenv(char **par, __silent char **sta);
int (*get_builtin(char *cmd))(char **par, char **sta);

/* The Builtin Helpers */
void free_env(void);
char **_copyenv(void);
char **_getenv(const char *var);

/* The Error Handling */
char *error_1(char **par);
char *error_2_cd(char **par);
char *error_2_exit(char **par);
char *error_2_syntax(char **par);
char *error_126(char **par);
char *error_127(char **par);
char *error_env(char **par);
int create_error(char **par, int err);

/* The Linkedlist Helpers */
void free_list(list_t *hd);
void free_alias_list(alias_t *hd);
list_t *add_node_end(list_t **hd, char *dir);
alias_t *add_alias_end(alias_t **hd, char *nm, char *val);

void help_cd(void);
void help_all(void);
void help_env(void);
void help_help(void);
void help_exit(void);
void help_alias(void);
void help_setenv(void);
void help_history(void);
void help_unsetenv(void);

int file_cmds(char *fpath, int *xret);
#endif /* _SSHELL_H_ */
