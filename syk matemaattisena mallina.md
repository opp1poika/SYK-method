Olkoon  $x_{i,j}$  kokelaan $i$ tulos kokeessa $j$. Tavoitteena on määrittää kokelaan $i$ arvosana $X\in {\text{L}{,}\ \text{E}{,}\ \text{M}{,}\ \text{C}{,}\ \text{B}{,}\ \text{A}{,}\ \text{i}\}$

Määritellään aluksi porrasfunktio:
```math
H\left(x\right):=\begin{cases}
1{,}&x\ge0\\
0{,}&x<0
\end{cases}
```
Olkoon olemassa $I$ oppilasta ja $J$ koetta. Molemmat vakiot ovat positiivisia kokonaislukuja. Näin ollen $0\le i < I$ ja $0\le j < J$ On myös mielekästä olettaa, että jokainen oppilas osallistuu vähintään yhteen kokeeseen.

Jos kokelas $i$ ei osallistu kokeeseen $j$, niin $x_{i, j}=-1$

Tällöin kokeeseen $j$ osallistuu $\delta_{j}=\displaystyle\sum_{i=0}^{I-1}H(x_{i, j})$ oppilasta ja kokeen $j$ keskiarvo on $\overline{x_j}=\displaystyle\sum_{i=0}^{I-1}\frac{x_{i{,}j}H\left(x_{i{,}j}\right)}{\delta_j}$

Näin ollen kokeen $j$ keskihajonta on $\sigma_j=\sqrt{\frac{\displaystyle\sum_{i=0}^{I-1} H\left(x_{i{,}j}\right)\left(x_{i{,}j}-\overline{x_j}\right)^2}{\delta_j}}$

Keskihajonnan avulla saadaan laskettua jokaiselle oppilaalle $i$ kokeeseen $j$ normitettu arvo $z_{i{,}j}=H\left(x_{i{,}j}\right)\frac{x_{i{,}j}-\overline{x_j}}{\sigma_j}$

Kukin oppilas $i$ osallistuu $\epsilon_i=\displaystyle\sum_{j=0}^{J-1}H\left(x_{i{,}j}\right)$ kokeeseen.

Nyt voidaan laskea jokaiselle oppilaalle $i$ ns. SYK-pisteet eli standardoitujen yhteispisteiden keskiarvo eli saadaan $\overline{z_i}=\displaystyle\sum_{j=0}^{J-1}\frac{z_{i{,}j}}{\epsilon_i}$

Seuraavaksi jokaiselle kokelaalle $i$ annetaan SYK-arvosana SYK-pistespektrin mukaisesti. Järjestetään arvot $\overline{z_i}$ siten, että $\forall i < I:\ \overline{z_i}\ge\overline{z_{i-1}}$

Silloin saadaan seuraava arvosanataulukko:

|Väli|SYK-arvosana|
|----|--------|
|$0\le i<0{,}05\cdot I$|i|
|$0{,}05\cdot I\le i<0{,}20\cdot I$|A|
|$0{,}20\cdot I\le i<0{,}40\cdot I$|B|
|$0{,}40\cdot I\le i<0{,}60\cdot I$|C|
|$0{,}60\cdot I\le i<0{,}80\cdot I$|M|
|$0{,}80\cdot I\le i<0{,}95\cdot I$|E|
|$0{,}95\cdot I\le i< I $|L|

Näitä SYK-arvosanoja ei anneta opiskelijoille vaan niitä käytetään määrittämään kokeessa $j$ saatu arvosana.
