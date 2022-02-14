#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	size_t cont;

	cont = 0;
	while (s[cont])
		cont++;
	return (cont);
}

char *ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while(s[i])
	{
		if(s[i] == (unsigned char)c)
			return ((char *)(s+ i));
		i++;
	}
	return (0);
}

char *ft_strjoin(const char *s1, const char *s2)
{
	size_t i;
	char *join;

	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	i = 0;
	while (*s1)
		join[i++] = *s1++;
	while (*s2)
		join[i++] = *s2++;
	join[i] = 0;
	return (join);
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
	char *new;
	char *temp;
	size_t i;

	new = malloc(len + 1);
	if(!new)
		return (0);
	temp = (char *)(s + start);
	i = 0;
	while (*temp && i < len)
		new[i++] = *temp++;
	new[i] = 0;
	return (new);
}

static void find_salt(int fd, char *buff, char **storage)
{
	size_t size;
	char *temp;

	if(!*storage || !ft_strchr(*storage, '\n'))
	{
		size = read(fd, buff, BUFFER_SIZE);
		while (size > 0)
		{
			buff[size] = 0;
			if (!*storage)
				*storage = ft_substr(buff, 0, size);
			else
			{
				temp = *storage;
				*storage = ft_strjoin(*storage, buff);
				free(temp);
			}
			if(ft_strchr(*storage, '\n'))
				break ;
			size = read(fd, buff, BUFFER_SIZE);
		}
	}
	free(buff);
}

char *cute_line(char **storage)
{
	size_t len1;
	size_t len2;
	char *temp;
	char *dest;

	if (!*storage)
		return (0);
	if(!ft_strchr(*storage, '\n'))
	{
		dest = ft_substr(*storage, 0, ft_strlen(*storage));
		free(*storage);
		*storage = 0;
		return (dest);
	}
	len1 = ft_strlen(*storage);
	len2 = ft_strlen(ft_strchr(*storage, '\n'));
	dest = ft_substr(*storage, 0, len1 - len2 + 1);
	temp = *storage;
	*storage = ft_substr(ft_strchr(*storage, '\n'), 1, len2);
	free(temp);
	return (dest);
}

char *get_next_line(int fd)
{
	char *buff;
	static char *storage;

	buff = malloc(BUFFER_SIZE  + 1);
	if (!buff || fd == -1 || BUFFER_SIZE < 1 || read(fd, buff, 0))
	{
		free(buff);
		return (0);
	}
	find_salt(fd, buff, &storage);
	return (cute_line(&storage));
}

