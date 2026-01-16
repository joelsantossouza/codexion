/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:58:30 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/16 09:37:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_ROUTINE_H
# define CODER_ROUTINE_H

# include <stdint.h>
# include <pthread.h>

# define TAKEN_DONGLE_MSG	"Has taken 1 dongle"
# define COMPILING_MSG		"Compiling"
# define DEBUGGING_MSG		"Debugging"
# define REFACTORING_MSG	"Refactoring"

int		wait_to_compile(uint8_t *coder_state, pthread_mutex_t *mutex, uint32_t *time_left);

#endif
