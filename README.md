# One header file *iconv wrapper* for C++11

*iconv wrapper* is a iconv wrapper for C++11.
It consists of only one header file.
Therefore, you can use it easily.

## Build samples

There are two ways for building samples.

### Manually compile

The samples can be built by something like the following commands.
You might need different commands and options depending on the environment.

#### Simple sample

```
$ g++ -std=c++11 -o simple-sample simple-sample.cc -liconv
```

#### Advanced sample

```
$ g++ -std=c++11 -o advanced-sample advanced-sample.cc -liconv
```

### Autotools

*iconv wrapper* does not require Autotools.
But, the samples can be built easily by Autotools as the following commands.

```
$ ./autogen.sh
$ ./configure
$ make
```

## Usage

### Simple sample

Here is a part of [simple-sample.cc](./simple-sample.cc).

```c++
#include "iconv_wrapper.hh"

#include <iostream>
#include <iomanip>
#include <string>

int main ()
{
  std::string teststring {u8"The quick brown fox jumps over the lazy dog"};

  std::cout << "Test string" << std::endl
            << teststring << std::endl << std::endl;

  // Convert from UTF-8 to UTF-16
  iconv_wrapper::iconv cvt_utf8_to_utf16 {"UTF-8", "UTF-16"};
  std::string utf16 {cvt_utf8_to_utf16.convert (teststring)};

  // Output the resulting UTF-16
  std::cout << "Converted to UTF-16" << std::endl;
  output_utf16 (utf16);

  std::cout << std::endl;

  // Convert from UTF-16 to UTF-8
  iconv_wrapper::iconv cvt_utf16_to_utf8 {"UTF-16", "UTF-8"};
  std::string utf8 {cvt_utf16_to_utf8.convert (utf16)};

  // Output the resulting UTF-8
  std::cout << "Converted from UTF-16 to UTF-8" << std::endl;
  output_utf8 (utf8);

  return 0;
}
```

Here is an output:

```
$ ./simple-sample
Test string
The quick brown fox jumps over the lazy dog

Converted to UTF-16
FEFF 0054 0068 0065 0020 0071 0075 0069 0063 006B 0020 0062 0072 006F 0077 006E
0020 0066 006F 0078 0020 006A 0075 006D 0070 0073 0020 006F 0076 0065 0072 0020
0074 0068 0065 0020 006C 0061 007A 0079 0020 0064 006F 0067

Converted from UTF-16 to UTF-8
The quick brown fox jumps over the lazy dog

```

### Advanced sample

Advanced sample is [advanced-sample.cc](./advanced-sample.cc).

## Declaration

### Constructor

#### Default constructor

```c++
iconv ()
```

Default constructor.

#### Constructor with opening conversion descriptor

```c++
iconv (const std::string &fromcode,
       const std::string &tocode)
```

Constructor with opening conversion descriptor.

* Parameters:
  + `fromcode`: Encoding name for converting from.
  + `tocode`: Encoding name for converting to.

### Open

```c++
void open (const std::string &fromcode,
           const std::string &tocode)
```

Open conversion descriptor.

* Parameters:
  + `fromcode`: Encoding name for converting from.
  + `tocode`: Encoding name for converting to.

### Close

```c++
void close () noexcept
```

Close conversion descriptor.

### Convert

#### Basic

```c++
std::string convert (const std::string &in)
```

Convert.
When input byte sequence is invalid or incomplete etc.,
system_error exception will throw.
In exception handler, you cannot use invalid position of input
and incomplete output.

* Parameters:
  + `in`: Input byte sequence for converting.
* Return value:
  + Output converted byte sequence.

#### Advanced

```c++
std::string &convert (const std::string &in,
                      std::string::size_type *pinpos,
                      std::string *pout)
```

Convert with getting the incomplete input / output
when an exception occurs.
When input byte sequence is invalid or incomplete etc.,
system_error exception will throw.
In exception handler, you can use invalid position of input
and incomplete output.

* Parameters:
  + `in`: Input byte sequence for converting.
  + `pinpos`: Pointer of first invalid position of input.
    It is set before exception throwing.
    An exception handler can use this.
  + `pout`: Output converted byte sequence.
    An exception handler can use this.
* Return value:
  + Output converted byte sequence.

### Reset

```c++
void reset (void) const noexcept
```

Reset conversion state.

## License

Copyright (C) 2016 Masamichi Hosoda. All rights reserved.

License: BSD-2-Clause

See [LICENSE](./LICENSE).
