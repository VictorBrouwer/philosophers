/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:29:14 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 11:05:20 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>

// 					STRUCTS

typedef	struct s_info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_finish;
	int				philo_count;
	int				is_dead;
	unsigned long	start_of_day;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}				t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	int				meals_done;
	unsigned long	time_last_meal;
	t_info			*info;
}				t_philo;

// 					FUNCTIONS
//		MAIN.C
t_info				*init_info(char **argv, int argc);
pthread_mutex_t	*	init_forks(int philo_count);
t_philo				*init_philos(t_info *info);
//		MULTITHREAD.C
int					multi_thread(t_philo *philos);
void				*routine(void *philos_arg);
int					observe(t_philo *philos);
int					join_philos(t_philo *philos);
//		ERROR_HANDLING,C
void				error(const char *str, int errno);
void				ft_putstr_fd(const char *s, int fd);
int					ft_atoi_prot(const char *str);
//		TASKS.C
void				start_eating(t_philo *philo);
void				lock_forks(t_philo *philo);
void				unlock_forks(t_philo *philo);
void				start_sleeping(t_philo *philo);
void				start_thinking(t_philo *philo);
//		DEATH.C
void				check_for_death(t_philo *philo);
void				die(t_philo *philo);
//		TIME.C
unsigned long		get_time_start(void);
unsigned long		get_time(t_philo *philo);
# endif