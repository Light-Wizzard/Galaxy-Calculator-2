# Kalkulatorhjelp

Jeg bruker QCalculator for Math Engine, den finnes på
[https://github.com/xenotux/qcalc ](https://github.com/xenotux/qcalc)
documentaion finnes på [https://www.state-machine.com/qtools/qcalc.html ](https://www.state-machine.com/qtools/qcalc.html),
Jeg liker dette prosjektet,
så jeg forklet det på [https://github.com/Light-Wizzard/qcalc ](https://github.com/Light-Wizzard/qcalc),
og jeg har brukt noen av dokumentene deres her, og håper å skrive en bedre hjelpeseksjon for dette prosjektet.

***

Den viktigste egenskapen til QCalc er at den godtar uttrykk i <b> C -syntaksen </b> - med samme operander og fortrinnsregler som i C- eller C ++ - kildekoden. Blant andre,
uttrykkene kan inneholde alle bitvise operatører (`<<`,` >> `,` | `,` & `,`^`,` ~ `) samt blandet desimal,
<b> heksadesimale </b> og til og med binære konstanter.

QCalc er også en kraftig flytende vitenskapelig kalkulator og støtter alle matematiske funksjoner
(`sin ()`, `cos ()`, `tan ()`, `exp ()`, `ln ()`, ...).

Noen eksempler på akseptable uttrykk er:
`((0xBEEF << 16) | 1280) & ~ 0xFF ' - binære operatorer, blandet hex og desimaltall

`($ 1011 << 24) | (1280 >> 8) ^ 0xFFF0` - blandede binære, des og heks tall

`(1234 % 55) + 4321 // 33` - resten, heltall divisjon (merk operatøren` // `heltall

`pi/6` - pi -konstant

`pow (sin (ans), 2) + pow (cos (ans), 2)` - vitenskapelige flytende beregninger,
[ans-variable] (https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Merk: QCalc bruker internt Python -kommandoen <b> eval </b> for å evaluere uttrykkene.
Vennligst se dokumentasjonen for [Python math uttrykk] (https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
for mer informasjon om støttet syntaks og funksjoner.

# Automatisk konvertering til heksadesimal og binær

Hvis resultatet av uttrykksevaluering er heltall (i motsetning til flytende punkt),
QCalc viser automatisk resultatet i heksadesimale og binære formater (se QCalc -skjermbilde).
For bedre lesbarhet viser hex-displayet en apostrof mellom de to 16-biters halvordene (f.eks. '0xDEAD'BEEF').
På samme måte viser den binære utgangen en apostrof mellom de fire 8-bits bytes (f.eks. '0b11011110'10101101'10111110'11101111').

# Heksadesimale og binære tall

Som utvidelse til C-syntaksen støtter QCalc både <b> heksadesimale tall </b> og <b> binære tall </b>.
Disse tallene er henholdsvis representert som `` 0x ... 'og' 0b ... '
og kan blandes til uttrykk. Her er noen eksempler på slike uttrykk:

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123`


# Ans Variabel

QCalc lagrer resultatet av den siste beregningen i variabelen `ans`.
Her er noen eksempler på uttrykk med variabelen `ans`:

`1/ans` - finn det inverse av den siste beregningen

`log (ans)/log (2)`-finn log-base-2 for den siste beregningen

# 64-bits rekkevidde

QCalc støtter 64-bitersområdet og bytter automatisk til 64-bits aritmetikk når et <b> heltall </b> resultat av en beregning overskrider 32-bitsområdet.
Her er noen eksempler på 64-biters utdata:

``
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000'00000000
> 0xDEADBEEF << 34
! ute av rekkevidde
>
``

# Feilhåndtering

Uttrykk du angir i QCalc kan ha alle slags feil: syntaksfeil,
beregningsfeil (f.eks. divisjon med null) osv.
I alle disse tilfellene svarer QCalc med meldingen `Feil` og forklaring på feilen:

``
> (2*4) +)
Spor tilbake (siste samtale sist):
  Fil "\ ProgramPath \ qcalc.py", linje 54, i _main
resultat = eval (expr)
  Fil "<string>", linje 1
(2*4) +)
^
SyntaxError: unmatched ')'
>
``