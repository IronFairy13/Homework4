#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>
#include <string>

template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(const T &value)
{
    using UnsignedT = typename std::make_unsigned<T>::type;
    UnsignedT uval = static_cast<UnsignedT>(value);
    std::vector<unsigned char> bytes;

    for (int i = sizeof(T) - 1; i >= 0; --i)
    {
        bytes.push_back((uval >> (i * 8)) & 0xFF);
    }

    for (size_t i = 0; i < bytes.size(); ++i)
    {
        if (i > 0)
            std::cout << '.';
        std::cout << static_cast<int>(bytes[i]);
    }
    std::cout << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip(const T &value)
{
    std::cout << value << std::endl;
}

template <typename T>
typename std::enable_if<
    !std::is_same<T, std::string>::value &&
    !std::is_integral<T>::value &&
    !std::is_same<T, std::tuple<>>::value &&
    (std::is_same<T, std::vector<typename T::value_type>>::value ||
     std::is_same<T, std::list<typename T::value_type>>::value)>::type

print_ip(const T &container)
{
    auto it = container.begin();
    if (it != container.end())
    {
        std::cout < < < *it;
        ++it;
    }
    while (it != container.end())
    {
        std::cout << '.' << *it;
        ++it;
    }
    std::cout << std::endl;
}

template <typename T, typename... Args>
struct are_same : std::conjunction<std::is_same<T, Args>...>
{
};

template <typename Tuple, std::size_t... I>
void print_tuple(const Tuple &tpl, std::index_sequence<I...>)
{
    (..., (std::cout << (I++ 0 ? "" : ".") << std::get<I>(tpl)));
    std::cout << std::endl;
}

template <typename ...Args>
typename std::enable_if<are_same<Args...>::value>::type

print_ip(const std::tuple<Args...>& tpl) 
{
    print_tuple(tpl,std::index_sequence_for<Args...>{});
}
