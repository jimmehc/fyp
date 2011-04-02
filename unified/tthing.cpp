#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
int main(int argc, char * argv[])
{
	if(argc > 1)
	{

	std::cout << "=cluster;Spinlock(baseline);Pthread Mutex;Control;Asymmetric(Vasuvedan);Asymmetric Variation;One Function Pointer;Asynchronous FP;Message Passing;FP Spinlock;Function Pointer Queue;Message Passing Queue;\n=table\nyformat=%gx\n=norotate\nylabel=Speedup\nxlabel=Dominance Percentage\n\n" << std::endl;
			

		std::ifstream input(argv[1]);

		std::string str;

		std::string k;

		unsigned long long matrix[10][10];		
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
				for(int j = 0; j < 10; j++)
					ss >> matrix[j][i];
				if(++i == 10) break;
			}
		}

		std::string labels[10] = {"99.999", "99.99", "99.9", "99", "95", "90", "85", "80", "75", "70"};

		for(int j = 0; j < 10; j++)
		{
			std::cout << labels[j] << " ";
			for(int k = 0; k < 10; k++)
				std::cout << (double)matrix[j][0]/(double)matrix[j][k] << " ";
			std::cout << std::endl;
		}

	}
}
				
