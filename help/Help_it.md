# Aiuto Calcolatrice

Uso QCalculator per il motore matematico, può essere trovato su
[https://github.com/xenotux/qcalc](https://github.com/xenotux/qcalc)
la documentazione è disponibile su [https://www.state-machine.com/qtools/qcalc.html] (https://www.state-machine.com/qtools/qcalc.html),
mi piace questo progetto,
quindi l'ho biforcato su [https://github.com/Light-Wizzard/qcalc] (https://github.com/Light-Wizzard/qcalc),
e ho usato parte della loro documentazione qui, e spero di scrivere una sezione di aiuto migliore per questo progetto.

***

La caratteristica più importante di QCalc è che accetta espressioni nella <b>sintassi C</b> - con gli stessi operandi e regole di precedenza del codice sorgente C o C++. Tra gli altri,
le espressioni possono contenere tutti gli operatori bit per bit (`<<`, `>>`, `|`, `&`, `^`, `~`) e decimali misti,
Costanti <b>esadecimali</b> e persino binarie.

QCalc è anche una potente calcolatrice scientifica in virgola mobile e supporta tutte le funzioni matematiche
(`sin()`, `cos()`, `tan()`, `exp()`, `ln()`, ...).

Alcuni esempi di espressioni accettabili sono:
`((0xBEEF << 16) | 1280) & ~0xFF` - operatori binari, numeri esadecimali e decimali misti

`($1011 << 24) | (1280 >> 8) ^ 0xFFF0` - numeri misti binari, dec ed esadecimali

`(1234% 55) + 4321//33` - resto, divisione intera (notare l'operatore di divisione intera `//`

`pi/6` - pi-costante

`pow(sin(ans),2) + pow(cos(ans),2)` - calcoli scientifici in virgola mobile,
[variabile ans](https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Nota: QCalc utilizza internamente il comando Python <b>eval</b> per valutare le espressioni.
Fare riferimento alla documentazione delle [espressioni matematiche Python](https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
per maggiori dettagli sulla sintassi e sulle funzionalità supportate.

# Conversione automatica in esadecimale e binario

Se il risultato della valutazione dell'espressione è intero (anziché in virgola mobile),
QCalc visualizza automaticamente il risultato in formato esadecimale e binario (vedi screenshot QCalc).
Per una migliore leggibilità, il display esadecimale mostra un apostrofo tra le due mezze parole a 16 bit (ad es., `0xDEAD'BEEF`).
Allo stesso modo, l'output binario mostra un apostrofo tra i quattro byte a 8 bit (ad esempio, `0b11011110'10101101'10111110'11101111`).

# Numeri esadecimali e binari

Come estensione della sintassi C, QCalc supporta sia i <b>numeri esadecimali</b> che i <b>numeri binari</b>.
Questi numeri sono rappresentati rispettivamente come `0x...` e `0b...`,
e può essere mescolato in espressioni. Ecco alcuni esempi di tali espressioni:

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123`


# La variabile ans

QCalc memorizza il risultato dell'ultimo calcolo nella variabile `ans`.
Ecco alcuni esempi di espressioni con la variabile `ans`:

`1/ans` - trova l'inverso dell'ultimo calcolo

`log(ans)/log(2)` - trova log-base-2 dell'ultimo calcolo

# Intervallo a 64 bit

QCalc supporta l'intervallo a 64 bit e passa automaticamente all'aritmetica a 64 bit quando un risultato <b>intero</b> di un calcolo supera l'intervallo a 32 bit.
Ecco alcuni esempi dell'output a 64 bit:

```
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000
> 0xDEADBEEF << 34
! fuori dal limite
>
```

# Gestione degli errori

Le espressioni immesse in QCalc potrebbero contenere tutti i tipi di errori: errori di sintassi,
errori di calcolo (ad es. divisione per zero), ecc.
In tutti questi casi, QCalc risponde con il messaggio `Error` e la spiegazione dell'errore:

```
> (2*4) + )
Traceback (ultima chiamata più recente):
  File "\ProgramPath\qcalc.py", riga 54, in _main
risultato = eval(espr)
  File "<stringa>", riga 1
(2*4) + )
^
Errore di sintassi: ')' senza corrispondenza
>
```