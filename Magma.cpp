#include "Magma.h"

namespace Mgm_pish
{
	const unsigned __int8 pi0[0x10] = 
	{
		0xc, 0x4, 0x6, 0x2,
		0xa, 0x5, 0xb, 0x9,
		0xe, 0x8, 0xd, 0x7,
		0x0, 0x3, 0xf, 0x1
	};

	const unsigned __int8 pi1[0x10] = 
	{ 
		0x60, 0x80, 0x20, 0x30,
		0x90, 0xa0, 0x50, 0xc0,
		0x10, 0xe0, 0x40, 0x70,
		0xb0, 0xd0, 0x00, 0xf0 
	};

	const unsigned __int8 pi2[0x10] = 
	{ 
		0xb, 0x3, 0x5, 0x8,
		0x2, 0xf, 0xa, 0xd,
		0xe, 0x1, 0x7, 0x4,
		0xc, 0x9, 0x6, 0x0
	};

	const unsigned __int8 pi3[0x10] = 
	{
		0xc0, 0x80, 0x20, 0x10,
		0xd0, 0x40, 0xf0, 0x60,
		0x70, 0x00, 0xa0, 0x50,
		0x30, 0xe0, 0x90, 0xb0
	};

	const unsigned __int8 pi4[0x10] = 
	{
		0x7, 0xf, 0x5, 0xa,
		0x8, 0x1, 0x6, 0xd,
		0x0, 0x9, 0x3, 0xe,
		0xb, 0x4, 0x2, 0xc
	};

	const unsigned __int8 pi5[0x10] = 
	{
		0x50, 0xd0, 0xf0, 0x60,
		0x90, 0x20, 0xc0, 0xa0,
		0xb0, 0x70, 0x80, 0x10,
		0x40, 0x30, 0xe0, 0x00
	};

	const unsigned __int8 pi6[0x10] = 
	{
		0x8, 0xe, 0x2, 0x5,
		0x6, 0x9, 0x1, 0xc,
		0xf, 0x4, 0xb, 0x0,
		0xd, 0xa, 0x3, 0x7
	};

	const unsigned __int8 pi7[0x10] = 
	{
		0x10, 0x70, 0xe0, 0xd0,
		0x00, 0x50, 0x80, 0x30,
		0x40, 0xf0, 0xa0, 0x60,
		0x90, 0xc0, 0xb0, 0x20
	};
}


Magma::Magma() 
{
	for (unsigned __int8 i = 0; i < 0x20; i++)
		K[i] = 0;

}

void Magma::push_key(const unsigned __int8* key_new)
{
	for (unsigned __int8 i = 0; i < 0x4; i++)
	{
		K[i] = key_new[i + 0x1c];

		K[0x4+i] = key_new[i + 0x18];

		K[0x8+i] = key_new[i + 0x14];

		K[0xc+i] = key_new[i + 0x10];

		K[0x10+i] = key_new[i + 0xc];

		K[0x14+i] = key_new[i + 0x8];

		K[0x18+i] = key_new[i + 0x4];

		K[0x1c+i] = key_new[i];
	}
}

void Magma::Give_ST(unsigned __int8* block)
{
	for (unsigned __int8 i = 0; i < 0x18; i++)
		G_k(block, block + 0x4, i % 0x8);

	for (unsigned __int8 i = 0; i < 0x7; ++i)
		G_k(block, block + 0x4, 0x7-i);

	Gs_k(block, block+0x4);
}

void Magma::Give_OT(unsigned __int8* block)
{
	for (unsigned __int8 i = 0; i < 0x8; ++i)
		G_k(block, block + 0x4, i);

	for (unsigned __int8 i = 0; i < 0x17; i++)
		G_k(block, block + 0x4, 0x7- i % 0x8);

	Gs_k(block, block + 0x4);
}

void Magma::G_k(unsigned __int8* a0, unsigned __int8* a1,const unsigned __int8 num_of_key)
{
	unsigned __int32 temp_a = *(unsigned __int32*)a1;

	unsigned __int32* temp = (unsigned __int32*)a1;

	*temp = *(unsigned __int32*)a0;

	g_k(a0, K+0x4 * num_of_key);
	
	temp = (unsigned __int32*)a0;

	*temp ^= temp_a;
}

void Magma::Gs_k(unsigned __int8* a0, unsigned __int8* a1)
{
	unsigned __int32 temp_a = *(unsigned __int32*)a1;//значение a1

	unsigned __int32* temp = (unsigned __int32*)a1;

	*temp = *(unsigned __int32*)a0;
	
	g_k(a1, K);

	*temp ^= temp_a;
}

void Magma::g_k(unsigned __int8* text, const unsigned __int8* key)
{
	unsigned __int32* temp = (unsigned __int32*)text;

	*temp += *(unsigned __int32*)key;
	
	text[0] = Mgm_pish::pi0[text[0] & 0xf] ^ Mgm_pish::pi1[text[0] >> 0x4];
	text[0x1] = Mgm_pish::pi2[text[0x1] & 0xf] ^ Mgm_pish::pi3[text[0x1] >> 0x4];
	text[0x2] = Mgm_pish::pi4[text[0x2] & 0xf] ^ Mgm_pish::pi5[text[0x2] >> 0x4];
	text[0x3] = Mgm_pish::pi6[text[0x3] & 0xf] ^ Mgm_pish::pi7[text[0x3] >> 0x4];
	
	*temp = *temp << 0xb ^ *temp >> 0x15;
}
