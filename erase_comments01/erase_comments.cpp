#include <iterator>
#include <fstream>
#include <string>
#include <iostream>

void erase_comments(std::string & code);

int main(int argc, char ** argv)
{
	std::fstream fin("test.txt", std::ios::in);

	std::string code {
		std::istreambuf_iterator < char > (fin),
		std::istreambuf_iterator < char > () };

	erase_comments(code);

	std::fstream fout("result.txt", std::ios::out);

	fout << code;

	system("pause");

	return EXIT_SUCCESS;
}

void erase_comments(std::string & code)
{
	for (auto current = std::begin(code); current != std::end(code); ++current) 
	{

		if (*current == '"')
		{
			// for
			++current;
			for ( ; (*std::prev(current) == '\\') || (*current != '"'); ++current );
		}
		if (*current == '/') 
		{
			if (*std::next(current) == '/') 
			{
				// for + erase
				for ( ; *current != '\n'; )
					code.erase(current, std::next(current));
			}
			else if (*std::next(current) == '*') 
			{
				// for + erase
				code.erase(current, ++std::next(current));
				for ( ; (*current != '*') & (*std::next(current) != '/'); )
					code.erase(current, std::next(current));
				code.erase(current, ++std::next(current));
			}
		}

		if (current == std::end(code))
		{
			break;
		}
	}
}