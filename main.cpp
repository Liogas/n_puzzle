/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/01/29 15:17:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include <unordered_map>
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
		std::cout << "State actuel traite : " << curr.state << std::endl;
		if (curr.state == dest)
		{
			std::cout << "Dest atteind donc on stop" << std::endl;
			break;
		}
		if (curr.distance > distances[curr.state])
		{
			std::cout << "Ignoré car plus petite distance existe" << std::endl;
			continue;
		}
		std::vector<State> neighbors = curr.state.genNeighbors();
		for (State n : neighbors)
		{
			int d = distances[curr.state] + 1;
			auto it = distances.find(n);
			if (it == distances.end() || it->second > d)
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

bool testSolvable(std::vector<std::vector<int>> grid)
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
		for (int i = grid.size() - 1; i >= 0; i++)
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
		if (row % 2 == 0 && nbInvers % 2 == 0)
			return (false);
		if (row % 2 != 0 && nbInvers % 2 != 0)
			return (false);
	}
	if (grid.size() % 2 != 0 && nbInvers % 2 != 0)
		return (false);
	
	return (true);
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

std::vector<std::vector<int>> genFinalGrid(std::vector<std::vector<int>> grid)
{
	std::vector<int> list;

	for (auto &row : grid)
		for (auto val : row)
			list.push_back(val);
	
	std::sort(list.begin(), list.end());
	for (auto val : list)
		std::cout << " " << val << std::endl;

	std::vector<std::vector<int>> g;
	int pos[2] = {0, 0};
	int dep[2] = {0, 1};
	int	limit[4] = {0, (int)grid.size() - 1, 0, (int)grid.size() - 1};

	for (size_t i = 1; i < list.size(); i++)
	{
		g[pos[0]][pos[1]] = list[i];
		if (dep[1] == 1 && pos[1] == limit[3])
		{
			limit[0] += 1;
			dep[1] = 0;
			dep[0] = 1;
		}
		else if (dep[1] == -1 && pos[1] == limit[2])
		{
			limit[1] -= 1;
			dep[1] = 0;
			dep[0] = -1;
		}
		else if (dep[0] == 1 && pos[0] == limit[1])
		{
			limit[3] -= 1;
			dep[1] = 0;
			dep[0] = -1;
		}
		else if (dep[0] == -1 && pos[0] == limit[0])
		{
			limit[2] += 1;
			dep[1] = 0;
			dep[0] = 1;
		}
		pos[0] += dep[0];
		pos[1] += dep[1];
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

	for (auto &row : parsingInfo.grid) {
        for (auto val : row)
			std::cout << " " << val;
		std::cout << std::endl;
    }
	std::cout << std::endl << std::endl;
	for (auto &row : finalGrid) {
        for (auto val : row)
			std::cout << " " << val;
		std::cout << std::endl;
    }


	// State start = {{{ 
	// 	{7, 2, 1}, 
	// 	{4, 6, 0}, 
	// 	{5, 8, 3} 
	// }}};

	// State dest = {{{ 
	// 	{1, 2, 3}, 
	// 	{4, 5, 6}, 
	// 	{7, 8, 0} 
	// }}};

	// if (!testSolvable(start.getValues()))
	// {
	// 	std::cout << "Grille non solvable" << std::endl;
	// 	return (0);
	// }

	// return (algo(start, dest, manhattan));
	return (0);
}