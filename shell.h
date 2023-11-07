#ifndef _SHELL_H_
#define _SHELL_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/* For Readswrite buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/* For command chain*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


/* 1 if using systems getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0


#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


extern char **environ;


/**
 * struct liststr - Singlys linked list.
 * @num: The number Field.
 * @str: A strings.
 * @next: Points to next node.
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contain pseudo-arguement to pass a function,
 * allowing uniform prototype for functions pointers struct,
 * @arg: A Strings generated from getline contains arguement
 * @argv:An arrays of strings generated from args
 * @path: A strings path for the current commands
 * @argc: The arguments counts
 * @line_count: The error counts
 * @err_num: The errors code for exits()s
 * @linecount_flag: if on count this line of input
 * @fname: The program filenames
 * @env: Linked list locals copy of environs
 * @environ: Customs modified copy of environs from LL envs
 * @history: The history nodes
 * @alias: The alias nodes
 * @env_changed: on if environs was change
 * @status: the returns status of the last exec'd commands
 * @cmd_buf: Address of pointers to cmd_buf, on if chain
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The fd from which to read line inputs
 * @histcount: The history line number counts.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointers to cmd ; chain buffers, for memory mangements */
	int cmd_buf_type; /* CMD_types ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Contains a builtin string and related functions
 * @type: The builtin command flags
 * @func: The function.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* for toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);


/* for toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);


/* for loophsh.c */
int loophsh(char **);


/*for  toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


/* for toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


/* for toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


/* for toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);


/* for toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);


/* for toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


/* for toem_memory.c */
int bfree(void **);


/* for toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


/* for toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);


/* for toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);


/* for toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);


/* for toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);


/* for toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);


/* for toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);


/* for toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);


/* for toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);


/* for toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);


/* for toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


/* for toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
