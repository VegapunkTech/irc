/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:36:18 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 09:37:45 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
 #define UTILS_HPP

#include <poll.h>
#include <vector>

#include "../include/client.hpp"

typedef std::vector<pollfd>::iterator       pfd_iterator;

void get_client_infos(const char *buffer, Client& cl);

#endif