/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:05:22 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 17:14:50 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h> 
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

// error messages
# define ERR_INP "Wrong input"
# define ERR_MAL "Malloc error"
# define ERR_PHI "You need at least one philosopher but max 200"
# define ERR_EAT "Philo needs to eat at least ones"
# define ERR_FORK "Mutex initialization error"
# define ERR_CRT  "Failed to create thread for philosopher"
# define ERR_STA "Failed to initialize state mutex"
# define ERR_MMX "Failed to initialize meal mutex for philosopher"
# define ERR_CRT1 "Failed to create monitor thread for philosopher"
# define ERR_DEA "Failed to initialize dead print mutex"
# define ERR_GTM "Error in func. gettimeofday"
# define ERR_FMX "Failed to initialize food mutex for philosopher"
# define ERR_INT "Input values must be only numbers within an positive int"

// colours
# define RED "\33[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define YELLOW "\033[0;33m"
# define CYAN    "\033[0;36m"
# define RESET   "\033[0m"

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_info	*info;		
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_info
{
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				has_to_eat;
	long			start_time;
	bool			dead;
	bool			dead_prt;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	state_mutex;
	pthread_t		monitor;
}	t_info;

// initialization functions
int		init_info(int argc, char **argv, t_info *info);
int		init_more_info(int argc, char **argv, t_info *info);
int		init_thp(t_info *info);
int		prep_philo(t_info *info);
void	init_philos(t_info *info);

// utils
long	get_time(void);
int		check_args(int argc, char **argv);
int		ft_atoi(char *str);
int		overflow_check(char *str);
void	*work(void *philo);
void	*check_deaths(void *void_info);
int		all_philosophers_ate_enough(t_info *info);
int		philo_usleep(t_philo *philo, int time_in_ms);
int		atoi_check(char *str);
int		check_if_died(t_info *info);
int		check_state(t_info *info);
int		check_philo_death(t_philo *ph, t_info *info);
void	add_finish_count(t_info *info);

// actions
void	start_dining(t_info *info);
void	think(t_philo *philo);
void	grab_a_fork(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	drop_forks(t_philo *philo);
void	sleeping(t_philo *philo);
void	end_dining(t_info *info);
void	one_philo(t_info *info);

#endif