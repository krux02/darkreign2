#include "IntegerInserter.h"	

#ifdef _MINI_CRYPT

using namespace std;
using namespace WONCryptMini;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

IntegerInserter::IntegerInserter()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void IntegerInserter::AddLength(RawBuffer &theBuf, int theLen)
{
	if(theLen>0x7f)
	{
		if(theLen>0xff)
		{
			theBuf+=0x82; // 2 length bytes

			unsigned char aLowLen = ((unsigned short)theLen)>>8;
			unsigned char aHighLen = theLen & 0xff;
			theBuf+=aHighLen;
			theBuf+=aLowLen;
		}
		else
		{
			theBuf+=0x81; // 1 length byte
			theBuf+=(unsigned char)theLen;
		}
	}
	else
	{
		theBuf+=(unsigned char)theLen;
	}

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RawBuffer IntegerInserter::Get()
{
	RawBuffer aHeader;
	aHeader += (unsigned char)(SEQUENCE | CONSTRUCTED);
	AddLength(aHeader,out.length());
	
	return aHeader+out;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


void IntegerInserter::Insert(const BigInteger &theInt)
{
	out+=(unsigned char)INTEGER;
	RawBuffer aBuf = theInt.toByteArray();
	AddLength(out,aBuf.length());
	out+=aBuf;	
}	

#endif
