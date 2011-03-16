#include <iostream>
#include "/usr/local/papi-3.6.2/include/papi.h" 

int main()
{
	int events[1] = {PAPI_L1_DCM};

	PAPI_start_counters(events, 1);

	std::cout << PAPI_num_counters() << std::endl;

	long long values[1];

	switch(PAPI_read_counters(values, 1))
	{
		case PAPI_EINVAL:
			std::cout << "PAPI_EINVAL" << std::endl;
			break;

		case PAPI_ESYS:
			std::cout << "PAPI_ESYS" << std::endl;
	}

	std::cout << values[0] << std::endl;
	PAPI_read_counters(values, 1);
}
