// direct map
{
	unsigned int cpuAdress;

	struct cacheentr
	{
	 boolam lru:
	 boolen initals;
	 unisgend  short  tag;
	 char bytes[4];
	 };
	 
	 unsignedchar bytesNo;
	 unsignedchar  short SETNO;
	 unsignedchar  UpperNo;
	 bytesNo = cpuAdress& 0x00000003;
	 SETNO = cupaddress& 0x0000FFC;
	 SETNO = SETNO > 2;
	 
	 
	 
	 // 14 bit set no 2^14 = 16k entry
	 
	 struct cacheentrydirectmap[65386];
	 for(int i; i< 65386; i++)
	 directm.invaild = true;
	 
	 read address from file = cpu;
	  --> cpuadress
	  
	  // cpu adres = 32 -> 16/14/2
	  // to extract bit  use & op
	  // bit & all values  to last number 
	  
	  
	  if(directm[SETNO].tag == cpuUpperAdress && directm[SETNO].invaild = 0!)
	  {
		HIT++;
	  }
	  Else
	  {
		Miss++;
	  }
	  
	  
}

// for 2 way create 2 process and up a flag for checking whether if it recently update with either 0 or 1, 
// if the could is zero use that as the that process as the update where as the 1 is the newly update.
// remember to change the flag to a 1 if you just update the process
