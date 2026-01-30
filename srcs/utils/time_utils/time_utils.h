/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:27:27 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/30 17:01:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

static inline
__attribute__((always_inline))
uint64_t	millis(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

static inline
__attribute__((always_inline))
void	set_abstime(struct timespec *abstime, uint64_t duration_ms)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
	{
		*abstime = (struct timespec){0};
		return ;
	}
	abstime->tv_sec = now.tv_sec + duration_ms / 1000;
	abstime->tv_nsec = now.tv_usec * 1000 + (duration_ms % 1000 * 1000000);
	if (abstime->tv_nsec >= 1000000000)
	{
		abstime->tv_sec += abstime->tv_nsec / 1000000000;
		abstime->tv_nsec %= 1000000000;
	}
}

uint64_t	timestamp_ms(uint64_t set_start);

#endif
