/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:29:14 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/13 13:28:54 by vbrouwer         ###   ########.fr       */
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
typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_finish;
	int				meals_done;
	int				is_dead;
	int				time_last_meal;
}				t_philo;

typedef	struct s_info
{
	int				philo_count;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_info;

// 					FUNCTIONS
//		MAIN.C
t_philo				*init_philos(int philos_count, pthread_mutex_t	*forks, char **argv, int argc);
void				init_info(char **argv, int argc, t_info *info);
int					ft_atoi_prot(const char *str);
//		MULTITHREAD.C
void				multi_thread(t_info *info);
void				*routine(void *philos_arg);
void				start_sleeping(t_philo *philo);
void				start_thinking(t_philo *philo);
//		ERROR_HANDLING,C
void				error(const char *str, int errno);
void				ft_putstr_fd(const char *s, int fd);
//		EATING.C
void				start_eating(t_philo *philo);
void				lock_forks(t_philo *philo);
void				unlock_forks(t_philo *philo);
//		DEATH.C
void				check_for_death(t_philo *philo);
void				die(t_philo *philo);

# endif