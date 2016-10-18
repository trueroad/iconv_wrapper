//
// One header file iconv wrapper for C++11
// https://github.com/trueroad/iconv_wrapper/
//
// Simple Sample
//
// Copyright (C) 2016 Masamichi Hosoda. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include "iconv_wrapper.hh"

#include <iostream>
#include <iomanip>
#include <string>

void output_utf16 (const std::string &s);
void output_utf8 (const std::string &s);

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

void output_utf16 (const std::string &s)
{
  int i {1};

  for (auto c: s)
    {
      std::cout << std::hex << std::uppercase
                << std::setw (2) << std::setfill ('0')
                << static_cast<int>(static_cast<unsigned char>(c));
      if (!(i % 32))
        {
          std::cout << std::endl;
        }
      else if (!(i % 2))
        {
          std::cout << " ";
        }
      ++i;
    }
  std::cout << std::endl;
}

void output_utf8 (const std::string &s)
{
  std::cout << s << std::endl;
}
