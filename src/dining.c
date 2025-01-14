/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:47:57 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 17:13:37 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	one_philo(t_info *info)
{
	printf(MAGENTA "%ld %d is thinking\n" RESET, get_time()
		- info->start_time, info->philos->id);
	printf(YELLOW "%ld %d has taken a fork\n" RESET, get_time()
		- info->start_time, info->philos->id);
	philo_usleep(info->philos, info->time_to_die);
	printf(CYAN "%ld %d died\n" RESET, get_time()
		- info->start_time, info->philos->id);
}

void	*work(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->last_meal = get_time();
	if (ph->id % 2 == 0)
		philo_usleep(philo, ph->info->time_to_eat - 10);
	while (1)
	{
		if (check_state(ph->info))
			break ;
		think(ph);
		take_forks(philo);
		eat(ph);
		drop_forks(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	start_dining(t_info *info)
{
	int	i;

	info->start_time = get_time();
	if (info->nbr_philo == 1)
	{
		one_philo(info);
		return ;
	}
	i = -1;
	while (++i < info->nbr_philo)
	{
		info->philos[i].last_meal = info->start_time;
		if (pthread_create(&info->thread[i], NULL,
				&work, &info->philos[i]) != 0)
		{
			printf(RED "%s\n" RESET, ERR_CRT);
			return ;
		}
	}
	if (pthread_create(&info->monitor, NULL, &check_deaths, info) != 0)
	{	
		printf(RED "%s %d\n" RESET, ERR_CRT1, info->philos->id);
		return ;
	}
}

void	end_dining(t_info *info)
{
	int	i;

	i = -1;
	if (info->nbr_philo > 1)
	{
		while (++i < info->nbr_philo)
			pthread_join(info->thread[i], NULL);
		pthread_join(info->monitor, NULL);
	}
	while (++i < info->nbr_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].meal_mutex);
	}
	pthread_mutex_destroy(&info->state_mutex);
	if (info->forks)
		free(info->forks);
	if (info->thread)
		free(info->thread);
	if (info->philos)
		free(info->philos);
}
