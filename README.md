# Hash generatorius

## Veikimo princimas

Šioje programoje realizuotas hash‘avimo algoritmas leidžiantis užšifruoti unikaliu fiksuoto dydžio pseudo-atsitiktiniu skaičiumi, betkokį įvedimo tekstą .
Programa reikia naudotis per komandinę eilutę.Paleidus programa bus nurodytos instrukcijos:
```
To hash a string: Hash -hs <text>
To hash a file(include extention): Hash -hf <path>
To test for collitions with random pairs: Hash -bench -C
To test the avalanche effect: Hash -bench -A
Speed test with selected file(include extention): Hash -spd <path>
```
Užhash‘oti eilutė: `Hash -hs <text>`  
Užhash‘oti failą: `Hash -hf <path>`  
Pratestuoti kolizijas: `Hash -bench -C`  
Pratestuoti apvalančio efektą: `Hash -bench -A`  
Pratestuoti algoritmo spartą: `Hash -spd <path>`  

## Eksperimentinio tyrimas

### Failai su vienu simboliu
Šiame bandyme užhash‘ojami du failai su vienu bet skirtingu simboliu 
```
C:Hash>Hash -hf a.txt
Hash: E25A22D256E24E4272567E120AEEF69AF60A12AAC6D2962206361EEE825AB2DE

C:Hash>Hash -hf b.txt
Hash: F6FAEE42224E2EF6C6FA0A06E26A7E9A565A9A06B29AEE1EFAE2E2B2D2B242EE
```

### Failai iš daug simboliu
Šiame bandyme užhash‘ojami du failai iš daug (~10000) simboliu kurie skyriais vienu simboliu.
```
C:Hash>Hash -hf largeFile1.txt
Hash: A414135AC6B9697862C5E95BAB38740D2334FB9448648751DF588A6C70CA8E72

C:Hash>Hash -hf largeFile2.txt
Hash: A414135AC6B9697862C5E95BAB38740D2334FB9448648751DF588A6C70CA8E72
```
Jau šituo atveju gaunama pirma kolizija. Iš ko daroma prielaida kad algoritmas nera atsparus kolizijomis.

### Spartos testavimas
Šiame bandyme užhash‘ojama kiekvieną eilutę iš `konstitucija.txt` failo ir lyginama su MD5 SHA1 SHA256 algoritmais.
```
C:Hash>Hash -spd konstitucija.txt
My hash took 0.0119766
MD5 took 0.0028009
SHA1 took 0.004729
SHA256 took 0.0054693
```
Maždaug šis algoritmas užtrunka: 5 kart ilgiau už MD5, 2.5 kart ilgiau už SHA1, 2 kart ilgiau už SHA256

### Atsitiktinių porų hash'ų lyginimas 
Šiame bandyme sugeneruojami ir užhash'ojami visiškai atsitiktinės poros (10000) tokio pačio ilgio (10, 100, 500, 1000) eilučių ir tikrinami hash'ai.
```
C:Hash>Hash -bench -C
Generating random pairs...
Checking random pairs...

Size 10 collitions: 0
Size 100 collitions: 0
Size 500 collitions: 0
Size 1000 collitions: 0
```
Per kelias generacijas nei vienos kolizijos nebuvo gauta


### Panašių porų hash'ų lyginimas 
Šiame bandyme sugeneruojami ir užhash'ojami atsitiktinės poros (10000) tokio pačio ilgio (10, 100, 500, 1000) eilučių, kurios skiriasi vienu bitu ir tikrinami hash'ai.
```
C:Hash>Hash -bench -A
Generating similar pairs...
Checking similar pairs...

Minimum binary diffirence: 0%
Maximum binary diffirence: 69.5312%
Average binary diffirence: 45.7734%

Minimum hex diffirence: 0%
Maximum hex diffirence: 100%
Average hex diffirence: 89.6593%

Size 10 collitions: 250
Size 100 collitions: 263
Size 500 collitions: 261
Size 1000 collitions: 246
```
Per šį bandymą kiekviena generacija buvo gauta apie ~1000 kolizijų. Hash'o vidutiniškas procentinis skirtingumas bitų lygmenyje apytiksliai - 45%, o hex'ų lygmenyje - 89% .

## Išvados
Bandymų rezultatai parodo, kad šis maišos algoritmas gali priimti bet kokio dydžio eilutės  ir gražinti fiksuoto dydžio  rezultatą. Taip pat, algoritmas yra deterministinis. Tačiau jis nėra pilnai atsparus kolizijoms bei algoritmas negali pasižymėti savo spartumu. 



