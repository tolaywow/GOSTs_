#include "Magma.h"
#include <stdexcept>

/**
 * @brief Набор подстановок
 *
 */
namespace Mgm_pish
{
	const uint8_t pi0[0x10] =
			{
					0xc, 0x4, 0x6, 0x2,
					0xa, 0x5, 0xb, 0x9,
					0xe, 0x8, 0xd, 0x7,
					0x0, 0x3, 0xf, 0x1};

	const uint8_t pi1[0x10] =
			{
					0x60, 0x80, 0x20, 0x30,
					0x90, 0xa0, 0x50, 0xc0,
					0x10, 0xe0, 0x40, 0x70,
					0xb0, 0xd0, 0x00, 0xf0};

	const uint8_t pi2[0x10] =
			{
					0xb, 0x3, 0x5, 0x8,
					0x2, 0xf, 0xa, 0xd,
					0xe, 0x1, 0x7, 0x4,
					0xc, 0x9, 0x6, 0x0};

	const uint8_t pi3[0x10] =
			{
					0xc0, 0x80, 0x20, 0x10,
					0xd0, 0x40, 0xf0, 0x60,
					0x70, 0x00, 0xa0, 0x50,
					0x30, 0xe0, 0x90, 0xb0};

	const uint8_t pi4[0x10] =
			{
					0x7, 0xf, 0x5, 0xa,
					0x8, 0x1, 0x6, 0xd,
					0x0, 0x9, 0x3, 0xe,
					0xb, 0x4, 0x2, 0xc};

	const uint8_t pi5[0x10] =
			{
					0x50, 0xd0, 0xf0, 0x60,
					0x90, 0x20, 0xc0, 0xa0,
					0xb0, 0x70, 0x80, 0x10,
					0x40, 0x30, 0xe0, 0x00};

	const uint8_t pi6[0x10] =
			{
					0x8, 0xe, 0x2, 0x5,
					0x6, 0x9, 0x1, 0xc,
					0xf, 0x4, 0xb, 0x0,
					0xd, 0xa, 0x3, 0x7};

	const uint8_t pi7[0x10] =
			{
					0x10, 0x70, 0xe0, 0xd0,
					0x00, 0x50, 0x80, 0x30,
					0x40, 0xf0, 0xa0, 0x60,
					0x90, 0xc0, 0xb0, 0x20};
}

/**
 * @brief Construct a new Magma:: Magma object
 *
 */
Magma::Magma()
{
	for (uint8_t i = 0; i < 0x20; i++)
	{
		K[i] = 0;
	}
}
/**
 * @brief метод загрузки ключей в алгоритм
 *
 * @param key_new C-массив с ключом
 */
void Magma::push_key(const uint8_t *key_new)
{
	if (key_new == nullptr)
	{
		throw std::invalid_argument("key_new");
	}

	for (uint8_t i = 0; i < 0x4; i++)
	{
		K[i] = key_new[i + 0x1c];

		K[0x4 + i] = key_new[i + 0x18];

		K[0x8 + i] = key_new[i + 0x14];

		K[0xc + i] = key_new[i + 0x10];

		K[0x10 + i] = key_new[i + 0xc];

		K[0x14 + i] = key_new[i + 0x8];

		K[0x18 + i] = key_new[i + 0x4];

		K[0x1c + i] = key_new[i];
	}
}

/**
 * @brief метод получения блока шифртекста из открытого
 * запись производится в полученный блок
 *
 * @param block  C-массив с открытым текстом
 */
void Magma::Give_ST(uint8_t *block)
{
	if (block == nullptr)
	{
		throw std::invalid_argument("block");
	}

	for (uint8_t i = 0; i < 0x18; i++)
	{
		G_k(block, block + 0x4, i % 0x8);
	}

	for (uint8_t i = 0; i < 0x7; ++i)
	{
		G_k(block, block + 0x4, 0x7 - i);
	}

	Gs_k(block, block + 0x4);
}

/**
 * @brief метод получения блока открытого из шифртекста
 * запись производится в полученный блок
 *
 * @param block  C-массив с открытым текстом
 */
void Magma::Give_OT(uint8_t *block)
{
	if (block == nullptr)
	{
		throw std::invalid_argument("block");
	}

	for (uint8_t i = 0; i < 0x8; ++i)
	{
		G_k(block, block + 0x4, i);
	}

	for (uint8_t i = 0; i < 0x17; i++)
	{
		G_k(block, block + 0x4, 0x7 - i % 0x8);
	}

	Gs_k(block, block + 0x4);
}

/**
 * @brief Перестановка местами и вызов метода g_k
 *
 * @param a0 В этот блок будет записан преобразованный блок а1
 * @param a1 В этот блок будет записано значение a0
 * @param num_of_key номер ключа для преобразования
 */
void Magma::G_k(uint8_t *a0, uint8_t *a1, const uint8_t num_of_key)
{
	uint32_t temp_a = *(uint32_t *)a1;

	uint32_t *temp = (uint32_t *)a1;

	*temp = *(uint32_t *)a0;

	g_k(a0, K + 0x4 * num_of_key);

	temp = (uint32_t *)a0;

	*temp ^= temp_a;
}

/**
 * @brief Последнее преобразование
 *
 * @param a0 Преобразуетса и конкатинируется к результату
 * @param a1 складывается по модулю 2
 */
void Magma::Gs_k(uint8_t *a0, uint8_t *a1)
{
	uint32_t temp_a = *(uint32_t *)a1; // �������� a1 ������ �����������, ����� ����� ������ ������

	uint32_t *temp = (uint32_t *)a1;

	*temp = *(uint32_t *)a0;

	g_k(a1, K);

	*temp ^= temp_a;
}

/**
 * @brief метод замены значений на подстановки и циклического сдвига на 11
 *
 * @param text Текст
 * @param key ключ
 */
void Magma::g_k(uint8_t *text, const uint8_t *key)
{
	uint32_t *temp = (uint32_t *)text;

	*temp += *(uint32_t *)key;

	text[0] = Mgm_pish::pi0[text[0] & 0xf] ^ Mgm_pish::pi1[text[0] >> 0x4];
	text[0x1] = Mgm_pish::pi2[text[0x1] & 0xf] ^ Mgm_pish::pi3[text[0x1] >> 0x4];
	text[0x2] = Mgm_pish::pi4[text[0x2] & 0xf] ^ Mgm_pish::pi5[text[0x2] >> 0x4];
	text[0x3] = Mgm_pish::pi6[text[0x3] & 0xf] ^ Mgm_pish::pi7[text[0x3] >> 0x4];

	*temp = *temp << 0xb ^ *temp >> 0x15;
}
