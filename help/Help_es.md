# Ayuda de la calculadora

Yo uso QCalculator para Math Engine, se puede encontrar en
[https://github.com/xenotux/qcalc](https://github.com/xenotux/qcalc)
La documentación se puede encontrar en [https://www.state-machine.com/qtools/qcalc.html](https://www.state-machine.com/qtools/qcalc.html),
Me gusta este proyecto,
así que lo bifurqué en [https://github.com/Light-Wizzard/qcalc](https://github.com/Light-Wizzard/qcalc),
y he usado parte de su documentación aquí, y espero escribir una sección de ayuda mejor para este proyecto.

***

La característica más importante de QCalc es que acepta expresiones en la <b> sintaxis C </b>, con los mismos operandos y reglas de precedencia que en el código fuente C o C ++. Entre otros,
las expresiones pueden contener todos los operadores bit a bit (`<<`, `>>`, `|`, `&`, `^`, `~`) así como decimales mixtos,
<b> hexadecimal </b> e incluso constantes binarias.

QCalc es también una poderosa calculadora científica de punto flotante y es compatible con todas las funciones matemáticas.
(`sin ()`, `cos ()`, `tan ()`, `exp ()`, `ln ()`, ...).

Algunos ejemplos de expresiones aceptables son:
`((0xBEEF << 16) | 1280) & ~ 0xFF` - operadores binarios, números hexadecimales y decimales mixtos

`($ 1011 << 24) | (1280 >> 8) ^ 0xFFF0` - números binarios, dec y hexadecimales mixtos

`(1234% 55) + 4321 // 33` - resto, división de enteros (observe el operador de división de enteros` // `

`pi / 6` - constante pi

`pow (sin (ans), 2) + pow (cos (ans), 2)` - cálculos científicos de punto flotante,
[variable de respuesta] (https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Nota: QCalc utiliza internamente el comando de Python <b> eval </b> para evaluar las expresiones.
Consulte la documentación de las [expresiones matemáticas de Python] (https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
para obtener más detalles sobre la sintaxis y las funciones admitidas.

# Conversión automática a hexadecimal y binario

Si el resultado de la evaluación de la expresión es un número entero (a diferencia del punto flotante),
QCalc muestra automáticamente el resultado en formatos hexadecimales y binarios (vea la captura de pantalla de QCalc).
Para una mejor legibilidad, la pantalla hexadecimal muestra un apóstrofo entre las dos medias palabras de 16 bits (por ejemplo, `0xDEAD'BEEF`).
De manera similar, la salida binaria muestra un apóstrofe entre los cuatro bytes de 8 bits (por ejemplo, `0b11011110'10101101'10111110'11101111`).

# Números hexadecimales y binarios

Como extensión de la sintaxis C, QCalc admite tanto <b> números hexadecimales </b> como <b> números binarios </b>.
Estos números se representan como "0x ..." y "0b ...", respectivamente,
y se puede mezclar en expresiones. A continuación, se muestran algunos ejemplos de tales expresiones:

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123`


# La variable ans

QCalc almacena el resultado del último cálculo en la variable `ans`.
Aquí hay algunos ejemplos de expresiones con la variable `ans`:

`1 / ans` - encuentra la inversa del último cálculo

`log (ans) / log (2)` - encuentra log-base-2 del último cálculo

# Rango de 64 bits

QCalc admite el rango de 64 bits y cambia automáticamente a la aritmética de 64 bits cuando un resultado <b> entero </b> de un cálculo excede el rango de 32 bits.
A continuación, se muestran algunos ejemplos de la salida de 64 bits:

''
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000
> 0xDEADBEEF << 34
! fuera de rango
>
''

# Manejo de errores

Las expresiones que ingresa en QCalc pueden tener todo tipo de errores: errores de sintaxis,
errores de cálculo (por ejemplo, división por cero), etc.
En todos estos casos, QCalc responde con el mensaje "Error" y la explicación del error:

''
> (2 * 4) +)
Rastreo (llamadas recientes más última):
  Archivo "\ ProgramPath \ qcalc.py", línea 54, en _main
resultado = eval (expr)
  Archivo "<cadena>", línea 1
(2 * 4) +)
^
SyntaxError: incomparable ')'
>
''