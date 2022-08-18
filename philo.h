/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:29:29 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/08/18 13:03:13 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PPL   "\x1B[35m"
# define YEL   "\x1B[33m"
# define CYN   "\x1B[36m"
# define GRN   "\x1B[32m"
# define RESET "\x1B[0m"
# define RED   "\x1B[31m"

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_philo
{
	int				philo_id;
	int				fork_left;
	int				fork_right;
	int				last_meal;
	int				n_meals;
	struct s_global	*global;
	pthread_t		threads;
}				t_philo;

typedef struct s_global
{	
	int				full;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				philo_died;
	int				time_init;
	struct s_philo	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
}				t_global;

void		ft_putstr_fd(char *str, int fd);
long		ft_atoi(const char *str);
int			is_digit(int ac, char **av);
t_bool		check_args(int ac, char **av);
t_global	*init_global(t_global *global, int ac, char **av);
t_bool		assign_philo(t_global *global);
t_bool		assign_rules(t_global *global, int ac, char **av);
int			get_time(void);
int			time_diff(int past);
t_bool		init_simul(t_global *global);
t_bool		init_mutexes(t_global *global);
t_bool		init_threads(t_global *global);
void		*action(void *p);
void		check_death(t_global *global);
void		print_action(t_philo *philo, int key);
int			finish_destroy(t_global *global);
void		sleepy_time(t_philo *philo, int time_action);
void		drop_forks(t_philo *philo);
void		pick_up_fork(t_philo *philo);
void		start_eating(t_philo *philo);
void		start_sleeping(t_philo *philo);
void		die(t_global *global);
t_bool		will_philo_die(t_global *global);
void		is_philo_satisfied(t_global *global);
void		*ft_calloc(size_t num, size_t size);
void		ft_bzero(void *s, size_t n);
int			check_simul(t_global *global);
#endif