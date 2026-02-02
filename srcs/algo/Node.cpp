/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:53:02 by glions            #+#    #+#             */
/*   Updated: 2026/02/02 12:39:17 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"

Node::Node(const std::vector<std::vector<int>> &grid, int g, int h):
	_g(g),
	_h(h),
	_f(g + h),
	_grid(grid)
{
	std::cout << "Node default constructor called" << std::endl;
	std::cout << this->_g << this->_h << this->_f << std::endl;
	(void)this->_father;
}


const std::vector<std::vector<int>>	&Node::getGrid() const
{
	return (this->_grid);
}

int	Node::getF() const
{
	return (this->_f);
}



