#include <iostream>
#include <fstream>
#include <vector>

// Interpret tokens
void run(const std::vector<int>& tokens);

// Tokenize code
std::vector<int> tokenize(const std::string& code);

// Utilities
std::string read_file(const std::string& path);

// Syntax
enum operators
{
	LEFT,
	RIGHT,
	INCREMENT,
	DECREMENT,
	INPUT,
	OUTPUT
};

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: lovel [program.lov]" << std::endl;
    return 1;
  }

	std::string code = read_file(argv[1]);

	std::vector<int> tokens = tokenize(code);

	run(tokens);

	return 0;
}

void run(const std::vector<int>& tokens)
{
	std::vector<int> tape;

  tape.reserve(1);
  tape.push_back(1);

	int pointer = 0;

	for (int token : tokens)
	{
		switch (token)
		{
			case LEFT:
				if (pointer > 0) pointer--;
				break;

			case RIGHT:
				pointer++;

				tape.reserve(1);
				tape.push_back(0);

				break;

			case INCREMENT:
				tape.at(pointer)++;
				break;

			case DECREMENT:
				tape.at(pointer)--;
				break;

			case INPUT:
				tape.at(pointer) = (int) getchar();
				break;

			case OUTPUT:
				std::cout << (char) tape.at(pointer);
				break;

			default:
				break;
		}
	}
}

std::vector<int> tokenize(const std::string& code)
{
	std::vector<int> tokens;

	for (char i : code)
	{
		int token = -1;

		switch (i)
		{
			case '>':
				token = RIGHT;

				break;

			case '<' :
				token = LEFT;

				break;

			case '+':
				token = INCREMENT;

				break;

			case '-':
				token = DECREMENT;

				break;

			case '%':
				token = INPUT;

				break;

			case '*':
				token = OUTPUT;

				break;

			default:
				break;
		}

		if (token != -1)
		{
			tokens.reserve(1);
			tokens.push_back(token);
		}
	}

	return tokens;
}

std::string read_file(const std::string& path)
{
	std::fstream file_stream(path);

	if (!file_stream.is_open()) std::cout << "Failed to open " << path << std::endl;

	std::string content;
	std::string tmp;

	while (std::getline(file_stream, tmp)) content += tmp;

	return content;
}
