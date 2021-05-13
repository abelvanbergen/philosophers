/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:36:54 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/12 22:56:55 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int				ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int				ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
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
