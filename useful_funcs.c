/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:47:40 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/27 00:03:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	msg_exit : a printf for crashing cleanly.
**	USAGE : msg_exit("error %[d, s]...", memory)
**		%s = string (char*)
**		%d = int
**	When %[...] is read,
**	 msg_exit will interpret memory as pointing to the specified datatype.
*/

void	msg_exit(char *msg, void *data)
{
	size_t	len;
	char	*var;

	if (msg)
	{
		len = 0;
		while (msg[len] && msg[len] != '%')
			++len;
		write(2, (void *)msg, len);
		if (msg[len++] == '%')
		{
			if (msg[len] == 'd')
				var = ft_itoa(*(int*)data);
			else if (msg[len] == 's')
				var = (char*)data;
			else
				msg_exit(&msg[len], data);
			write(2, var, ft_strlen(var));
			msg_exit(&msg[len] + 1, 0);
		}
		write(2, "\n", 1);
	}
	write(1, "error\n", 6);
	exit(EXIT_FAILURE);
}

void	chaos(void *fate)
{
	if (fate == NULL)
		msg_exit("Doom is uppon us.", 0);
}
