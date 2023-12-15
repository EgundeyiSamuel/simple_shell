#include "samd.h"

/**
 * cd_pd - changes to the parent directory
 *
 * @shell_data: Shell data structure containing relevant information
 *
 * Return: void
 */

void cd_pd(shell_data *shell_data)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *parent_dir;

	/* Get the current working directory */
	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	set_env_var("OLDPWD", cp_pwd, shell_data);

	*directory = shell_data->args[1];

	/* If the directory is . , no change is needed */
	if (_strcmp(".", directory) == 0)
	{
		set_env_var("PWD", cp_pwd, shell_data);
		free(cp_pwd);
		return;
	}

	parent_dir = dirname(cp_pwd);

	/* Change to the parent directory */
	if (chdir(parent_dir) == -1)

	{
		/* Handle the error if changing directory fails */
		error_code(shell_data, 2);
		free(cp_pwd);
		return;
	}

	set_env_var("PWD", parent_dir, shell_data);

	/* Update the status to indicate success */

	shell_data->status = 0;
	free(cp_pwd);
}

/**
 * cd_dr - To change current directory.
 * @shell_data: relevant data
 *
 * Return: 1 success.
 */
int cd_dr(shell_data *shell_data)
{
	char *dr;
	int is_home, ishome1, is_dash;

	dr = shell_data->args[1];

	if (dr)
	{
		is_home = _strcmp("$HOME", dr);
		ishome1 = _strcmp("~", dr);
		is_dash = _strcmp("--", dr);
	}

	/* Check for special directory names */
	if (!dr || !is_home || !ishome1 || !is_dash)
	{
		cd_home(shell_data);
		return (1);
	}

	/* Handle - option */
	if (_strcmp("-", dr) == 0)
	{
		cd_go_back(shell_data);
		return (1);
	}

	/* Handle "." and ".." directories */
	if (_strcmp(".", dr) == 0 || _strcmp("..", dr) == 0)
	{
		cd_pd(shell_data);
		return (1);
	}

	/* Handle other directory paths */
	cd_go(shell_data);

	return (1);
}

/**
 * cd_go - changes to a directory given
 *
 * @shell_data: relevant data
 * Return: void
 */
void cd_go(shell_data *shell_data)
{
	char pwd[PATH_MAX];
	char *dr, *cp_pwd, *cp_dr;

	getcwd(pwd, sizeof(pwd));

	dr = shell_data->args[1];
	if (chdir(dir) == -1)
	{
		error_code(shell_data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env_var("OLDPWD", cp_pwd, shell_data);

	cp_dr = _strdup(dr);
	set_env_var("PWD", cp_dr, shell_data);

	free(cp_pwd);
	free(cp_dr);

	shell_data->status = 0;

	chdir(dr);
}

/**
 * cd_go_back - to change back to the previous directory
 *
 * @shell_data: relevant data(environ)
 * Return: nothing
 */
void cd_go_back(shell_data *shell_data)
{
	char *p_oldpwd, *cp_pwd, *cp_oldpwd;

	cp_pwd = _strdup(getcwd(NULL, 0));
	p_oldpwd = _getenv("OLDPWD", shell_data->_environ);

	if (!p_oldpwd)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env_var("OLDPWD", cp_pwd, shell_data);

	if (chdir(cp_oldpwd) == -1)
		set_env_var("PWD", cp_pwd, shell_data);
	else
		set_env_var("PWD", cp_oldpwd, shell_data);

	write(STDOUT_FILENO, cp_pwd, _strlen(cp_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shell_data->status = 0;

	chdir(cp_pwd);
}

/**
 * cd_home - to change to the home directory
 *
 * @shell_data: relevant data (environ)
 */
void cd_home(shell_data *shell_data)
{
	char *print_pwd, *home;
	char *cp_pwd = _strdup(getcwd(NULL, 0));
	(void) print_pwd;

	home = _getenv("HOME", shell_data->_environ);

	if (!home)
	{
		set_env_var("OLDPWD", cp_pwd, shell_data);
		free(cp_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		error_code(shell_data, 2);
		free(cp_pwd);
		return;
	}

	set_env_var("OLDPWD", cp_pwd, shell_data);
	set_env_var("PWD", home, shell_data);
	free(cp_pwd);
	shell_data->status = 0;
}
