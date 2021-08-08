#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>
# include <pthread.h>

# define LOOP 1
# define RED		"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN	"\x1b[36m"
# define RESET	"\x1b[0m"

typedef struct s_param
{
	long		philos_num;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		loop_eat;
}	t_param;

typedef struct s_philo
{
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*show_msg;
	pthread_mutex_t	die;
	pthread_t		id;
	t_param			*params;
	long			*start;
	long			last_eat_time;
	int				i;
	int				num_of_eat;
}	t_philo;

typedef struct s_all
{
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*show_msg;
	t_philo			*philos;
	t_param			params;
	long			start;
	int				eat_full;
}	t_all;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_parser(char *av[], t_param *prm);
int		ft_isdigit(int c);
void	ft_close();
void	ft_show_msg(t_philo *ph, char *str);
long	ft_get_current_time(void);
void	ft_check_philo_index(t_philo *philo);
void	ft_philo_eat(t_philo *ph);
void	ft_init_forks(t_all *all);
void	ft_init_philosophers(t_all *all);
void	ft_death_check(t_all *all);

#endif