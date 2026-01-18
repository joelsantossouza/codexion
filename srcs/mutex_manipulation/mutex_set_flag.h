/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set_flag.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:00:55 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/15 11:12:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_SET_FLAG_H
# define MUTEX_SET_FLAG_H

# include <stdint.h>
# include <pthread.h>

static inline
void	mutex_set_flag(uint8_t *flags, uint8_t set, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*flags |= set;
	pthread_mutex_unlock(mutex);
}

#endif
