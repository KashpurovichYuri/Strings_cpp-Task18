#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include "../seminar18/code/Part3/json.hpp"

using nlohmann::json;

struct Human
{
	std::string name;
	int age;
	int height;
	int weight;
	char gender;
	std::string place_of_birth;
	std::string date_of_birth;
	std::string phone_number;
	std::string email;
};

void to_json(json & j, const Human & h)
{
	j = json
	{
		{"name", h.name},
		{"age", h.age},
		{"height", h.height},
		{"weight", h.weight},
		{"gender", h.gender},
		{"place of birth", h.place_of_birth},
		{"date of birth", h.date_of_birth},
		{"phone_number", h.phone_number},
		{"email", h.email},
	};
}

std::istream & operator>>(std::istream&  stream, Human human)
{	
	std::cout << "Enter the name: ";
	stream >> human.name;
	std::cout << "age: ";
	stream >> human.age;
	std::cout << "the height and the weight: ";
	stream >> human.height >> human.weight;
	std::cout << "your gender: ";
	stream >> human.gender;
	std::cout << "where and when were you birth: ";
	stream >> human.place_of_birth >> human.date_of_birth;
	std::cout << "your phone_number and email: ";
	stream >> human.phone_number >> human.email;

	return stream;
}

int main()
{
	std::vector < Human >            humans(3);
	std::vector < json >              jsons(3);

	std::cout << "Welcome! Please, fill some information about yourself\n";
	for (auto i = 0; i < humans.size(); ++i)
	{
		std::cin >> humans[i];
		jsons[i] = humans[i];
	}

	auto path = std::filesystem::current_path();
	std::filesystem::create_directory(path / "JSONs files");
	path = path / "JSONs files";
	std::ofstream fout;
	std::vector < std::string > files_names(3);
	for (auto i = 0; i < jsons.size(); ++i)
	{
		files_names[i] = path.string() + "/" + "human" + std::to_string(i) + ".txt";
		fout.open(files_names[i]);
		fout << std::setw(4) << jsons[i] << std::endl;
		fout.close();
	}
}