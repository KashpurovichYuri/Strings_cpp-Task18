#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

std::vector < std::string > make_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (
        std::chrono::system_clock::now().time_since_epoch().count()));

    std::vector < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.push_back(s))
        for (auto & c : s)
            c = letter(e);
    for (auto& string : words)
        string.back() = '\n';

    return words;
}

void make_file(const size_t N, const size_t length)
{
    std::vector < std::string > words = make_words(N, length);
    std::fstream fwords("words.txt", std::ios::out);
    for (const auto& record : words)
        fwords << record;
}

int main()
{
    // make file with words
    const auto N = 20;
    const auto length = 10; // with '\n' symbol
    make_file(N, length);

    // search string if we do not know length of created words.
    std::fstream words("words.txt", std::ios::in);
    std::stringstream text;
    text << words.rdbuf();
    auto code = text.str(); // if I am not using this there will be some garbage?!

    auto current = std::begin(code);
    for ( ; *current != '\n'; ++current);
    auto length_of_word = std::distance(std::begin(code), current) + 1;

    int number_of_string;
    std::cin >> number_of_string;
    int pos = length_of_word * number_of_string;

    text.seekg(pos, std::ios::beg); 
    std::string ans(length_of_word, '\0');
    text.read(&ans[0], length_of_word);
    std::cout << ans << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}