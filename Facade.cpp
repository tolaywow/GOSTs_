#include "Facade.h"
#include "Hash512.h"

Facade::Facade(size_t length_of_hash)
{
  length_of_hash_8 = length_of_hash / 0x8;

  if (length_of_hash == 0x200)
  {
    // Hash512 hash512;
    Hash = new Hash512;
  }
}

Facade::~Facade()
{
}

void Facade::give_hash(uint8_t *block, uint8_t *result)
{
  block_h = Hash->give_hash(block, uint64_t(length_of_hash_8) * 0x8 - 0x8);

  for (size_t i = 0; i < length_of_hash_8; i++)
  {
    result[i] = block_h[i];
  }
}
