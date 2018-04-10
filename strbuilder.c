/*
 * This module provides a dynamically allocated string builder implementation
 */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include "strbuilder.h"

static void _resize(str_builder_t *ctx, size_t desired_size);
static int _append(str_builder_t *ctx, const char *src, size_t len);

int str_builder_init(str_builder_t *ctx, size_t chunk)
{
   ctx->size = chunk;
   ctx->chunk = chunk;
   ctx->offset = 0;

   ctx->buffer = malloc(chunk);
   if(!ctx->buffer)
   {
      return -1;
   }

   // Set the first null-character
   ctx->buffer[ctx->offset] = '\0';

   return 0;
}

/*
 * Returns the number of characters written not including the null-character,
 * or -1 on error. Relies on the src string being null-terminated.
 * Use str_builder_nappend if the src string is not guaranteed to be null
 * terminated properly.
 */
int str_builder_append(str_builder_t *ctx, const char *src)
{
   // Check src is not null before dereferencing it
   if(!src)
   {
      return -1;
   }

   // Work out the length by finding the offset of the null character
   int len = strlen(src);

   // Add the source to the buffer
   return _append(ctx, src, len);
}

int str_builder_nappend(str_builder_t *ctx, const char *src, size_t limit)
{
   // Check src is not null before dereferencing it
   if(!src)
   {
      return -1;
   }

   // Gets the length of the string less the null-character, up to limit
   int len = strnlen(src, limit);

   // Append the string to the end of the buffer
   return _append(ctx, src, len);
}

int str_builder_sprintf(str_builder_t *ctx, const char *format, ...)
{
   // Check src is not null before dereferencing it
   if(!format)
   {
      return -1;
   }

   va_list arglist;

   // Calculate the resulting string length of the sprintf format when populated
   va_start( arglist, format );
   int len = vsnprintf(NULL, 0, format, arglist);
   va_end( arglist );

   // Work out the total size of the string after adding the string src onto
   // the existing string (including the null-character)
   int desired_size = ctx->offset + len + 1;

   // Resize
   _resize(ctx, desired_size);

   if ( !ctx->buffer )
   {
      // There was an error allocing the buffer
      return -1;
   }

   // Finally print the formatted string to the buffer
   va_start( arglist, format );
   vsprintf( &ctx->buffer[ctx->offset], format, arglist );
   va_end( arglist );

   // Increment the current offset by the length of the string we just added
   ctx->offset += len;

   // Add in the null terminator
   ctx->buffer[ctx->offset] = '\0';

   return len;
}

/*
 * Appends an IP address to the end of a string in little-endian format.
 *
 * param in ctx
 *     String builder object.
 * param in ip
 *     IP address stored in little endian byte order.
 *
 * return: Returns the number of characters written on success; -1 on error.
 */
int str_builder_append_ip_be( str_builder_t *ctx, uint32_t ip )
{
   return str_builder_sprintf( ctx, "%u.%u.%u.%u",
         ( ip >> 24 ) & 0xFF,
         ( ip >> 16 ) & 0xFF,
         ( ip >>  8 ) & 0xFF,
         ( ip >>  0 ) & 0xFF );
}

/*
 * Appends an IP address to the end of a string in big-endian byte order.
 *
 * param in ctx
 *     String builder object.
 * param in ip
 *     IP address stored in big endian byte order.
 *
 * return: Returns the number of characters written on success; -1 on error.
 */
int str_builder_append_ip_le( str_builder_t *ctx, uint32_t ip )
{
   return str_builder_sprintf( ctx, "%u.%u.%u.%u",
         ( ip >>  0 ) & 0xFF,
         ( ip >>  8 ) & 0xFF,
         ( ip >> 24 ) & 0xFF,
         ( ip >> 24 ) & 0xFF );
}

/*
 * This could be NULL if a previous memory allocation (or reallocation) failed.
 */


/*
 * Returns a pointer to the first character of the underlying string buffer.
 *
 *
 * param in ctx
 *     String builder object.
 *
 * return: A valid pointer in
 */
char *str_builder_get(str_builder_t *ctx)
{
   return ctx->buffer;
}

int str_builder_size(str_builder_t *ctx)
{
   if(!ctx->buffer)
      return -1;
   return ctx->offset; // Don't include the null character
}

void str_builder_free(str_builder_t *ctx)
{
   free(ctx->buffer);
}

static void _resize(str_builder_t *ctx, size_t desired_size)
{
   if ( !ctx->buffer )
   {
      // There was an error allocing the buffer in the past
      return;
   }

   // Ensure we have enough room for the string + the null-character by doubling
   // the intented size of the buffer till we get something which is large
   // enough to container the string.
   // We do this instead of simply allocating the exact amount we need in order
   // to minimize the number of times we have to call realloc.
   while( ctx->size < desired_size )
   {
      ctx->size += ctx->chunk;
   }

   ctx->buffer = realloc(ctx->buffer, ctx->size);
}

/*
 * Returns the number of characters written not including the null-character,
 * or -1 on error.
 */
static int _append(str_builder_t *ctx, const char *src, size_t len)
{
   // Work out the total size of the string after adding the string src onto
   // the existing string (including the null-character)
   int desired_size = ctx->offset + len + 1;

   // Dynamically resize our string buffer - this will copy over the old data
   // too
   _resize( ctx, desired_size );

   if ( !ctx->buffer )
   {
      // There was an error allocing the buffer
      return -1;
   }

   // Copy over the exact number of bytes in the string. This does not include
   // the null character
   memcpy( &ctx->buffer[ctx->offset], src, len );

   // Increment the current offset by the length of the string we just added
   ctx->offset += len;

   // Add in the null terminator
   ctx->buffer[ctx->offset] = '\0';

   return len;
}
