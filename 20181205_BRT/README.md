# LEZIONE 2018/12/05 - ALBERI BINARI DI RICERCA
##### Gabor Galazzo 20024195 A.A. 2018/2019


Il programma *brt* permette di effettuare un test di valutazione delle performance effettive di ordinamento di un vettore mediante **quick_sort** o costrusione di **Albero Binario di Ricerca** e ricerche su essi.

> Uso: ./brt `n_array` `n_ricerche` `max_dim` `step`


L'applicativo procede con un <span style="color:lightblue">for</span> da *i* = 0 a `max_dim` con un passo di `step`; crea `n_array` array disordinati e li riordina tramite **ABR** o **quick_sort** e calcola la media del *tempo si esecuzione* e *numero di HIT*.
Infine per `n_ricerche` volte effettua ricerche tramite **ricerca dicotomica** calcolando la media del *numero di HIT*

## Risultati Finali

![fig. 1.1](doc/ordinamento_hit.png)

![fig. 1.2](doc/ordinamento_tempo.png)

![f1.3](doc/ricerca.png)

#### Per una migliore comprensione si consiglia di visualizzare il file [Benchmark_graphs.xls](doc/Benchmark_graphs.xlsx)

##### Le curve di asintotico sono realizzate applicando un restringimento del codominio basato sugli ipotetici valori di T(n)
![example](https://latex.codecogs.com/gif.latex?Ex%3A%20O%28n%5Ccdot%20log%28n%29%29%20%3D%20n%5Ccdot%20log%28n%29%20%5Ccdot%20%5Cfrac%7BmaxValue%7D%7BMaxSize%5Ccdot%20log%28MaxSize%29%7D)

## Commenti e considerazioni sui grafici ottenuti

#### Come trovate l’idea di usare un albero binario di ricerca come struttura per l’ordinamento e la ricerca efficiente di chiavi?
> Direi che è molto eficente dato che da la possibilità di effettuare ordinamenti in ![onlogn](https://latex.codecogs.com/gif.latex?O%28n%20%5Ccdot%20log%28n%29%29) e ricerche in ![ologn](https://latex.codecogs.com/gif.latex?O%28log%28n%29%29) potendo sfruttare un allocazione dinamica

### Quale complessità teorica (in notazione O) avrà la nostra tecnica di ordinamento mediante ABR?

> ![onlogn](https://latex.codecogs.com/gif.latex?T%28n%29%20%3DO%28n%20%5Ccdot%20log%28n%29%29)

### Avete notato differenze tra le performance di ricerca tra ABR e ricerca binaria, nonostante abbiano la stessa complessità teorica?

> Si: come si può notare dalla fig. 3 la ricerca all'interno di un **ABR "normale"** è molto più instabile e irregolare del **quick_sort**

### Se ci fossero differenze, quali potrebbero essere i motivi di queste differenze?

> Le differenze ci sono: il problema principale e che un ABR o dei suoi sottoalberi, in certi casi, possono degenerare in una lista, facendo tendere la ricerca ad una complessità ![on](https://latex.codecogs.com/gif.latex?O%28n%29)

### Quale soluzione funziona meglio nella pratica, tenendo conto sia del caso medio, sia del caso peggiore? Quale scegliereste nella pratica?

> Nella pratica valuterei quale esigenza è più importante: se avere la ricerca veloce o adottare una struttura dinamica. Quindi se effettuo **più ricerche** e meno modifiche opterei per usare un **vettore ordinato**, altrimenti se mi vengono richeste meno ricerche ma **molte modifiche** opterei su un **ABR**