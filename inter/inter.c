#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int ascii[255] = {0};
	int x;
	int y;

	if(argc == 3)
	{
		x = 2;
		while (x > 0)
		{
			y = 0;
			while(argv[x][y])
			{
				if(!ascii[(unsigned char)argv[x][y]] && x == 2)
					ascii[(unsigned char)argv[x][y]] = 1;
				if(ascii[(unsigned char)argv[x][y]] == 1 && x == 1)
				{
					ascii[(unsigned char)argv[x][y]] = 2;
					write(1, &argv[x][y], 1);
				}
				y++;
			}
			x--;
		}
	}
	write(1, "\n", 1);
	return (0);
}
