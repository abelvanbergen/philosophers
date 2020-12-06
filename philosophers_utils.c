/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 09:51:44 by avan-ber      #+#    #+#                 */
/*   Updated: 2020/12/06 14:54:56 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_put_unsigned_nbr(unsigned long long nb)
{
	if (nb > 9)
		ft_put_unsigned_nbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}

static int	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	is_nbr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int		simple_atoi(char *nb)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (nb[i] != '\0')
	{
		res += (res * 10) + (nb[i] - '0');
		i++;
	}
	return (res);
}
