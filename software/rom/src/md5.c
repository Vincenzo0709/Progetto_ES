#include "md5.h"

/* size_t memprint(const void *src, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++) {
        uint8_t byte = ((uint8_t *)src)[i];
        uint8_t high = byte / 16;
        uint8_t low = byte % 16;
        putchar(high + ((high >= 0xa) ? 'W' : '0'));
        putchar(low + ((low >= 0xa) ? 'W' : '0'));
    }
    
    return i;
} */

int memcmp(const void *src2, const void *src1, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		if (((uint8_t *)src2)[i] != ((uint8_t *)src1)[i]) {
			return -1;
		}
	}

	return 0;
}

void *memcpy(void *dst, const void *src, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
	}

	return dst;
}

void *memset(void *dst, int val, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		((uint8_t *)dst)[i] = (uint8_t)val;
	}

	return dst;
}

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

void *md5(uint8_t *dst, uint8_t *src, size_t len)
{
	uint32_t r[] = {
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};

	uint32_t k[] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	uint32_t h[] = {
		0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
	};

	int len4 = (len / 4) * 4;
	int new_len = ((((len + 8) / 64) + 1) * 64) - 8;

	uint8_t msg[new_len + 64 - len4];
	memset(msg, 0, new_len + 64 - len4);

	memcpy(msg, src + len4, len - len4);
	msg[len - len4] = 128;

	uint32_t bits_len = 8 * len;
	memcpy(msg + new_len - len4, &bits_len, 4);

	int offset;
	for (offset = 0; offset < new_len; offset += (512 / 8)) {
		uint32_t a = h[0];
		uint32_t b = h[1];
		uint32_t c = h[2];
		uint32_t d = h[3];

		uint32_t i;
		for (i = 0; i < 64; i++) {
			uint32_t f, g;

			if (i < 16) {
				f = (b & c) | ((~b) & d);
				g = i;
			} else if (i < 32) {
				f = (d & b) | ((~d) & c);
				g = (5 * i + 1) % 16;
			} else if (i < 48) {
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			} else {
				f = c ^ (b | (~d));
				g = (7 * i) % 16;
			}
			
			uint8_t *p;
			int n = offset + g * 4;
			if (n < len4) {
				p = src + n;
			} else {
				p = msg + n - len4;
			}
			
			uint32_t *w = (uint32_t *)p;
			
			uint32_t tmp = d;
			d = c;
			c = b;
			b = b + LEFTROTATE((a + f + k[i] + *w), r[i]);
			a = tmp;
		}

		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
	}

	memcpy(dst, h, 16);
}

void *hmac(
    uint8_t *dst,
    uint8_t *key,
    int keyLen,
    uint8_t *src,
    int srcLen
)
{
	static const int B = 64, L = 16;

	uint8_t keyPadded[B];
	memcpy(keyPadded, key, keyLen);
	memset(keyPadded + keyLen, 0, B - keyLen);

	uint8_t a[B + srcLen];
	for (int i = 0; i < B; i++)
		a[i] = keyPadded[i] ^ 0x36;
	memcpy(a + B, src, srcLen);

	uint8_t b[B + L];
	for (int i = 0; i < B; i++)
		b[i] = keyPadded[i] ^ 0x5C;
	md5(b + B, a, B + srcLen);

	md5(dst, b, B + L);
	return dst;
}
