/*
 * Data Lab: Manipulating Bits
 * Optimized solution
 *
 * Integer puzzles use only the operators permitted by the lab.
 * Floating-point puzzles use integer/unsigned operations only.
 */

int bitXor(int x, int y) {
  return ~(x & y) & ~(~x & ~y);
}

int leastBitPos(int x) {
  return x & (~x + 1);
}

int getByte(int x, int n) {
  return (x >> (n << 3)) & 0xFF;
}

int logicalShift(int x, int n) {
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

int grayToBinary(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return x;
}

int bitCount(int x) {
  int m4 = 0x0F | (0x0F << 8);
  int m2;
  int m1;

  m4 = m4 | (m4 << 16);
  m2 = m4 ^ (m4 << 2);
  m1 = m2 ^ (m2 << 1);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  x = x + (x >> 8);
  x = x + (x >> 16);

  return x & 0x3F;
}

int isEqual(int x, int y) {
  return !(x ^ y);
}

int divpwr2(int x, int n) {
  int s = x >> 31;
  int bias = (s << n) ^ s;

  return (x + bias) >> n;
}

int sign(int x) {
  return (x >> 31) | !!x;
}

int addOK(int x, int y) {
  int sum = x + y;

  return !(((x ^ sum) & (y ^ sum)) >> 31);
}

int absVal(int x) {
  int mask = x >> 31;

  return (x + mask) ^ mask;
}

int satSub(int x, int y) {
  int d = x + ~y + 1;
  int ov = ((x ^ y) & (x ^ d)) >> 31;
  int tmin = 1 << 31;
  int sat = (d >> 31) ^ tmin;

  return d ^ (ov & (d ^ sat));
}

unsigned float_twice(unsigned uf) {
  unsigned exp = uf & 0x7F800000u;

  if (exp) {
    if (exp == 0x7F800000u)
      return uf;

    if (exp == 0x7F000000u) {
      if (uf & 0x80000000u)
        return 0xFF800000u;
      return 0x7F800000u;
    }

    return uf + 0x00800000u;
  }

  return uf + (uf & 0x7FFFFFFFu);
}

int float_f2i(unsigned uf) {
  unsigned e = (uf >> 23) & 0xFF;
  int frac;

  if (e < 127)
    return 0;

  if (e > 157)
    return 0x80000000u;

  frac = ((uf << 8) | 0x80000000u) >> (158 - e);

  if (uf & 0x80000000u)
    return -frac;

  return frac;
}

unsigned float_negpwr2(int x) {
  int neg127 = 0xFFFFFF81u;

  if (x < neg127)
    return 0x7F800000u;

  if (x < 127)
    return (127 - x) << 23;

  if (x <= 149)
    return 1u << (149 - x);

  return 0;
}

unsigned float_greater(unsigned x, unsigned y) {
  unsigned ax = x & 0x7FFFFFFFu;
  unsigned ay = y & 0x7FFFFFFFu;
  unsigned sx = x >> 31;
  unsigned sy = y >> 31;

  if (ax > 0x7F800000u)
    return 0;

  if (ay > 0x7F800000u)
    return 0;

  if (sx) {
    if (sy)
      return x < y;
    return 0;
  }

  if (sy)
    return ax || ay;

  return x > y;
}
