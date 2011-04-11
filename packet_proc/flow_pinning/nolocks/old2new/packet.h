#ifndef PACKET
#define PACKET

#include <string>

class Fragment;

class Packet
{
	public:
	int source;
	int dest;
	int id;
	std::string * contents;

	Packet (int s, int d, int i, std::string c);

	Packet (Fragment** fs);
};

class Fragment : public Packet
{
	public:
	int fragnum;
	int numfrags;

	Fragment(int s, int d, int i, std::string c, int f, int n) : Packet(s,d,i,c)
	{
		fragnum = f;
		numfrags = n;
	}
};


Packet::Packet (int s, int d, int i, std::string c)
{
        source = s;
        dest = d;
        id = i;
        contents = new std::string(c);
}

Packet::Packet (Fragment** fs)
{
        source = fs[0]->source;
        dest = fs[0]->dest;
        id = fs[0]->id;

        contents = new std::string("");

        for(int i = 0; i < fs[0]->numfrags; i++)
        {
		if(fs[i] != NULL)
			*contents += *fs[i]->contents;
        }
}

#endif
