# Aide de la calculatrice

J'utilise QCalculator pour le moteur mathématique, il peut être trouvé à
[https://github.com/xenotux/qcalc](https://github.com/xenotux/qcalc)
la documentation peut être trouvée sur [https://www.state-machine.com/qtools/qcalc.html](https://www.state-machine.com/qtools/qcalc.html),
J'aime ce projet,
je l'ai donc forké sur [https://github.com/Light-Wizzard/qcalc](https://github.com/Light-Wizzard/qcalc),
et j'ai utilisé une partie de leur documentation ici, et j'espère écrire une meilleure section d'aide pour ce projet.

***

La caractéristique la plus importante de QCalc est qu'il accepte les expressions dans la <b>syntaxe C</b> - avec les mêmes opérandes et règles de priorité que dans le code source C ou C++. Entre autres,
les expressions peuvent contenir tous les opérateurs au niveau du bit (`<<`, `>>`, `|`, `&`, `^`, `~`) ainsi que des décimales mixtes,
<b>hexadécimales</b> et même des constantes binaires.

QCalc est également une puissante calculatrice scientifique à virgule flottante et prend en charge toutes les fonctions mathématiques
(`sin()`, `cos()`, `tan()`, `exp()`, `ln()`, ...).

Voici quelques exemples d'expressions acceptables :
`((0xBEEF << 16) | 1280) & ~0xFF` - opérateurs binaires, nombres hexadécimaux et décimaux mixtes

`($1011 << 24) | (1280 >> 8) ^ 0xFFF0` - nombres binaires, déc et hexadécimaux mixtes

`(1234 % 55) + 4321//33` - reste, division entière (notez l'opérateur de division entière `//`

`pi/6` - pi-constante

`pow(sin(ans),2) + pow(cos(ans),2)` - calculs scientifiques en virgule flottante,
[ans-variable](https://www.state-machine.com/qtools/qcalc.html#qcalc_ans)

***

Remarque : QCalc utilise en interne la commande Python <b>eval</b> pour évaluer les expressions.
Veuillez vous référer à la documentation des [expressions mathématiques Python](https://en.wikibooks.org/wiki/Python_Programming/Basic_Math)
pour plus de détails sur la syntaxe et les fonctionnalités prises en charge.

# Conversion automatique en hexadécimal et binaire

Si le résultat de l'évaluation de l'expression est un entier (par opposition à une virgule flottante),
QCalc affiche automatiquement le résultat aux formats hexadécimal et binaire (voir capture d'écran QCalc).
Pour une meilleure lisibilité, l'affichage hexadécimal montre une apostrophe entre les deux demi-mots de 16 bits (par exemple, "0xDEAD'BEEF").
De même, la sortie binaire affiche une apostrophe entre les quatre octets de 8 bits (par exemple, "0b11011110'10101101'10111110'11101111").

# Nombres hexadécimaux et binaires

En tant qu'extension de la syntaxe C, QCalc prend en charge à la fois les <b>nombres hexadécimaux</b> et les <b>nombres binaires</b>.
Ces nombres sont représentés par « 0x... » et « 0b... », respectivement,
et peut être mélangé dans des expressions. Voici quelques exemples de telles expressions :

`(0b0110011 << 14) & 0xDEADBEEF (0b0010 | 0b10000) * 123`


# La variable ans

QCalc stocke le résultat du dernier calcul dans la variable "ans".
Voici quelques exemples d'expressions avec la variable `ans` :

`1/ans` - trouver l'inverse du dernier calcul

`log(ans)/log(2)` - trouve log-base-2 du dernier calcul

# Plage de 64 bits

QCalc prend en charge la plage 64 bits et passe automatiquement à l'arithmétique 64 bits lorsqu'un résultat <b>entier</b> d'un calcul dépasse la plage 32 bits.
Voici quelques exemples de sortie 64 bits :

```
> 0xDEADBEEF << 27
= 501427843159293952 | 0x06F5'6DF7'7800'0000
= 0b00000110'11110101'01101101'11110111'01111000'00000000'00000000'00000000
> 0xDEADBEEF << 24
= 62678480394911744 | 0x00DE'ADBE'EF00'0000
= 0b00000000'11011110'10101101'10111110'11101111'00000000'00000000'00000000
> 0xDEADBEEF << 34
! hors de portée
>
```

# La gestion des erreurs

Les expressions que vous saisissez dans QCalc peuvent contenir toutes sortes d'erreurs : erreurs de syntaxe,
erreurs de calcul (par exemple, division par zéro), etc.
Dans tous ces cas, QCalc répond avec le message « Erreur » et l'explication de l'erreur :

```
> (2*4) + )
Traceback (appel le plus récent en dernier) :
  Fichier "\ProgramPath\qcalc.py", ligne 54, dans _main
résultat = eval(expr)
  Fichier "<string>", ligne 1
(2*4) + )
^
Erreur de syntaxe : sans correspondance ')'
>
```