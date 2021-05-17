/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:14:59 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/17 19:47:50 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_philo(t_philo_info* data)
{
	printf("philo +----------------------------+\n");
	printf("number of philosophers: 	%u\n", data->philo.number);
	printf("time to die:			%u\n", data->t_die);
	printf("time to eat:			%u\n", data->t_eat);
	printf("time to sleep:			%u\n", data->t_sleep);
	printf("Must eat:			%i\n", (int)data->must_eat);
	printf("number to eat			%u\n", data->nb_must_eat);
}

unsigned long	get_time_ms()
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 +  time.tv_usec / 1000;
	return (time_ms);
}

int are_all_numbers(char **numbers, int amount)
{
	int i;

	i = 1;
	while (i < amount)
	{
		if (ft_isnumber(numbers[i]) == 0)
			return (error_argument_numbers(i, numbers[i]));
		i++;
	}
	return (0);
}

void	ft_close_all_forks(t_philo_info* info, int index)
{
	int i;
	int	ret;

	i = 0;
	while(i < index)
	{
		ret = pthread_mutex_destroy(&info->forks[i]);
		if (ret != 0)
		{
			pthread_mutex_unlock(&info->forks[i]);
			pthread_mutex_destroy(&info->forks[i]);
		}
		i++;
	}
}

void	ft_alarm(unsigned int time_to_pass)
{
	unsigned long	time_ms;
	unsigned long	update_ms;

	time_ms = get_time_ms();
	while(1)
	{
		usleep(100);
		update_ms = get_time_ms();
		if (update_ms - time_ms > time_to_pass)
		{
			printf("ft_alarm: %lu\n", update_ms - time_ms);
			return ;
		}
	}
	printf("ft_alarm: %lu\n", update_ms - time_ms);
	(void)time_to_pass;
}

void	write_philo_message(char *msg, int philo_nb, unsigned long time_start)
{
	unsigned long	time_ms;
	
	time_ms = get_time_ms();
	printf("%ld %i %s", time_ms - time_start, philo_nb, msg);
}

int	is_other_philo_dead(t_philo_info *info)
{
	pthread_mutex_lock(&info->m_philo_died);
	if (info->philo_died == true)
		return (1);
	pthread_mutex_unlock(&info->m_philo_died);
	return (0);
}

int	is_philo_dead(t_philo_info *info)
{
	unsigned long	time;

	time = get_time_ms();
	if (info->time_last_eat - time > info->t_die)
	{
		pthread_mutex_lock(&info->m_philo_died);
		info->philo_died = true;
		pthread_mutex_unlock(&info->m_philo_died);
		return (1);
	}
	return (0);
}

int	philo_eat(t_philo_info *info)
{
	if (is_other_philo_dead(info) == 1)
		return (1);
	if (is_philo_dead(info) == 1)
		return (1);
	pthread_mutex_lock(&info->forks[info->philo.left_fork]);
	write_philo_message("has taken a fork", info->philo.number, info->time);
		if (is_other_philo_dead(info) == 1)
		return (1);
	if (is_philo_dead(info) == 1)
		return (1);
	pthread_mutex_lock(&info->forks[info->philo.right_fork]);
	write_philo_message("has taken a fork", info->philo.number, info->time);
	if (is_other_philo_dead(info) == 1)
		return (1);
	if (is_philo_dead(info) == 1)
		return (1);
	write_philo_message("is eating", info->philo.number, info->time);
	ft_alarm(info->t_eat);
	pthread_mutex_unlock(&info->forks[info->philo.left_fork]);
	pthread_mutex_unlock(&info->forks[info->philo.right_fork]);
	return (0);
}

int	philo_sleep(t_philo_info *info)
{
	if (is_other_philo_dead(info) == 1)
		return (1);
	if (is_philo_dead(info) == 1)
		return (1);
	ft_alarm(info->t_sleep);
	if (is_other_philo_dead(info) == 1)
		return (1);
	if (is_philo_dead(info) == 1)
		return (1);
	return (0);
}

void	philo_being_philo(void *varg)
{
	int turn;
	int	ret;
	
	t_philo_info *info;
	info = (t_philo_info *)varg;
	if (info->philo.number % 2 == 0)
		usleep(100);
	turn = 0;
	while (info->must_eat == true && turn < info->nb_must_eat)
	{
		ret = philo_eat(info);
		if (ret == 1)
			return ;
		ret = philo_sleep(info);
		if (ret == 1)
			return ;
		write_philo_message("is thinking", info->philo.number, info->time);
	}
	return ;
}

int	philo_info_init(int ac, char **av, t_philo_info* info)
{
	int i;
	int ret;
	struct timeval	time;
	
	if (are_all_numbers(av, ac) == 1)
		return (1);
	info->philo_amount = ft_atoui(av[1]);
	if (info->philo_amount < 2 || info->philo_amount > 200)
		return (error_philo_amount());
	info->t_die = ft_atoui(av[2]);
	if (info->t_die < 60)
		return(error_time_to_low("Time to die"));
	info->t_eat = ft_atoui(av[3]);
	if (info->t_eat < 60)
		return(error_time_to_low("Time to eat"));
	info->t_sleep = ft_atoui(av[4]);
	if (info->t_sleep < 60)
		return(error_time_to_low("Time to sleep"));
	if (ac == 6)
	{
		info->must_eat = true;
		info->nb_must_eat= ft_atoui(av[4]);
		if (info->nb_must_eat == 0)
			return (error_amount_to_eat_zero());
	}
	else
		info->must_eat = false;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_amount);
	if (info->forks == NULL)
		return (error_malloc_failed());
	i = 0;
	while (i < info->philo_amount)
	{
		ret = pthread_mutex_init(&(info->forks[i]), NULL);
		if (ret != 0)
		{
			ft_close_all_forks(info, i);
			free(info->forks);
			return (error_mutex_failed());
		}
		i++;
	}
	ret = pthread_mutex_init(&info->m_philo_died, NULL);
	if (ret != 0)
	{
		ft_close_all_forks(info, i);
		free(info->forks);
		return (error_mutex_failed());
	}
	gettimeofday(&time, NULL);
	info->time = time.tv_sec * 1000 +  time.tv_usec / 1000;
	return (0);
}

int main(int ac, char **av)
{
	t_philo_info	info;
	
	if (ac == 5 || ac == 6)
	{
		if(philo_info_init(ac, av, &info))
			return(1);
		create_philo(&info)
	}
	else
		return(error_argument_amount());
	return (0);
}