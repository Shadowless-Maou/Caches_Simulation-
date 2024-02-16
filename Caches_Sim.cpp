#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

using namespace std;

#define cacheSize 13864;
#define TagHex 0xFFFF0000;
#define UpperHex 0x0000FFFF;
#define WordHex 0x00000003;
#define SetHex 0x0000FFFC;
#define addrHex 0xFFFFFFFC;

unsigned short BytesN;
unsigned short SetN;
unsigned short UpperN;
unsigned short LowerN;
unsigned int Tag;

int HIT = 0;
int MISS = 0;
void DirectMappping(unsigned long CPUaddress);
void Twowayset(int way);
//void SetAss(unsigned int CPUaddress);
const int cachesize = cacheSize;
struct cachesEntry
{
	bool LRU;
	bool invaild;
	unsigned short Tag;
	unsigned char Flags;
	char bytes[4];
};

struct cachesEntry directmap[cachesize];

int main()
{
	unsigned int CPUaddr;
	fstream my_file; //object of fstream classs
	//convert address into bin
	//addressFile >> hex >> CPUaddress; //read address into cpuaddress

	int ans;
	ans = 0;
	std::cout << "\n|----------------Which cacheing method would you like to go with ?-----------------|" << std::endl;
	std::cout << "\n|-----(1)--DirectMapping--(2)--2-way-set-associative--(3)--full-set-associative----|" << std::endl;
	std::cout << "\nYour input ==> ";
	std::cin >> ans;

	if (ans == 1)
	{
		for (int i = 0; i < cachesize; i++)
		{
			directmap[i].invaild = true;
			directmap[i].LRU = true;
			directmap[i].Tag = true;
		}
		my_file.open("Addr.txt", ios::in);
		if (!my_file)
		{
			std::cout << "Error in reading file: " << std::endl;
			return 0;
		}
		while (my_file >> hex >> CPUaddr) //converting hex to decimal int cpuaddr
		{
			DirectMappping(CPUaddr);
		}
		my_file.close();
	}
	else if (ans == 2)
	{

		Twowayset(2);
	}
	else if (ans == 3)
	{
		my_file.open("6numbers.txt", ios::in);
		if (!my_file)
		{
			std::cout << "Error in reading file: " << std::endl;
			return 0;
		}
		while (my_file >> hex >> CPUaddr) //converting hex to decimal int cpuaddr
		{
			//SetAss(CPUaddr);
		}
		my_file.close();
	}

	printf("\nAmount of hits => %d\n", HIT);
	printf("\nAmount of misses => %d\n", MISS);
}

void DirectMappping(unsigned long CPUaddress)
{
	//cout << "  ..." << cpuAddr;
	//address  & with taghex
	//address & with wordhex
	//address & with SETHEx
	//compare CpuUpper address with
	//
	std::cout << "\n-------address has been read in :: " << hex << CPUaddress << std::endl;
	BytesN = CPUaddress & WordHex;
	SetN = CPUaddress & SetHex;
	Tag = CPUaddress & TagHex;
	Tag = CPUaddress >> 16;
	SetN = SetN >> 2;
	std::cout << "\nBytesN => " << BytesN << std::endl; //testing
	std::cout << "\nTAG => " << Tag << std::endl;		//testing
	std::cout << "\nSetN   => " << SetN << std::endl;	//testing
	if ((directmap[SetN].Tag == Tag) && (!directmap[SetN].invaild))
	{
		std::cout << "\n-------address is a hit :: " << hex << CPUaddress << std::endl;
		HIT++;
	}
	else
	{
		std::cout << "\n-------address is a Miss :: " << hex << CPUaddress << std::endl;
		directmap[SetN].Tag = Tag;
		directmap[SetN].invaild = false;
		MISS++;
	}
}

void Twowayset(int way)
{
	unsigned long CPUaddress;
	fstream my_file; //object of fstream classs
	cachesEntry TwoWayCacheing[2][cachesize];
	for (int x = 0; x < way; x++)
	{
		for (int i = 0; i < cachesize; i++)
		{
			TwoWayCacheing[x][i].invaild = true;
			TwoWayCacheing[x][i].LRU = true;
			TwoWayCacheing[x][i].Tag = true;
		}
	}

	my_file.open("Addr.txt", ios::in);
	if (!my_file)
	{
		std::cout << "Error in reading file: " << std::endl;
		return;
	}
	while (!my_file.eof())
	{

		my_file >> hex >> CPUaddress; //converting hex to decimal
		BytesN = CPUaddress & WordHex;
		SetN = CPUaddress & SetHex;
		Tag = CPUaddress & TagHex;
		Tag = CPUaddress >> 16;
		SetN = SetN >> 2;

		for (int x = 0; x < way; x++)
		{
			std::cout << "\n-------address has been read in ::" << hex << CPUaddress << std::endl;
			printf("\nBytesN  ==> %x", BytesN);
			printf("\nTag     ==> %x", Tag);
			printf("\nSetN    ==> %d", SetN);
			printf("\nWay     ==> %d", x);
			if ((TwoWayCacheing[x][SetN].Tag == Tag) && (!TwoWayCacheing[x][SetN].invaild))
			{
				std::cout << "\n-------address is a Hit :: " << hex << CPUaddress << std::endl;
				HIT++;
				if (TwoWayCacheing[x][SetN].LRU)
				{
					for (int y = 0; y < way; y++)
					{
						TwoWayCacheing[y][SetN].LRU = !TwoWayCacheing[y][SetN].LRU;
					}
				}
				break;
			}
			else if (x == way - 1)
			{
				std::cout << "\n-------address is a Miss :: " << hex << CPUaddress << std::endl;
				MISS++;
				for (int z = 0; z < way; z++)
				{
					if (TwoWayCacheing[z][SetN].LRU)
					{
						TwoWayCacheing[z][SetN].Tag = Tag;
						TwoWayCacheing[z][SetN].invaild = false;
						TwoWayCacheing[z][SetN].LRU = false;
						TwoWayCacheing[!z][SetN].LRU = true;
						break;
					}
				}
			}
		}
	}
	my_file.close();
}

/*void SetAss()
{
	unsigned long CPUaddress;
	fstream my_file; //object of fstream classs
	int x = 0;
	cachesEntry Fullassociative[x][cachesize];
	unsigned long tag;


	for (int y = 0; y < cachesize; y++)
	{
		Fullassociative[x][y].invaild = true;
		Fullassociative[x][y].LRU = true;
		Fullassociative[x][y].Tag = true;
	}

	my_file.open("6numbers.txt", ios::in);
	if (!my_file)
	{
		std::cout << "Error in reading file: " << std::endl;
		return;
	}
	while (!my_file.eof())
	{

		my_file >> hex >> CPUaddress; //converting hex to decimal
		BytesN = CPUaddress & WordHex;
		SetN = CPUaddress & SetHex;
		tag = CPUaddress & TagHex;
		Tag = CPUaddress >> 16;
		SetN = SetN >> 2;

		std::cout << "\n-------address has been read in ::" << hex << CPUaddress << std::endl;
		printf("\nBytesN  ==> %x", BytesN);
		printf("\nTag     ==> %x", Tag);
		printf("\nSetN    ==> %d", SetN);
		if ((Fullassociative[][SetN].Tag == Tag) && (!Fullassociative[SetN].invaild))
		{
			std::cout << "\n-------address is a Hit :: " << hex << CPUaddress << std::endl;
			HIT++;


		}

	}
}
my_file.close();
}*/
