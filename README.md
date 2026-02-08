# SA_to_binary<br>

SA (Signals Analyzer) from http://signals.radioscanner.ru/info/item21/
has some built-in generic decoders that can be used to get the raw binary from FSK and PSK
type signals.

This program turns the ASCII output from SA's decoders into binary files, which can then be
analyzed further in a hex editor or binary viewer.

## Features

Other than converting the ASCII to binary which is described below this program can also:

* Shift the output by 1-7 bits
* Invert the output
* Reverse the bit order in a byte
* Use your own custom table (recommended)

### Note: Shift works by placing extra 0's at the beginning of the file.

**See "table_example.txt" for the table format**

## Operation

This is how the converter works:

First it takes ASCII characters and converts them into their corresponding binary number
according to the table below or according to your custom table.

**Note: If type is not given, the default is 2.**

```
    | TYPE: | IN: |  OUT:  |
    |:-----:|:---:|:------:|
    |   2   |  0  |  0     |
    |       |  1  |  1     |
    |:-----:|:---:|:------:|
    |  3-4  |  2  |  10    |
    |       |  3  |  11    |
    |:-----:|:---:|:------:|
    |  5-8  |  4  |  100   |
    |       |  5  |  101   |
    |       |  6  |  110   |
    |       |  7  |  111   |
    |:-----:|:---:|:------:|
    | 9-16  |  8  |  1000  |
    |       |  9  |  1001  |
    |       |  A  |  1010  |
    |       |  B  |  1011  |
    |       |  C  |  1100  |
    |       |  D  |  1101  |
    |       |  E  |  1110  |
    |       |  F  |  1111  |
    |:-----:|:---:|:------:|
    | 17-32 |  G  |  10000 |
    |       |  H  |  10001 |
    |       |  I  |  10010 |
    |       |  J  |  10011 |
    |       |  K  |  10100 |
    |       |  L  |  10101 |
    |       |  M  |  10110 |
    |       |  N  |  10111 |
    |       |  O  |  11000 |
    |       |  P  |  11001 |
    |       |  Q  |  11010 |
    |       |  R  |  11011 |
    |       |  S  |  11100 |
    |       |  T  |  11101 |
    |       |  U  |  11110 |
    |       |  V  |  11111 |

```

**Note: This program will ignore other characters that are not found in the table.**

It then concatenates the bits until a "full" byte is achived.

In case cancatenating 2 or more bits results in more than 8 bits, the program splits them.
One byte is saved and the other remaining bits continue to be concatenated with more bits
until a "full" byte is reached again. Once there are no more bits from the input file left, if
there are any remaining concatenated bits that do not make a byte, they are then padded with 0's.

**Important:**

The bits are saved to the file MSb first! Using the reverse bit order option, they will be saved LSb first!

Ex. 1:

```
Type: 2
Input: 111010110

 1 is 1, 0 is 0 ...

Output: 111010110

Because the last bits don't make a byte, the program pads the output and the result is:

Output: 1110101100000000
```

Ex. 2:

```
Type: 4
Input: 10103201

 1 is 01, 0 is 00 ...

Output: 0100010011100001

```

Ex. 3:

```
Type: 16
Input: A12345

 A is 1010, 1 is 0001, 2 is 0010 ...

Output: 101011011100101

Because the last bits don't make a byte, the program pads the output and the result is:

Output: 1010110111001010

```

Ex. 4:

```
Type: 2
Input: AA11

 A will get ignored, 1 is 1 ...

Output: 11

Because the last bits don't make a byte, the program pads the output and the result is:

Output: 11000000

```


## Compiling on linux

On linux all you need is g++ installed.
First clone the repository, then inside it run the compile script.

Example:

```
git clone https://github.com/KingWing34/SA_to_binary.git
cd SA_to_binary
./compile_linux.sh
```

The executable will be in the build folder that will be created if everything succeeds.


## Compiling on Windows

At the moment there is a batch scrip that will compile the code, but the program does not
seem to function as it should like on linux.
This could be because of variable sizes being interpreted differently on windows
than on linux maybe. However it "appears" to work when not using an external table
or when not converting a very "random" file, such as one containing repeating 1010's..


If you still want to compile for windows, I recommend getting Mingw-w64 and running the 
provided batch script within it.

## TODO

* Add option: Try different combinations by rotating the table
* Add option: Try all combinations - (probably useless)
* Add GUI maybe.
