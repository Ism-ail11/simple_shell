#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define readBuf_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USEgetLine 0
#define USE_STRTOK 0
#define HIST_FILE ".shell_history"
#define HIST_MAX 4096
#define INFO_INIT {\
	NULL, NULL, NULL, \
	0, 0, 0, \
	0, NULL, NULL, \
	NULL, NULL, NULL, \
	0, 0, NULL, \
	0, 0, 0 \
}


extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int shellLoop(info_t *, char **);
int findBuiltin(info_t *);
void findCommand(info_t *);
void runCommand(info_t *info);
int isCommand(info_t *, char *);
char *duplicateChars(char *, int, int);
char *findPath(info_t *, char *, char *);
int loophsh(char **);
void printString(char *);
int printChar(char);
int printCharToFD(char c, int fd);
int printStringToFD(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *startsWith(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strDuplicate(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **splitString(char *, char *);
char *_memset(char *, char, unsigned int);
void freeStringArray(char **);
void *reallocateMemory(void *, unsigned int, unsigned int);
int freePointer(void **);
int isInteractiveMode(info_t *);
int isDelimiter(char, char *);
int _isalpha(int);
int convertStringToInt(char *);
int errAtoi(char *);
void printError(info_t *, char *);
int printDecimal(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);
int myExit(info_t *);
int changeDirectory(info_t *info);
int myHelp(info_t *);
int myHistory(info_t *);
int myAlias(info_t *);
ssize_t getInput(info_t *);
int getLine(info_t *, char **, size_t *);
void sigintHandler(int);
void clearInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);
char *getEnvVariable(info_t *, const char *);
int myEnv(info_t *);
int mySetEnv(info_t *);
int myUnsetEnv(info_t *);
int envList(info_t *);
char **getEnviron(info_t *);
int unsetEnv(info_t *, char *);
int setEnv(info_t *, char *, char *);
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);
list_t *addNode(list_t **, const char *, int);
list_t *endNode(list_t **, const char *, int);
size_t printListStr(const list_t *);
int deleteNode(list_t **, unsigned int);
ssize_t inputBuf(info_t *info, char **buf, size_t *len);
void freeLinkedList(list_t **);
size_t listLen(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);
int isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);
char **_splitString(char *str, char d);

#endif
