#include <concepts>
#include <iostream>

// Définition d'un concept simple
template<typename T>
concept Addable = requires(T a, T b)
{
    { a + b } -> std::convertible_to<T>;
};

// Fonction contrainte par le concept
template<Addable T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    std::cout << add(3, 4) << std::endl;   // OK
    // std::cout << add("a", "b") << std::endl; // devrait échouer
    return (0);
}