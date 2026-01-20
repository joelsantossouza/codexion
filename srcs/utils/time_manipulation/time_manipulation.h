/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manipulation.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:59:13 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 20:42:58 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_MANIPULATION_H
# define TIME_MANIPULATION_H

# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

uint64_t	timestamp(const uint64_t *new_start);

static inline
uint64_t	millis(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec * 0.001);
}

#endif
