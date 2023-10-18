#ifndef MD5_H
#define MD5_H

#include <stddef.h>
#include <stdint.h>

int memcmp(const void *ptr1, const void *ptr2, size_t num);
void *memcpy(void *dst, const void *src, size_t len);
void *memset(void *dst, int val, size_t len);
void *md5(uint8_t *dst, uint8_t *src, size_t len);
void *hmac(uint8_t *dst, uint8_t *key, int keyLen, uint8_t *src, int srcLen);

#endif
