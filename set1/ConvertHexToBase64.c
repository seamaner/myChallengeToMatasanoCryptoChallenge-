#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int base64_encode(const char* src, const int src_len, char *dst, int dst_len)
{
    char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    int i;
    unsigned char c;

    if (src == NULL || dst == NULL) return -1;

    if (dst_len <
            (src_len * 4 % 3 ? src_len * 4 / 3 + 3 : src_len * 4 / 3)
       ) return -1;

    for (i = 0; i < src_len; i += 3) {
        *dst++ = b64[src[i] >> 2];
        if (i + 2 < src_len) {
            c = (src[i] & 0x03) << 4;
            c |= (src[i+1] & 0xf0) >> 4;
            *dst++ = b64[c];
            c = (src[i+1] & 0x0f) << 2;
            c |= (src[i+2] & 0xc0) >> 6;
            *dst++ = b64[c];
            *dst++ = b64[src[i+2] & 0x3f];
        } else {
            break;
        }
    }
    if (i + 1 < src_len) {
        c = (src[i] & 0x03) << 4;
        c |= (src[i+1] & 0xf0) >> 4;
        *dst++ = b64[c];
        *dst++ = b64[(src[i+1] & 0x0f) << 2];
        *dst++ = '=';
    } else if (i < src_len){
        *dst++ = b64[(src[i] & 0x03) << 4];
        *dst++ = '=';
        *dst++ = '=';
    }
    return 0;
}

static unsigned char char2val(unsigned char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}

static int hex_decode(const char*hex, char*dst)
{
    unsigned char c;

    if (!hex || !dst)
        return -1;
    while(*hex != '\0') {
        c = char2val(hex[0]);
        c <<= 4;
        c += char2val(hex[1]);
        *dst++ = c;
        hex += 2;
    }
    return 0;
}

int main(void)
{
    char hex[]="49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    int hlen = 0, blen = 0;
    char *bbuf, *b64buf;

    hlen = strlen(hex);
    if (hlen & 0x01) {
        printf("hex is not correct\n");
        return -1;
    }

    bbuf = (char*)calloc(1, hlen >> 1);
    if (hex_decode(hex, bbuf) != 0) {
        printf("hex is error\n");
        return 0;
    }

    blen = hlen * 4 % 3 ? hlen * 4 / 3 + 3 : hlen * 4 / 3;
    b64buf = (char*)calloc(1, blen + 1);

    if (base64_encode(bbuf, hlen >> 1, b64buf, blen) != 0) {
        printf("base64 convert error\n");
        return -1;
    }
    b64buf[blen] = '\0';
    printf("%s\n", b64buf);
    printf("%s\n", "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
    if (strcmp(b64buf, "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t") == 0)
        printf("result is ok\n");
    if (bbuf)
        free(bbuf);
    if (b64buf)
        free(b64buf);
    return 0;
}
