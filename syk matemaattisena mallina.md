Olkoon  $s_{i,j}$  kokelaan $i$ tulos kokeessa $j$. Tavoitteena on määrittää kokelaan $i$ arvosana $X\in {\text{L}{,}\ \text{E}{,}\ \text{M}{,}\ \text{C}{,}\ \text{B}{,}\ \text{A}{,}\ \text{i}\}$

Määritellään aluksi porrasfunktio:
```math
H\left(x\right):=\begin{cases}
1{,}&x\ge0\\
0{,}&x<0
\end{cases}
```
Olkoon olemassa $I$ oppilasta ja $J$ koetta. Molemmat vakiot ovat positiivisia kokonaislukuja.

Jos kokelas $i$ ei osallistu kokeeseen $j$, niin $s_{i, j}=-1$

Tällöin kokeeseen $j$ osallistuu $\delta_{j}=\displaystyle\sum_{i=1}^I H(s_{i, j})$ oppilasta ja kokeen $j$ keskiarvo on $\overline{s_j}=\displaystyle\sum_{i=1}^I\frac{s_{i{,}j}H\left(s_{i{,}j}\right)}{\delta_j}$

