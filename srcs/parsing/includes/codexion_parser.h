/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/01 18:50:02 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_PARSER_H
# define CODEXION_PARSER_H

# include "errors.h"

# ifndef MAX_CODERS
#  define MAX_CODERS 200
# endif

# if MAX_CODERS < 0 || MAX_CODERS > 2147483647
#  error "MAX_CODERS must be a positive integer!"
# endif

typedef struct s_codexion_config t_codexion_config;

enum e_exit_status	codexion_parser(t_codexion_config *config, int argc, char **argv);

#endif
