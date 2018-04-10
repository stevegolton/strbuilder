#ifndef STR_BUILDER_H
#define STR_BUILDER_H

#include <stddef.h>

typedef struct
{
   char *buffer;
   size_t offset; // <-- always points to the position of the null terminator
   size_t size;
   size_t chunk;

} str_builder_t;

int str_builder_init(str_builder_t *ctx, size_t chunk);
int str_builder_append(str_builder_t *ctx, const char *src);
int str_builder_nappend(str_builder_t *ctx, const char *src, size_t limit);
int str_builder_sprintf(str_builder_t *ctx, const char *format, ...);
char *str_builder_get(str_builder_t *ctx);
int str_builder_size(str_builder_t *ctx);
void str_builder_free(str_builder_t *ctx);

#endif
