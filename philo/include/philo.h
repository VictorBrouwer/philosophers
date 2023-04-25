/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:29:14 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/25 16:02:07 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERROR 1
# define SUCCES 0

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <stdbool.h>

// 					STRUCTS

typedef struct s_info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_finish;
	int				philo_count;
	int				full_philo_count;
	unsigned long	start_of_day;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	full_philo_mutex;
	bool			is_dead;
	pthread_mutex_t	start_mutex;
}				t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meals_mutex;
	int				meals_done;
	unsigned long	time_last_meal;
	t_info			*info;
}				t_philo;

// 					FUNCTIONS
//		MAIN.C
t_info				*init_info(char **argv, int argc);
pthread_mutex_t		*init_forks(int philo_count);
t_philo				*init_philos(t_info *info);
//		MULTITHREAD.C
int					multi_thread(t_philo *philos);
int					observe(t_philo *philos);
int					join_philos(t_philo *philos);
//		ERROR_HANDLING,C
void				ft_putstr_fd(const char *s, int fd);
int					ft_atoi_prot(const char *str);
int					check_args(char **argv, int argc);
//		TASKS.C
void				*routine(void *philos_arg);
void				uneven_group(t_philo *philo);
void				even_group(t_philo *philo);
int					print_action(t_philo *philo, char *action);
//		DEATH.C
int					check_for_eol(t_philo *philo);
void				die(t_philo *philo);
int					check_for_starvation(t_philo *philo);
int					check_full_philos(t_philo *philo);
//		TIME.C
unsigned long		get_time_start(void);
unsigned long		get_time(t_philo *philo);
//		SLEEP.C
int					start_sleeping(t_philo *philo, int time);
//		EAT.C
int					start_eating(t_philo *philo);
int					take_forks(t_philo *philo);
void				update_meals(t_philo *philo);

#endif