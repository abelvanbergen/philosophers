#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

unsigned long	get_time_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

void	ft_sleep(unsigned int time_to_pass)
{
	unsigned long	time_ms;
	unsigned long	update_ms;

	time_ms = get_time_ms();
	while (1)
	{
		usleep(100);
		update_ms = get_time_ms();
		if (update_ms - time_ms >= time_to_pass)
			return ;
	}
	(void)time_to_pass;
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

unsigned int	ft_atoui(char *str)
{
	unsigned int	ret;
	int				i;

	ret = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret);
}
