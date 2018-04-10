# strbuilder
Dynamically allocated string builder for C - because life's too short for C string manipulation.

## Status
[![Build Status](https://travis-ci.org/stevegolton/strbuilder.png)](https://travis-ci.org/stevegolton/strbuilder)

## Building
```
git clone https://github.com/stevegolton/strbuilder.git
cd strbuilder
cmake . && make && make test
```

## Usage
```
// Make a new string builder 'object' - block size 16 chars
str_builder_t ctx;
str_builder_init(&ctx, 16);

// Append some strings to it
str_builder_append(&cmd, "foo ");
str_builder_append(&cmd, "bar ");

// Sprintf some stuff to it
str_builder_sprintf(&cmd, "%f", 1.234);

// Get a pointer to the underlying C string and do stuff with it... 
char *result = str_builder_get(&cmd);
int len = str_builder_size(&cmd);

puts(result);
write(result, len);

// Clean up
str_builder_free(&cmd);

```

## Issues
- strbuilder is in no way reentrant
