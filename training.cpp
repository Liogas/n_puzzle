/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:35:39 by glions            #+#    #+#             */
/*   Updated: 2026/01/23 11:31:14 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unordered_map>
#include <iostream>
#include <queue>
#include <array>

void	exo1()
{
	std::unordered_map<std::string, int> fruits;

	fruits["pommes"] = 5;
	fruits["bananes"] = 2;
	fruits["cerises"] = 3;

	std::cout << "Nombre de pommes -> " << fruits["pommes"] << std::endl;

	for (auto& pair : fruits)
		std::cout << pair.first << " -> " << pair.second << std::endl;

	std::string test = "poires";
	std::cout << test;
	if (fruits.find(test) != fruits.end())
		std::cout << " est present" << std::endl;
	else
		std::cout << " n'est pas present" << std::endl;
}

void	exo2()
{
	std::unordered_map<char, int> letters;
	std::string string = "aaabbccccdddddd";

	for (char c : string)
		letters[c]++;

	for (std::pair<const char, int>& pair: letters)
		std::cout << pair.first << " -> " << pair.second << std::endl;
}

void	exo3()
{
	struct Point
	{
		int	x;
		int	y;

		bool operator==(const Point& other) const
		{
			return (x == other.x && y == other.y);
		}
	};

	struct PointHash
	{
		std::size_t operator()(const Point &p) const
		{
			return (std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1));
		}
	};

	std::unordered_map<Point, std::string, PointHash> points;
	points[{0, 0}] = "origine";
	points[{1, 2}] = "point A";
	points[{3, 5}] = "point B";

	for (std::pair<const Point, std::string>& pair : points)
		std::cout << "[" << pair.first.x << ";" << pair.first.y << "]" << " -> " << pair.second << std::endl;
}

void	exo4()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	std::unordered_map<State, int, StateHash> states;
	int tab[] = {1 ,2, 3, 2, 1, 4, 3, 3};
	for (int i : tab)
	{
		states[State{i}]++;
	}

	for (std::pair<const State, int>& pair : states)
	{
		std::cout << pair.first.value << " -> " << pair.second << std::endl;
	}
}

void	exo5()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	std::unordered_map<State, bool, StateHash> visited;
	
	std::queue<State> tmp;
	tmp.push(State{2});
	while (!tmp.empty())
	{
		State val = tmp.front();
		std::cout << "Traitement de " << val.value << std::endl;
		if (visited.find(val) == visited.end())
		{
			std::cout << val.value << " est maintenant visite" << std::endl;
			visited[val] = true;
			if (val.value > 0 && visited.find(State{val.value - 1}) == visited.end())
			{
				tmp.push(State{val.value - 1});
				std::cout << "Nouveau voisin -> " << val.value - 1 << std::endl;
			}
			if (val.value < 5 && visited.find(State{val.value + 1}) == visited.end())
			{
				std::cout << "Nouveau voisin -> " << val.value + 1 << std::endl;
				tmp.push({val.value + 1});
			}
		}
		tmp.pop();
	}
}

void exo6()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	std::unordered_map<State, int, StateHash> distances;
	
	std::queue<State> tmp;
	State start = State{4};
	tmp.push(start);
	distances[start] = 0;
	State dest = State{3};
	while (!tmp.empty())
	{
		State val = tmp.front();
		std::cout << "Traitement de " << val.value << std::endl;
		if (val.value > 0 && distances.find(State{val.value - 1}) == distances.end())
		{
			tmp.push(State{val.value - 1});
			distances[State{val.value - 1}] = distances[val] + 1;
			std::cout << "Nouveau voisin -> " << val.value - 1 << " distance -> " << distances[State{val.value - 1}] << std::endl;
		}
		if (val.value < 5 && distances.find(State{val.value + 1}) == distances.end())
		{
			tmp.push({val.value + 1});
			distances[State{val.value + 1}] = distances[val] + 1;
			std::cout << "Nouveau voisin -> " << val.value + 1 << " distance -> " << distances[State{val.value + 1}] << std::endl;
		}
		tmp.pop();
	}
	std::cout << "Distance entre " << start.value << " et " << dest.value << " -> " << distances[dest] << std::endl; 
}

void	exo7()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}

		bool operator!=(const State &other) const
		{
			return (value != other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	struct	Elem
	{
		int		distance;
		State 	state;
	};

	struct Cmp
	{
		bool operator()(const Elem &a, const Elem &b) const
		{
			return (a.distance > b.distance);
		}
	};

	std::unordered_map<State, std::vector<std::pair<State, int>>, StateHash> graph;
	graph[State{1}] = {{State{2}, 2}, {State{3}, 5}, {State{4}, 1}};
	graph[State{2}] = {{State{1}, 2}, {State{5}, 2}, {State{6}, 4}};
	graph[State{3}] = {{State{1}, 5}, {State{6}, 1}};
	graph[State{4}] = {{State{1}, 1}, {State{6}, 7}};
	graph[State{5}] = {{State{2}, 2}, {State{7}, 3}};
	graph[State{6}] = {{State{2}, 4}, {State{3}, 1}, {State{4}, 7}, {State{7}, 2}};
	graph[State{7}] = {{State{5}, 3}, {State{6}, 2}, {State{8}, 1}};
	graph[State{8}] = {{State{7}, 1}};
	
	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;

	State start = State{1};
	tmp.push(Elem{.distance= 0, .state= start});
	distances[start] = 0;
	State dest = State{8};
	while (!tmp.empty())
	{
		Elem val = tmp.top();
		tmp.pop();
		if (val.state == dest)
		{
			std::cout << "Dest atteind donc on stop" << std::endl;
			break;
		}
		if (val.distance > distances[val.state])
		{
			std::cout << "Distance connue plus petite donc on ignore" << std::endl;
			continue;
		}
		std::cout << "Traitement de " << val.state.value << std::endl;
		auto neigh = graph.find(val.state);
		if (neigh == graph.end())
			std::cout << "Ne possede pas de voisins" << std::endl;
		else
		{
			for (auto n : neigh->second)
			{
				int d = distances[val.state] + n.second;
				if ((distances.find(n.first) != distances.end()
					&& distances.find(n.first)->second > d)
					|| distances.find(n.first) == distances.end())
				{
					distances[n.first] = d;
					fathers[n.first] = val.state;
					tmp.push(Elem({.distance= distances[n.first], .state= n.first}));
					std::cout << "Voisin1 -> " << n.first.value << " distance -> ";
					std::cout << distances[n.first] << " parent -> " << fathers[n.first].value << std::endl;
				}
			}
		}
	}
	std::cout << "Distance entre " << start.value << " et " << dest.value << " -> " << distances[dest] << std::endl;
	std::cout << "Parcours entre les deux points : " << std::endl;
	std::cout << dest.value << std::endl;
	while (dest != start)
	{
		dest = State{fathers[dest]};
		std::cout << dest.value << std::endl;
	}
}

void	exo8()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}

		bool operator!=(const State &other) const
		{
			return (value != other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	struct	Elem
	{
		int		distance;
		int		estimate;
		State 	state;
	};

	struct Cmp
	{
		bool operator()(const Elem &a, const Elem &b) const
		{
			return (a.distance + a.estimate > b.distance + b.estimate);
		}
	};

	std::unordered_map<State, std::vector<std::pair<State, int>>, StateHash> graph;
	graph[State{1}] = {{State{2}, 2}, {State{3}, 5}, {State{4}, 1}};
	graph[State{2}] = {{State{1}, 2}, {State{5}, 2}, {State{6}, 4}};
	graph[State{3}] = {{State{1}, 5}, {State{6}, 1}};
	graph[State{4}] = {{State{1}, 1}, {State{6}, 7}};
	graph[State{5}] = {{State{2}, 2}, {State{7}, 3}};
	graph[State{6}] = {{State{2}, 4}, {State{3}, 1}, {State{4}, 7}, {State{7}, 2}};
	graph[State{7}] = {{State{5}, 3}, {State{6}, 2}, {State{8}, 1}};
	graph[State{8}] = {{State{7}, 1}};
	
	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;

	State start = State{1};
	distances[start] = 0;
	State dest = State{8};
	tmp.push(Elem{.distance= 0, .estimate=dest.value - start.value,.state= start});
	while (!tmp.empty())
	{
		Elem val = tmp.top();
		tmp.pop();
		if (val.state == dest)
		{
			std::cout << "Dest atteind donc on stop" << std::endl;
			break;
		}
		if (val.distance > distances[val.state])
		{
			std::cout << "Distance connue plus petite donc on ignore" << std::endl;
			continue;
		}
		std::cout << "Traitement de " << val.state.value << std::endl;
		auto neigh = graph.find(val.state);
		if (neigh == graph.end())
			std::cout << "Ne possede pas de voisins" << std::endl;
		else
		{
			for (auto n : neigh->second)
			{
				int d = distances[val.state] + n.second;
				if ((distances.find(n.first) != distances.end()
					&& distances.find(n.first)->second > d)
					|| distances.find(n.first) == distances.end())
				{
					distances[n.first] = d;
					fathers[n.first] = val.state;
					tmp.push(Elem({.distance= distances[n.first], .estimate=dest.value - n.first.value,.state= n.first}));
					std::cout << "Voisin1 -> " << n.first.value << " distance -> ";
					std::cout << distances[n.first] << " parent -> " << fathers[n.first].value << std::endl;
				}
			}
		}
	}
	std::cout << "Distance entre " << start.value << " et " << dest.value << " -> " << distances[dest] << std::endl;
	std::cout << "Parcours entre les deux points : " << std::endl;
	std::cout << dest.value << std::endl;
	while (dest != start)
	{
		dest = State{fathers[dest]};
		std::cout << dest.value << std::endl;
	}
}

int		calc(int y, int x, int v, std::array<std::array<int, 3>, 3> &b)
{
	for (size_t i = 0; i < b.size(); i++)
	{
		for(size_t j = 0; j < b[i].size(); j++)
		{
			if (b[i][j] == v)
				return (abs(y - (int)i) + abs(x - (int)j));
		}
	}
	return (0);
}

int		calcEstimation(std::array<std::array<int, 3>, 3> &a, std::array<std::array<int, 3>, 3> &b)
{
	int	estimation = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < a[i].size(); j++)
		{
			if (a[i][j] != 0)
				estimation += calc(i, j, a[i][j], b);	
		}
	}
	return (estimation);
}

struct Pos
{
	size_t	y;
	size_t	x;
};

Pos	getPos(std::array<std::array<int, 3>, 3> &arr)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		for (size_t j = 0; j < arr[i].size(); j++)
		{
			if (arr[i][j] == 0)
				return (Pos{.y=i, .x=j});
		}
	}
	return (Pos{.y=4, .x=4});
}

void	exo9()
{
	struct State
	{
		std::array<std::array<int, 3>, 3> values;

		bool operator==(const State &other) const
		{
			return (values == other.values);
		}

		bool operator!=(const State &other) const
		{
			return (values != other.values);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			size_t h = 0;
			for (size_t i = 0; i < s.values.size(); i++)
			{
				for (size_t j = 0; j < s.values[i].size(); j++)
					h = h * 31 + std::hash<int>()(s.values[i][j]);
			}
			return (h);
		}
	};

	struct	Elem
	{
		int		distance;
		int		estimate;
		State 	state;
	};

	struct Cmp
	{
		bool operator()(const Elem &a, const Elem &b) const
		{
			return (a.distance + a.estimate > b.distance + b.estimate);
		}
	};

	State start = {{{ 
		{7, 2, 1}, 
		{4, 6, 0}, 
		{5, 8, 3} 
	}}};

	State dest = {{{ 
		{1, 2, 3}, 
		{4, 5, 6}, 
		{7, 8, 0} 
	}}};

	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;

	distances[start] = 0;
	tmp.push(Elem{.distance= 0, .estimate=calcEstimation(start.values, dest.values),.state= start});
	while (!tmp.empty())
	{
		Elem val = tmp.top();
		tmp.pop();
		std::cout << "State actuel traite : " << std::endl;
		for (size_t i = 0; i < val.state.values.size(); i++)
		{
			for (size_t j = 0; j < val.state.values[i].size(); j++)
			{
				std::cout << " " << val.state.values[i][j];
			}
			std::cout << std::endl;
		}
		if (val.state == dest)
		{
			std::cout << "Dest atteind donc on stop" << std::endl;
			break;
		}
		if (val.distance > distances[val.state])
		{
			std::cout << "Distance connue plus petite donc on ignore" << std::endl;
			continue;
		}

		Pos pos = getPos(val.state.values);
		if (pos.x > val.state.values.size())
			std::cout << "Ce state ne possede pas de voisin" << std::endl;
		else
		{
			if (pos.x > 0)
			{
				// enfant gauche
				std::array<std::array<int, 3>, 3> copy = val.state.values;
				int	arrTmp = copy[pos.y][pos.x];
				copy[pos.y][pos.x] = copy[pos.y][pos.x - 1];
				copy[pos.y][pos.x - 1] = arrTmp;
				State newState = State{copy};
				int d = distances[val.state] + 1;
				if ((distances.find(newState) != distances.end()
					&& distances.find(newState)->second > d)
					|| distances.find(newState) == distances.end())
				{
					distances[newState] = d;
					fathers[newState] = val.state;
					tmp.push(Elem({.distance= distances[newState], .estimate=calcEstimation(dest.values, newState.values),.state= newState}));
				}
			}
			if (pos.x < val.state.values.size() - 1)
			{
				// enfant droite
				std::array<std::array<int, 3>, 3> copy = val.state.values;
				int	arrTmp = copy[pos.y][pos.x];
				copy[pos.y][pos.x] = copy[pos.y][pos.x + 1];
				copy[pos.y][pos.x + 1] = arrTmp;
				State newState = State{copy};
				int d = distances[val.state] + 1;
				if ((distances.find(newState) != distances.end()
					&& distances.find(newState)->second > d)
					|| distances.find(newState) == distances.end())
				{
					distances[newState] = d;
					fathers[newState] = val.state;
					tmp.push(Elem({.distance= distances[newState], .estimate=calcEstimation(dest.values, newState.values),.state= newState}));
				}
			}
			if (pos.y > 0)
			{
				// enfant haut
				std::array<std::array<int, 3>, 3> copy = val.state.values;
				int	arrTmp = copy[pos.y][pos.x];
				copy[pos.y][pos.x] = copy[pos.y - 1][pos.x];
				copy[pos.y - 1][pos.x] = arrTmp;
				State newState = State{copy};
				int d = distances[val.state] + 1;
				if ((distances.find(newState) != distances.end()
					&& distances.find(newState)->second > d)
					|| distances.find(newState) == distances.end())
				{
					distances[newState] = d;
					fathers[newState] = val.state;
					tmp.push(Elem({.distance= distances[newState], .estimate=calcEstimation(dest.values, newState.values),.state= newState}));
				}
			}
			if (pos.y < val.state.values.size() - 1)
			{
				// enfant bas
				std::array<std::array<int, 3>, 3> copy = val.state.values;
				int	arrTmp = copy[pos.y][pos.x];
				copy[pos.y][pos.x] = copy[pos.y + 1][pos.x];
				copy[pos.y + 1][pos.x] = arrTmp;
				State newState = State{copy};
				int d = distances[val.state] + 1;
				if ((distances.find(newState) != distances.end()
					&& distances.find(newState)->second > d)
					|| distances.find(newState) == distances.end())
				{
					distances[newState] = d;
					fathers[newState] = val.state;
					tmp.push(Elem({.distance= distances[newState], .estimate=calcEstimation(dest.values, newState.values),.state= newState}));
				}
			}
		}
	}
	std::cout << "Start : " << std::endl;
	for (size_t i = 0; i < start.values.size(); i++)
	{
		for (size_t j = 0; j < start.values[i].size(); j++)
		{
			std::cout << " " << start.values[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "Dest : " << std::endl;
	for (size_t i = 0; i < dest.values.size(); i++)
	{
		for (size_t j = 0; j < dest.values[i].size(); j++)
		{
			std::cout << " " << dest.values[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "Distance : " << distances[dest] << std::endl;
	std::cout << "Chemin parcouru : " << std::endl;
	for (size_t i = 0; i < dest.values.size(); i++)
	{
		for (size_t j = 0; j < dest.values[i].size(); j++)
		{
			std::cout << " " << dest.values[i][j];
		}
		std::cout << std::endl;
	}
	int i = 0;
	std::cout << std::endl;
	while (dest != start)
	{
		dest = State{fathers[dest]};
		for (size_t i = 0; i < dest.values.size(); i++)
		{
			for (size_t j = 0; j < dest.values[i].size(); j++)
			{
				std::cout << " " << dest.values[i][j];
			}
			std::cout << std::endl;
		}
		i++;
		std::cout << std::endl;
		std::cout << i << std::endl;
		std::cout << std::endl;
	}
}

int	main()
{
	// exo1();
	// exo2();
	// exo3();
	// exo4();
	// exo5();
	// exo6();
	// std::cout << "SANS A*" << std::endl;
	// exo7();
	// std::cout << std::endl << std::endl << std::endl;
	// std::cout << "AVEC A*" << std::endl;
	// exo8();
	exo9();
	return (0);
}
