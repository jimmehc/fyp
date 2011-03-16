#include <iostream>
#include <fstream>
#include <sstream>
int main(int argc, char * argv[])
{
	if(argc > 1)
	{
		std::ifstream input(argv[1]);

		std::string str;

		std::string k;

		unsigned long long matrix[5][6];		
		int i = 0;

		std::stringstream ss;
		if(input.is_open())
		{
			while(!input.eof())
			{
				ss.clear();
				getline(input, str);
				ss.str(str);
				ss >> k;
				std::cout << k << std::endl;
				if(k == "end") break;
				for(int j = 0; j < 5; j++)
					ss >> matrix[j][i];
				if(++i == 6) break;
			}
		}

		for(int j = 0; j < 5; j++)
		{
			for(int k = 0; k < 6; k++)
				std::cout << (double)matrix[j][0]/(double)matrix[j][k] << " ";
			std::cout << std::endl;
		}

	}
}
				
