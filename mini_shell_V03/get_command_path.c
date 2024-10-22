#include "mini_shell.h"


void 	ft_free_split(char **split)
{
    int i ;

    i = 0; 

    while(split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}


char *check_if_dir(char *cmd_path  )
{
    struct  stat info;

    if (!stat(cmd_path, &info) && !S_ISDIR(info.st_mode))
        return (cmd_path);
    else
    {
        free(cmd_path);
        return NULL;
    }
}

char	*cmd_helper(char *cmd, char *PATH_VARIABLE)
{
	char	*cmd_path;
	char	**potencial_paths;
    int i;

    i = 0;
    potencial_paths = ft_split(PATH_VARIABLE , ":");
	while (potencial_paths[i])
	{
		cmd_path = ft_strjoin(potencial_paths[i], cmd);
		if (!access(cmd_path, X_OK)  )
		{
            ft_free_split(potencial_paths);  
            return check_if_dir(cmd_path  ) ; 
		}
		else
			free(cmd_path);
        i++;
	}
   ft_free_split(potencial_paths);
   return (NULL);
}

char	*get_command_path(char *cmd, char *PATH_VARIABLE)
{
    char     *resp;

	cmd = ft_strjoin("/", cmd);
	resp = cmd_helper(cmd, PATH_VARIABLE);
    free(cmd);
	return (resp);
}

char	*is_command(char *cmd, char **env)
{
	int	i;
    struct  stat info;

	i = 0;
	if (memchr(cmd, '/', strlen(cmd)) )
    {
        if (!access(cmd, X_OK) && !stat(cmd, &info) && !S_ISDIR(info.st_mode))
            return (cmd);
        else 
            return NULL;
    }
	while (env[i])
	{
		if (!strncmp(env[i], "PATH=", 5))
			return (get_command_path(cmd , env[i] + sizeof(char)*5));
		i++;
	}
	return (NULL);
}
