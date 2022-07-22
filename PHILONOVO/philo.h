/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:29:29 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/22 15:32:09 by mda-cruz         ###   ########.fr       */
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

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

typedef int t_bool;
#define TRUE 1
#define FALSE 0

typedef struct s_philo
{
	int philo_id;
	int fork_left;
	int fork_right;
	int last_meal;
	int n_meals;
	struct s_global *global;
}				t_philo;

typedef struct s_global
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	int philo_died;
	int time_init;
	struct s_philo	*philo;
	pthread_mutex_t *forks;
}				t_global;



void		ft_putstr_fd(char *str, int fd);
long		ft_atoi(const char *str);
int			is_digit(int ac, char **av);
t_bool		check_args(int ac, char **av);
t_global	*init_global(t_global *global, int ac, char **av);
t_bool		assign_philo(t_global *global);
t_bool		assign_rules(t_global *global, int ac, char **av);
int 		get_time();
int 		time_diff(int past);
#endif