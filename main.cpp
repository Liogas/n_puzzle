/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/01/30 12:42:39 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <algorithm>

int		calc(int y, int x, int v, const State &goal)
{
	for (size_t i = 0; i < goal.getValues().size(); i++)
	{
		for(size_t j = 0; j < goal.getValues()[i].size(); j++)
		{
			if (goal.getValues()[i][j] == v)
				return (abs(y - (int)i) + abs(x - (int)j));
		}
	}
	return (0);
}

int	manhattan(const State &current, const State &goal)
{
	int	estimation = 0;
	for (size_t i = 0; i < current.getValues().size(); i++)
	{
		for (size_t j = 0; j < current.getValues()[i].size(); j++)
		{
			if (current.getValues()[i][j] != 0)
				estimation += calc(i, j, current.getValues()[i][j], goal);	
		}
	}
	return (estimation);
}

int	algo(State &start, State &dest, int heur(const State&, const State&))
{
	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;
	std::unordered_set<State, StateHash> closed;
	int	ddd = 0;

	distances[start] = 0;
	tmp.push( Elem {
		.distance= 0,
		.estimate=heur(start, dest),
		.state= start
	});
	while (!tmp.empty())
	{
		Elem curr = tmp.top();
		tmp.pop();
		if (closed.find(curr.state) != closed.end())
		{
			std::cout << "Deja traite (" << ddd++ << ")" << std::endl;
    		continue;
		}
		std::cout << "Pas encore traite" << std::endl;

		closed.insert(curr.state);
		// std::cout << "State actuel traite : " << curr.state << std::endl;
		if (curr.state == dest)
		{
			std::cout << "Dest atteind donc on stop" << std::endl;
			break;
		}
		// if (curr.distance > distances[curr.state])
		// {
		// 	std::cout << "Ignoré car plus petite distance existe" << std::endl;
		// 	continue;
		// }
		std::vector<State> neighbors = curr.state.genNeighbors();
		for (State n : neighbors)
		{
			if (closed.find(n) != closed.end())
				continue ;
			int d = distances[curr.state] + 1;
			if (distances.find(n) == distances.end() || d < distances[n])
			{
				distances[n] = d;
				fathers.erase(n);
				fathers.emplace(n, curr.state);
				tmp.push(Elem({
					.distance= distances[n],
					.estimate=heur(n, dest),
					.state= n
				}));
			}
		}
	}
	std::cout << "Start : " << std::endl << start << std::endl;
	std::cout << "Dest : " << std::endl;
	std::cout << "Start : " << std::endl << dest << std::endl;
	std::cout << "Distance : " << distances[dest] << std::endl;
	std::cout << "Chemin parcouru : " << std::endl;
	std::cout << dest << std::endl;
	int i = 0;
	std::cout << std::endl;
	State curr = dest;
	while (curr != start)
	{
		curr = fathers.at(curr);
		std::cout << curr << std::endl;
		i++;
		std::cout << std::endl;
		std::cout << i << std::endl;
		std::cout << std::endl;
	}
	return (0);
}

bool parity(std::vector<std::vector<int>> grid)
{
	std::vector<int> 	list;
	int				 	row = 0;
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != 0)
				list.push_back(grid[i][j]);
		}
	}
	int	nbInvers = 0;
	for (size_t i = 0; i < list.size(); i++)
	{
		for (size_t j = i + 1; j < list.size(); j++)
		{
			if (list[i] > list[j])
				nbInvers++;
		}
	}
	if (grid.size() % 2 == 0)
	{
		for (int i = grid.size() - 1; i >= 0; i--)
		{
			row++;
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] == 0)
				{
					i = -1;
					break ;
				}
			}
		}
	}
	if (grid.size() % 2 != 0)
		return (nbInvers % 2);
	return ((nbInvers + row) % 2);
}

bool parsing(char *pathFile, ParsingInfo &info)
{
	std::ifstream file(pathFile);
	if (!file.is_open())
		return (false);
	std::string	line;
	std::getline(file, line);
	if (line.size() == 0)
		return (file.close(), false);
	if (line == "# This puzzle is solvable")
		info.solvable = true;
	else if (line == "# This puzzle is unsolvable")
		info.solvable = false;
	else
		return (file.close(), false);
	std::getline(file, line);
	if (line.size() == 0)
		return (false);
	std::istringstream iss(line);
	if (!(iss >> info.size))
		return (file.close(), false);
	char test;
	if (iss >> test)
		return (file.close(), false);
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::vector<int> row;
		int	n;
		while (ss >> n)
			row.push_back(n);
		info.grid.push_back(row);
	}
	file.close();
	if ((int)info.grid.size() != info.size)
		return (false);
	std::vector<int> mem;
	for (auto &row : info.grid) {
        for (auto val : row)
		{
			auto it = std::find(mem.begin(), mem.end(), val);
			if (it != mem.end())
				return (false);
			mem.push_back(val);
		}
    }
	auto it = std::find(mem.begin(), mem.end(), 0);
	if (it == mem.end())
		return (false);
	return (true);
}

std::vector<std::vector<int>> genFinalGrid(std::vector<std::vector<int>> &grid)
{
	int	n = grid.size();
	std::vector<int> values;
	std::vector<std::vector<int>> g(n, std::vector<int>(n, -1));

	for (const auto &row : grid)
		for (int val : row)
		{
			if (val != 0)
				values.push_back(val);
		}
	std::sort(values.begin(), values.end());
	values.push_back(0);
	int	dir[4] = {0, n - 1, 0, n - 1};
	int	idx = 0;
	while (dir[0] <= dir[1] && dir[2] <= dir[3])
	{
		for (int x = dir[2]; x <= dir[3]; x++)
			g[dir[0]][x] = values[idx++];
		dir[0]++;
		for (int y = dir[0]; y <= dir[1]; y++)
			g[y][dir[3]] = values[idx++];
		dir[3]--;
		for (int x = dir[3]; x >= dir[2]; x--)
			g[dir[1]][x] = values[idx++];
		dir[1]--;
		for (int y = dir[1]; y >= dir[0]; y--)
			g[y][dir[2]] = values[idx++];
		dir[2]++;
	}
	return (g);
}

int	main(int ac, char **av)
{
	ParsingInfo	parsingInfo;
	if (ac != 2)
	{
		std::cout << "Necessite un fichier d'entree contenant la grille" << std::endl;
		return (1);
	}
	
	if (!parsing(av[1], parsingInfo))
	{
		std::cerr << "Fichier non conforme : " << av[1] << std::endl;
		return (1);
	}

	std::vector<std::vector<int>> finalGrid = genFinalGrid(parsingInfo.grid);

	State start(parsingInfo.grid);
	State dest(finalGrid);

	for (auto &row : start.getValues()) {
        for (auto val : row)
			std::cout << " " << val;
		std::cout << std::endl;
    }
	std::cout << std::endl << std::endl;
	for (auto &row : dest.getValues()) {
        for (auto val : row)
			std::cout << " " << val;
		std::cout << std::endl;
    }

	if (parity(start.getValues()) != parity(dest.getValues()))
	{
		std::cout << "Grille non solvable" << std::endl;
		return (0);
	}

	return (algo(start, dest, manhattan));
	return (0);
}