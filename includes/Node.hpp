/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:02:04 by glions            #+#    #+#             */
/*   Updated: 2026/02/12 14:29:53 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <queue>
# include <iostream>
# include <unordered_set>

struct Pos
{
	int	y;
	int	x;
};

class Node
{
	public:
		// constructor //
		Node();
		Node(const std::vector<std::vector<int>> &grid, int g, int h);
		// getters //
		int									getF() const;
		int									getH() const;
		int									getG() const;
		const std::vector<std::vector<int>>	&getGrid() const;
		// setters //
		void	setF(const int &f);
		void	setH(const int &h);
		void	setG(const int &g);
		void	setValueGrid(int y, int x, int val);
		// overrides //
		bool operator==(const Node &o) const;
		bool operator!=(const Node &o) const;
		// methods //
		std::vector<Node>	genNeighbors();
		Node				project(std::unordered_set<int> &patterns) const;
	private:
		// props //
		int								_g;
		int								_h;
		int								_f;
		std::vector<std::vector<int>>	_grid;
		// methods //
		void	genNeighbor(std::vector<Node> &n,
					int dirY, int dirX);
		Pos		getEmptySlot() const;
};

std::ostream &operator<<(std::ostream &os, const Node &node);

struct NodeHash
{
	std::size_t operator()(const Node &n) const
	{
		size_t h = 0;
		for (size_t i = 0; i < n.getGrid().size(); i++)
		{
			for (size_t j = 0; j < n.getGrid()[i].size(); j++)
				h = h * 31 + std::hash<int>()(n.getGrid()[i][j]);
		}
		return (h);
	}
};

struct NodeCmp
{
	bool operator()(const Node &a, const Node &b) const
	{
		return (a.getF() > b.getF());
	}
};

#endif