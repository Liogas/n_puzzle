/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:53:02 by glions            #+#    #+#             */
/*   Updated: 2026/02/09 12:41:07 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"

// PUBLIC //

Node::Node():
	_g(-1),
	_h(-1),
	_f(-1),
	_grid()
{

}


Node::Node(const std::vector<std::vector<int>> &grid, int g, int h):
	_g(g),
	_h(h),
	_f(g + h),
	_grid(grid)
{
	std::cout << "Node default constructor called" << std::endl;
	std::cout << this->_g << ";" << this->_h << ";" << this->_f << std::endl;
}

std::vector<Node>	Node::genNeighbors()
{
	std::vector<Node> neighbors;
	Pos emptySlot = this->getEmptySlot();
	if (emptySlot.y > 0)
		genNeighbor(neighbors, -1, 0);
	if (emptySlot.y < (int)this->_grid.size() - 1) 
		genNeighbor(neighbors, 1, 0);
	if (emptySlot.x > 0) 
		genNeighbor(neighbors, 0, -1);
	if (emptySlot.x < (int)this->_grid[emptySlot.y].size() - 1) 
		genNeighbor(neighbors, 0, 1);
	return (neighbors);
}

bool	Node::operator==(const Node &o) const
{
	return (this->_grid == o.getGrid());
}

bool	Node::operator!=(const Node &o) const
{
	return (this->_grid != o.getGrid());
}

const std::vector<std::vector<int>>	&Node::getGrid() const
{
	return (this->_grid);
}

int	Node::getF() const
{
	return (this->_f);
}

int	Node::getG() const
{
	return (this->_g);
}

int	Node::getH() const
{
	return (this->_h);
}

void	Node::setF(const int &f)
{
	this->_f = f;
}

void	Node::setG(const int &g)
{
	this->_g = g;
}

void	Node::setH(const int &h)
{
	this->_h = h;
}


// PRIVATE //

Pos	Node::getEmptySlot() const
{
	for (size_t i = 0; i < this->_grid.size(); i++)
	{
		for (size_t j = 0; j < this->_grid[i].size(); j++)
		{
			if (this->_grid[i][j] == 0)
				return (Pos{.y= (int)i, .x= (int)j});
		}
	}
	return (Pos{.y= -1, .x= -1});
}

void	Node::genNeighbor(std::vector<Node> &n, int dirY, int dirX)
{
	Node newState = *this;
	Pos	emptySlot = newState.getEmptySlot();
	std::swap(newState._grid[emptySlot.y][emptySlot.x],
		newState._grid[emptySlot.y + dirY][emptySlot.x + dirX]);
	n.push_back(newState);
}


std::ostream &operator<<(std::ostream &os, const Node &node)
{
	for (size_t i = 0; i < node.getGrid().size(); i++)
	{
		for (size_t j = 0; j < node.getGrid()[i].size(); j++)
		{
			os << " " << node.getGrid()[i][j];
		}
		os << std::endl;
	}
	return (os);
}





