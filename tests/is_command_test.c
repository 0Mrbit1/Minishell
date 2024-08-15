#include "libft.h"
#include <stdio.h>
#include <sys/stat.h>

char	*cmd_helper(char *cmd, char *PATH_VARIABLE)
{
	char	*cmd_path;
	char	**potencial_paths;
    struct  stat info;
    int i;

    i = 0;
    potencial_paths = ft_split(PATH_VARIABLE , ":");
	while (potencial_paths[i])
	{
		cmd_path = ft_strjoin(potencial_paths[i], cmd);
		if (!access(cmd_path, X_OK)  )
		{
            ft_free_split(potencial_paths); 
            if (!stat(cmd_path, &info) && !S_ISDIR(info.st_mode))
            {
                return (cmd_path);
            }
            else
            {
                free(cmd_path);
                return 0;
            }
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
	char	*cmd_path;
    char     *resp;

	cmd = ft_strjoin("/", cmd);
	resp = cmd_helper(cmd, PATH_VARIABLE);
    free(cmd);
	return (resp);
}

char	*is_command(char *cmd, char **envp)
{
	int	i;
    struct  stat info;

	i = 0;
	if (ft_memchr(cmd, '/', ft_strlen(cmd)) )
    {
        if (!access(cmd, X_OK) && !stat(cmd, &info)  && !S_ISDIR(info.st_mode))
        {
            return (cmd);
        }
        else 
            return NULL;
    }

	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (get_command_path(cmd , envp[i] + sizeof(char)*5));
		i++;
	}
	return (NULL);
}