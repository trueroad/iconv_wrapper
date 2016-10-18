//
// One header file iconv wrapper for C++11
// https://github.com/trueroad/iconv_wrapper/
//
// Advanced Sample
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
#include <utility>
#include <vector>

void output_utf16 (const std::string &s);

int main ()
{
  // Test strings {description, body}
  std::vector<std::pair<std::string, std::string>> teststrings
  {
    { "Test string 1 (normal text)",
      "The quick brown fox jumps over the lazy dog"},
    { "Test string 2 (normal encodings \"/\" in 1 octet)",
      "test / test"},
    { "Test string 3 (overlong encodings \"/\" in 2 octets)",
      "test \xc0\xaf test"},
    { "Test string 4 (overlong encodings \"/\" in 3 octets)",
      "test \xe0\x80\xaf test"},
    { "Test string 5 (overlong encodings \"/\" in 4 octets)",
      "test \xf0\x80\x80\xaf test"},
    { "Test string 6 (invalid code points U+D800~U+DFFF aka surrogate pair)",
      "test \xed\xa1\x82\xed\xbe\xb7 test"},
    { "Test string 7 (contains \\0)",
      static_cast<std::string>("test ") + '\0' + " test"},
  };

  // Create conversion instance without initialization
  iconv_wrapper::iconv cvt;

  try
    {
      // Initialize conversion instance: from UTF-8 to UTF-16
      cvt.open ("UTF-8", "UTF-16");
    }
  catch(std::system_error &error)
    {
      std::cout << "open error: " << error.code ()
                << " - " << error.what () << std::endl;
    }

  // Convert with exception handling
  std::cout << "*** Convert from UTF-8 to UTF-16 with exception handling ***"
            << std::endl;
  for (auto &a: teststrings)
    {
      // Description of test string
      std::cout << a.first << std::endl;
      try
        {
          // Convert and output test string
          output_utf16 (cvt.convert (a.second));
        }
      catch(std::system_error &error)
        {
          // Output exception
          std::cout << "convert error: " << error.code ()
                    << " - " << error.what () << std::endl;
          // Reset error state of conversion instance
          cvt.reset ();
        }
      std::cout << std::endl;
    }

  // Convert with getting the incomplete input / output
  // when an exception occurs)
  std::cout << "*** Convert with incomplete input / output when exception ***"
            << std::endl;
  for (auto &a: teststrings)
    {
      std::string utf16;
      std::string::size_type pos;

      // Description of test string
      std::cout << a.first << std::endl;
      try
        {
          // Convert and output test string
          output_utf16 (cvt.convert (a.second, &pos, &utf16));
        }
      catch(std::system_error &error)
        {
          // Output exception and incomplete input / output
          std::cout << "convert error: " << error.code ()
                    << " - " << error.what () << std::endl
                    << "first invalid position of input: "
                    << pos << std::endl
                    << "incomplete output: ";
          output_utf16 (utf16);
          // Reset error state of conversion instance
          cvt.reset ();
        }
      std::cout << std::endl;
    }

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
