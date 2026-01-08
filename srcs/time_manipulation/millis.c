/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   millis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:33:32 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/08 17:45:44 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

size_t	millis(void)
{
	static struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec * 0.001);
}
