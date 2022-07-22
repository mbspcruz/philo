/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:19:38 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 20:41:52 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#define PPL   "\x1B[35m"
#define YEL   "\x1B[33m"
#define CYN   "\x1B[36m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_data
{
	int n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	int	philo_died;
	pthread_mutex_t *forks;
	pthread_mutex_t dead_lock;
	pthread_mutex_t eat_lock;
	int	init_time;
	int				meals;
	struct s_philo			*philo;  
}				t_data;

typedef	struct s_philo
{
	int		philo_id;
	int		n_meals;
	pthread_t thread;
	int		left_fork;
	int 	right_fork;
	int		last_meal;
	struct s_data	*data;
}				t_philo;

t_data			*setup_args(int ac, char **av, t_data *data);
int				is_digit(int ac, char **av);
t_data			*init_args(int ac, char ** av, t_data *data);
int				valid_args(int ac, char **av);
t_philo			*setup_philo(t_data *data);
int				setup_mutex(t_data *data);
int				start_sim(t_data *data);
void			*action(void *p);
int				get_time();
void			ft_putstr_fd(char *str, int fd);
long			ft_atoi(const char *str);
void			sleepy_time(int time);
int				check_death(t_philo *philo);
int	will_die(t_philo *philo);
int				time_of_death(t_philo *philo);
void			start_dying(t_philo *philo);
int				philo_think(t_philo *philo);
int				philo_sleep(t_philo *philo);
int 			let_go_forks(t_philo *philo);
int				philo_eat(t_philo *philo);
int				pick_up_fork(t_philo *philo);
void			free_clean(t_data *data);
void print_status(t_philo *philo, int key, int time);
int	time_diff(int past, int current);
#endif