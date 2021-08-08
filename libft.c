#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	z;

	z = 0;
	while (s1[z] != '\0' || s2[z] != '\0')
	{
		if (s1[z] != s2[z])
			return ((unsigned char)s1[z] - (unsigned char)s2[z]);
		z++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

void	ft_close()
{
	ft_putstr_fd(strerror(errno), 2);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
