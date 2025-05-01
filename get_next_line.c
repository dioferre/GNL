/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:10:48 by dioferre          #+#    #+#             */
/*   Updated: 2024/06/18 10:01:08 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)

{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*get_read(int fd, char *backup)
{
	char	*buff;
	int		check_read;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	check_read = 1;
	while (!(ft_strchr(backup, '\n')) && check_read != 0)
	{
		check_read = read(fd, buff, BUFFER_SIZE);
		if (check_read <= 0)
		{
			if (backup)
				return (free(buff), backup);
			return (free (buff), free (backup), NULL);
		}
		buff[check_read] = 0;
		backup = ft_strjoin(backup, buff);
	}
	free (buff);
	return (backup);
}

char	*current_line(char *backup)
{
	char	*line;
	int		i;

	i = 0;
	if (!backup || backup[0] == 0)
		return (NULL);
	while (backup[i] != '\n' && backup[i])
		i++;
	if (backup[i] == '\n')
		i++;
	line = ft_substr(backup, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*next_line(char *backup)
{
	char	*result;
	int		i;

	i = 0;
	if (!backup || backup[0] == 0)
		return (NULL);
	while (backup[i] != '\n' && backup[i])
		i++;
	if (backup[i] == '\n')
		i++;
	result = ft_substr(backup, i, ft_strlen(backup) - i);
	free (backup);
	if (result[0] == 0)
	{
		free (result);
		return (NULL);
	}
	return (result);
}

char	*get_next_line(int fd)

{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = get_read(fd, backup);
	if (!backup || backup == NULL)
		return (NULL);
	line = current_line(backup);
	backup = next_line(backup);
	return (line);
}
/*
int	main()

{
	int		fd;
	char	*line;

	int	i = 0;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close (fd);
	return (0);
}
*/
