#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>

template <typename TP>
std::time_t to_time_t(TP tp)
{
    auto sctp = std::chrono::time_point_cast < std::chrono::system_clock::duration >
    	(tp - TP::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
}

void print_info(const std::filesystem::directory_entry & entry)
{
	auto name = entry.path().filename().string();
	auto ftime = to_time_t(std::filesystem::last_write_time(entry));

	if (std::filesystem::is_regular_file(entry.path()))
		std::cout << std::setw(15) << "File" << std::setw(30) << name;
	else if (std::filesystem::is_directory(entry.path()))
		std::cout << std::setw(15) << "Directory" << std::setw(30) << name;
	std::cout << std::setw(30) << ftime << std::endl;
}

int main()
{

	std::string directory;
	std::cin >> directory;
	std::filesystem::path path = std::filesystem::absolute(directory);

	if (!std::filesystem::exists(directory))
	{
		std::cerr << "Path " << directory << " does not exist.\n";

		return EXIT_FAILURE;
	}
	else
		std::cout << "Path " << directory << " exists." << std::endl;

	std::cout << "There are:\n";
	std::cout << std::setw(15) << "Type" << std::setw(30)
		<< "Name" << std::setw(30) << "Time of the latest change" << "\n";
	for (const auto & entry : std::filesystem::directory_iterator(directory))
		print_info(entry);

	system("pause");

	return EXIT_SUCCESS;
}