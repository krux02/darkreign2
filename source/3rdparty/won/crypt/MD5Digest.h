#ifndef __MINICRYPT_MD5DIGEST_H__
#define __MINICRYPT_MD5DIGEST_H__

#include "MiniMisc.h"

namespace WONCryptMini
{

class MD5Digest
{

private:
    enum {
		HASH_LENGTH = 16,
		DATA_LENGTH = 64
	};

	RawBuffer out;

    int data[DATA_LENGTH/4];
    int mDigest[HASH_LENGTH/4];
    unsigned char tmp[DATA_LENGTH];
	__int64 count;

private:
	static int F(int x,int y,int z) { return (z ^ (x & (y^z))); }
	static int G(int x,int y,int z) { return (y ^ (z & (x^y))); }
	static int H(int x,int y,int z) { return (x ^ y ^ z); }
	static int I(int x,int y,int z) { return (y  ^  (x | ~z)); }

	static int FF(int a,int b,int c,int d,int k,int s,int t);
	static int GG(int a,int b,int c,int d,int k,int s,int t);
	static int HH(int a,int b,int c,int d,int k,int s,int t);
	static int II(int a,int b,int c,int d,int k,int s,int t);

	void transform();
	void transform(int M[]);
	void ReadData();

	static void byte2int(const unsigned char src[], int srcOffset,int dst[], int dstOffset, int length);
public:
	MD5Digest();
	void reset();

	void update(const RawBuffer& input);

	RawBuffer digest();
	RawBuffer digest(const RawBuffer& in);
	RawBuffer digest(const RawBuffer& in, int pos);



};

}

#endif
