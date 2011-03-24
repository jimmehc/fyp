#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
int main(int argc, char * argv[])
{
	if(argc > 1)
	{

	std::cout << "=cluster;Spinlock(baseline);Asymmetric(Vasuvedan);Asymmetric Variation;Function Pointer Queue;Message Passing Queue;\n=table\nyformat=%gx\n=norotate\nylabel=Speedup\nxlabel=Dominance Percentage\nmin=1\n\n" << std::endl;
			

		std::ifstream input(argv[1]);

		std::string str;

		std::string k;

		unsigned long long matrix[2][5];		
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
//				std::cout << k << std::endl;
				if(k == "end") break;
				for(int j = 0; j < 2; j++)
					ss >> matrix[j][i];
				if(++i == 5) break;
			}
		}

		std::string labels[2] = {"80", "70"};

		for(int j = 0; j < 2; j++)
		{
			std::cout << labels[j] << " ";
			for(int k = 0; k < 5; k++)
				std::cout << (double)matrix[j][0]/(double)matrix[j][k] << " ";
			std::cout << std::endl;
		}

	}
}
				
