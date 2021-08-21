# Rechner-Hilfe

Ich verwende QCalculator für die Math Engine, es ist zu finden unter
[https://github.com/xenotux/qcalc](https://github.com/xenotux/qcalc)
Dokumentation finden Sie unter [https://www.state-machine.com/qtools/qcalc.html](https://www.state-machine.com/qtools/qcalc.html),
Ich mag dieses Projekt,
also habe ich es unter [https://github.com/Light-Wizzard/qcalc](https://github.com/Light-Wizzard/qcalc) gegabelt,
und ich habe einige ihrer Dokumentationen hier verwendet und hoffe, einen besseren Hilfebereich für dieses Projekt schreiben zu können.

***

Die wichtigste Eigenschaft von QCalc ist, dass es Ausdrücke in der <b>C-Syntax</b> akzeptiert - mit den gleichen Operanden und Vorrangregeln wie im C- oder C++-Quellcode. Unter anderen,
die Ausdrücke können alle bitweisen Operatoren (`<<`, `>>`, `|`, `&`, `^`, `~`) sowie gemischt dezimal,
<b>hexadezimale</b> und sogar binäre Konstanten.

QCalc ist auch ein leistungsstarker wissenschaftlicher Fließkommarechner und unterstützt alle mathematischen Funktionen
(`sin()`, `cos()`, `tan()`, `exp()`, `ln()`, ...).

Einige Beispiele für akzeptable Ausdrücke sind:
`((0xBEEF << 16) | 1280) & ~0xFF` - binäre Operatoren, gemischte Hex- und Dezimalzahlen

`($1011 << 24) | (1280 >> 8) ^ 0xFFF0` - gemischte Binär-, Dez- und Hex-Zahlen

`(1234 % 55) + 4321//33` - Rest, ganzzahlige Division (beachte den `//` ganzzahligen Divisionsoperator

`pi/6` - pi-Konstante

`pow(sin(ans),2) + pow(cos(ans),2)` - wissenschaftliche Gleitkommaberechnungen,
[ans-variable](https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Hinweis: QCalc verwendet intern den Python-Befehl <b>eval</b>, um die Ausdrücke auszuwerten.
Bitte beachten Sie die Dokumentation der [Python-Mathe-Ausdrücke](https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
Weitere Informationen zu unterstützter Syntax und Funktionen.

# Automatische Konvertierung in Hexadezimal und Binär

Wenn das Ergebnis der Ausdrucksauswertung ganzzahlig ist (im Gegensatz zu Gleitkomma),
QCalc zeigt das Ergebnis automatisch im Hexadezimal- und Binärformat an (siehe QCalc-Screenshot).
Zur besseren Lesbarkeit zeigt die Hex-Anzeige einen Apostroph zwischen den beiden 16-Bit-Halbworten (z.B. `0xDEAD'BEEF`).
In ähnlicher Weise zeigt die binäre Ausgabe einen Apostroph zwischen den vier 8-Bit-Bytes (z. B. '0b11011110'10101101'10111110'11101111').

# Hexadezimal- und Binärzahlen

Als Erweiterung der C-Syntax unterstützt QCalc sowohl <b>Hexadezimalzahlen</b> als auch <b>Binärzahlen</b>.
Diese Zahlen werden als `0x...` bzw. `0b...` dargestellt.
und kann in Ausdrücke gemischt werden. Hier einige Beispiele für solche Ausdrücke:

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123`


# Die ans-Variable

QCalc speichert das Ergebnis der letzten Berechnung in der Variablen `ans`.
Hier sind einige Beispiele für Ausdrücke mit der Variablen `ans`:

`1/ans` - finde die Umkehrung der letzten Berechnung

`log(ans)/log(2)` - finde Log-Basis-2 der letzten Berechnung

# 64-Bit-Bereich

QCalc unterstützt den 64-Bit-Bereich und schaltet automatisch auf 64-Bit-Arithmetik um, wenn ein <b>integer</b>-Ergebnis einer Berechnung den 32-Bit-Bereich überschreitet.
Hier sind einige Beispiele für die 64-Bit-Ausgabe:

```
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000
> 0xDEADBEEF << 34
! außer Reichweite
>
```

# Fehlerbehandlung

Ausdrücke, die Sie in QCalc eingeben, können alle Arten von Fehlern enthalten: Syntaxfehler,
Rechenfehler (z. B. Division durch Null) usw.
In all diesen Fällen antwortet QCalc mit der Meldung `Error` und der Erklärung des Fehlers:

```
> (2*4) + )
Traceback (letzter Anruf zuletzt):
  Datei "\ProgramPath\qcalc.py", Zeile 54, in _main
result = eval(ausdruck)
  Datei "<string>", Zeile 1
(2*4) + )
^
SyntaxError: nicht übereinstimmend ')'
>
```