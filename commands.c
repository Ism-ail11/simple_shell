#include "shell.h"

/**
 * changeDirectory - Changes the current working directory.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: Depends on the condition.
 */

int changeDirectory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnvVariable(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = getEnvVariable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getEnvVariable(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(getEnvVariable(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = getEnvVariable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printError(info, "can't cd to ");
		printString(info->argv[1]), printChar('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", getEnvVariable(info, "PWD="));
		setEnv(info, "PWD", getcwd(buffer, 1024));
	} return (0);
}

/**
 * isCommand - Checks if a path is a command.
 *
 * @info: Pointer to the parameter structure.
 * @path: Path to be checked.
 *
 * Return: Depends on the condition.
 */

int isCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * findBuiltin - Finds a built-in command.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: Depends on the condition.
 */

int findBuiltin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myExit},
		{"env", myEnv},
		{"help", myHelp},
		{"history", myHistory},
		{"setenv", mySetEnv},
		{"unsetenv", myUnsetEnv},
		{"cd", changeDirectory},
		{"alias", myAlias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * findCommand - Finds a command in the path.
 *
 * @info: Pointer to the parameter structure.
 */

void findCommand(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findPath(info, getEnvVariable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		runCommand(info);
	}
	else
	{
		if ((isInteractiveMode(info) || getEnvVariable(info, "PATH=")
			|| info->argv[0][0] == '/') && isCommand(info, info->argv[0]))
			runCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * runCommand - Executes a command.
 *
 * @info: Pointer to the parameter structure.
 */

void runCommand(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printError(info, "Permission denied\n");
		}
	}
}
