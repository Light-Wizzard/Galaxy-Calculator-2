# Calculator Help

I use QCalculator for the Math Engine, it can be found at
[https://github.com/xenotux/qcalc](https://github.com/xenotux/qcalc)
documentaion can be found at [https://www.state-machine.com/qtools/qcalc.html](https://www.state-machine.com/qtools/qcalc.html),
I like this project, 
so I forked it at [https://github.com/Light-Wizzard/qcalc](https://github.com/Light-Wizzard/qcalc),
and I have used some of their documentaion here, and hope to write a better Help Section for this project.

***

The most important feature of QCalc is that it accepts expressions in the <b>C-syntax</b> - with the same operands and precedence rules as in the C or C++ source code. Among others,
the expressions can contain all bit-wise operators (`<<`, `>>`, `|`, `&`, `^`, `~`) as well as mixed decimal,
<b>hexadecimal</b> and even binary constants.

QCalc is also a powerful floating-point scientific calculator and supports all mathematical functions
(`sin()`, `cos()`, `tan()`, `exp()`, `ln()`, ...).

Some examples of acceptable expressions are:
`((0xBEEF << 16) | 1280) & ~0xFF` - binary operators, mixed hex and decimal numbers

`($1011 << 24) | (1280 >> 8) ^ 0xFFF0` - mixed binary, dec and hex numbers

`(1234 % 55) + 4321//33` - remainder, integer division (note the `//` integer division operator

`pi/6` - pi-constant

`pow(sin(ans),2) + pow(cos(ans),2)` - scientific floating-point calculations,
[ans-variable](https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Note: QCalc internally uses the Python command <b>eval</b> to evaluate the expressions.
Please refer to the documentation of the [Python math expressions](https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
for more details of supported syntax and features.

# Automatic Conversion to Hexadecimal and Binary

If the result of expression evaluation is integer (as opposed to floating point), 
QCalc automatically displays the result in hexadecimal and binary formats (see QCalc screenshot).
For better readability the hex display shows an apostrophe between the two 16-bit half-words (e.g., `0xDEAD'BEEF`).
Similarly, the binary output shows an apostrophe between the four 8-bit bytes (e.g., `0b11011110'10101101'10111110'11101111`).

# Hexadecimal and Binary Numbers

As the extension to the C-syntax, QCalc supports both <b>hexadecimal numbers</b> and <b>binary numbers</b>.
These numbers are represented as `0x...` and `0b...`, respectively, 
and can be mixed into expressions. Here are a few examples of such expressions:

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123`


# The ans Variable

QCalc stores the result of the last computation in the `ans` variable. 
Here are some examples of expressions with the `ans` variable:

`1/ans` - find the inverse of the last computation

`log(ans)/log(2)` - find log-base-2 of the last computation

# 64-bit Range

QCalc supports the 64-bit range and switches to 64-bit arithmetic automatically when an <b>integer</b> result of a computation exceeds the 32-bit range. 
Here are some examples of the 64-bit output:

```
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000
> 0xDEADBEEF << 34
! out of range
>
```

# Error handling

Expressions that you enter into QCalc might have all kinds of errors: syntax errors, 
computation errors (e.g., division by zero), etc.
In all these cases, QCalc responds with the `Error` message and the explanation of the error:

```
> (2*4) + )
Traceback (most recent call last):
  File "\ProgramPath\qcalc.py", line 54, in _main
result = eval(expr)
  File "<string>", line 1
(2*4) + )
^
SyntaxError: unmatched ')'
>
```

