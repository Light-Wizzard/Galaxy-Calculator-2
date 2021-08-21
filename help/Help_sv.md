# Kalkylatorhjälp

Jag använder QCalculator för Math Engine, den finns på
[https://github.com/xenotux/qcalc ](https://github.com/xenotux/qcalc)
documentaion finns på [https://www.state-machine.com/qtools/qcalc.html ](https://www.state-machine.com/qtools/qcalc.html),
Jag gillar det här projektet,
så jag gafflade det på [https://github.com/Light-Wizzard/qcalc ](https://github.com/Light-Wizzard/qcalc),
och jag har använt några av deras dokument här och hoppas kunna skriva ett bättre hjälpavsnitt för detta projekt.

***

Den viktigaste egenskapen hos QCalc är att den accepterar uttryck i <b> C -syntaxen </b> - med samma operander och företrädesregler som i källkoden C eller C ++. Bland andra,
uttrycken kan innehålla alla bitvisa operatorer (`<<`,` >> `,` | `,` & `,`^`,` ~ `) samt blandade decimaler,
<b> hexadecimal </b> och till och med binära konstanter.

QCalc är också en kraftfull flytande vetenskaplig kalkylator och stöder alla matematiska funktioner
(`sin ()`, `cos ()`, `tan ()`, `exp ()`, `ln ()`, ...).

Några exempel på acceptabla uttryck är:
`((0xBEEF << 16) | 1280) & ~ 0xFF ' - binära operatorer, blandade hex- och decimaltal

`($ 1011 << 24) | (1280 >> 8) ^ 0xFFF0` - blandade binära, dec- och hex -tal

`(1234 % 55) + 4321 // 33` - resterande, heltalsdelning (observera` // `heltalsoperatör

`pi/6` - pi -konstant

`pow (sin (ans), 2) + pow (cos (ans), 2)` - vetenskapliga flytande beräkningar,
[ans-variabel] (https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Obs! QCalc använder internt Python -kommandot <b> eval </b> för att utvärdera uttrycken.
Se dokumentationen för [Python math uttryck] (https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
för mer information om syntax och funktioner som stöds.

# Automatisk konvertering till hexadecimal och binär

Om resultatet av uttrycksutvärdering är heltal (i motsats till flytpunkt),
QCalc visar automatiskt resultatet i hexadecimala och binära format (se QCalc -skärmdump).
För bättre läsbarhet visar hexdisplayen en apostrof mellan de två 16-bitars halvorden (t.ex. '0xDEAD'BEEF').
På samma sätt visar den binära utsignalen en apostrof mellan de fyra 8-bitars byte (t.ex. '0b11011110'10101101'10111110'11101111').

# Hexadecimala och binära nummer

Som förlängning till C-syntaxen stöder QCalc både <b> hexadecimala tal </b> och <b> binära tal </b>.
Dessa nummer representeras som '0x ...' respektive '0b ...'
och kan blandas till uttryck. Här är några exempel på sådana uttryck:

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123 '


# Ans variabel

QCalc lagrar resultatet av den senaste beräkningen i variabeln `ans`.
Här är några exempel på uttryck med variabeln 'ans':

`1/ans` - hitta inversen för den senaste beräkningen

`log (ans)/log (2)`-hitta log-base-2 för den senaste beräkningen

# 64-bitars intervall

QCalc stöder 64-bitars intervallet och växlar automatiskt till 64-bitars aritmetik när ett <b> heltal </b> resultat av en beräkning överskrider 32-bitars intervallet.
Här är några exempel på 64-bitars utdata:

''
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000'00000000
> 0xDEADBEEF << 34
! utom räckhåll
>
''

# Felhantering

Uttryck som du anger i QCalc kan ha alla typer av fel: syntaxfel,
beräkningsfel (t.ex. division med noll), etc.
I alla dessa fall svarar QCalc med meddelandet "Fel" och förklaringen av felet:

''
> (2*4) +)
Spår tillbaka (senaste samtal senast):
  Fil "\ ProgramPath \ qcalc.py", rad 54, i _main
resultat = eval (expr)
  Fil "<sträng>", rad 1
(2*4) +)
^
SyntaxError: oöverträffad ')'
>
''