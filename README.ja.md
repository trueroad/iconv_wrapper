<!-- -*- coding: utf-8 -*- -->
# One header file *iconv wrapper* for C++11

[ Japanese (日本語) / [English](./README.md) ]

[
https://github.com/trueroad/iconv_wrapper
](https://github.com/trueroad/iconv_wrapper)

*iconv wrapper* は C++11 用の iconv ラッパーです。
ヘッダファイル一つだけでできていますので、簡単に使えます。

## サンプルをビルドする

サンプルをビルドする方法には 2 通りあります。

### 手動コンパイル

サンプルは下記のようなコマンドでビルドできます。
環境によっては異なるコマンドやオプションが必要になる場合があります。

#### シンプルなサンプル

```
$ g++ -std=c++11 -o simple-sample simple-sample.cc -liconv
```

#### 高度なサンプル

```
$ g++ -std=c++11 -o advanced-sample advanced-sample.cc -liconv
```

### Autotools

*iconv wrapper* そのものは Autotools 不要ですが、
Autotools を使うと以下のコマンドで簡単にビルドできます。

```
$ ./autogen.sh
$ ./configure
$ make
```

## 使い方

### シンプルなサンプル

以下は [simple-sample.cc](./simple-sample.cc) からの抜粋です。

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

以下、出力の例です。

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

### 高度なサンプル

高度なサンプルは [advanced-sample.cc](./advanced-sample.cc) にあります。

## 定義

### コンストラクタ

#### デフォルトコンストラクタ

```c++
iconv ()
```

デフォルトコンストラクタです。

#### 変換記述子を開くコンストラクタ

```c++
iconv (const std::string &fromcode,
       const std::string &tocode)
```

変換記述子を開くコンストラクタです。

* パラメータ:
  + `fromcode`: 変換元エンコーディング名。
  + `tocode`: 変換先エンコーディング名。

### Open

```c++
void open (const std::string &fromcode,
           const std::string &tocode)
```

変換記述子を開きます。

* パラメータ:
  + `fromcode`: 変換元エンコーディング名。
  + `tocode`: 変換先エンコーディング名。

### Close

```c++
void close () noexcept
```

変換記述子を閉じます。

### 変換

#### 基本

```c++
std::string convert (const std::string &in)
```

変換します。
入力に不正や不完全なシーケンスがあった場合、
system_error 例外が投げられます。
例外ハンドラでは不正の位置や不完全な出力を使うことができません。

* パラメータ:
  + `in`: 変換するバイトシーケンス。
* 返り値:
  + 変換したバイトシーケンス。

#### 高度

```c++
std::string &convert (const std::string &in,
                      std::string::size_type *pinpos,
                      std::string *pout)
```

変換時に例外が発生した場合、不完全な入出力の状態を取得できます。
入力に不正や不完全なシーケンスがあった場合、
system_error 例外が投げられます。
例外ハンドラで不正の位置や不完全な出力を使うことができます。

* パラメータ:
  + `in`: 変換するバイトシーケンス。
  + `pinpos`: 最初の不正バイトの位置を格納する変数へのポインタ。
    例外が投げられる前に設定されます。
    例外ハンドラでこの値を使うことができます。
  + `pout`: 変換したバイトシーケンス。
    例外ハンドラでこの値を使うことができます。
* 返り値:
  + 変換したバイトシーケンス。

### リセット

```c++
void reset (void) const noexcept
```

変換ステータスをリセットします。

## License

Copyright (C) 2016 Masamichi Hosoda. All rights reserved.

License: BSD-2-Clause

[LICENSE](./LICENSE) をご覧ください。

もし GPL が良い場合には、
[Extract PDFmark](https://github.com/trueroad/extractpdfmark)
に GPL 版の *iconv wrapper* があります。
