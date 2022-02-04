# Darwin Knapsack

Trabalho Final da Disciplina<br>
SSC0713 - Sistemas Evolutivos Aplicados a Robotica<br>

Alunos:<br>
- Gabriel Citroni Uliana - NUSP: 9779367<br>
- Vinícius Luiz da Silva Genésio - NUSP: 10284688<br>

Professor: Eduardo do Valle Simões<br>

## Explicação em Vídeo
[Darwin Knapsack - Explicação](https://youtu.be/jEd7Kg2b_Pg)

## Descrição do Problema

O programa Darwin Knapsack foi desenvolvido para resolver o Problema da Mochila, através do uso de Algoritmos Evolutivos.<br>
No Problema da Mochila, temos disponíveis vários itens e cada item tem um valor e um peso.<br>
Nós queremos levar o maior valor possível selecionando os itens, sem que seja ultrapassada a capacidade de peso máxima, previamente estipulada pelo problema.<br>
Cada item pode ser adicionado apenas uma vez na mochila.<br>

## Técnicas Utilizadas

- Elitismo
- Torneio de 2
- Predação
- Taxa de Mutação Variável

## Como usar

Primeiramente é necessário a instalação do gnuplot, caso não possua no seu sistema linux, execute a linha de comando no seu terminal:

```
$ sudo apt-get install gnuplot
```

Para usar enquanto recebe as informações das gerações no terminal, primeiro deve se retirar as partes de codigos comentadas no main.c<br>
Em seguida usar os seguintes comandos:<br>
```
$ make
$ make run
```

Para plotar um gráfico dos resultados, deve se utilizar os seguintes comandos:
```
$ make
$ ./main > grafico.txt
```

Em seguida, para plotar os gráficos execute a linha de comando: 

```
$ gnuplot
```

Agora com o gnuplot executando no terminal, digite:

```
> plot 'grafico.txt' title 'grafico' with lines
```

Isso irá produzir o gráfico referente ao Fitness do melhor individuo em cada geração.<br>
Caso deseje ver um gráfico referente a média da população, substitua o `getFiness(Bestindividuals[9])` por `getPopulationAverage()`, no `printf` da função `printGenerationInfo()`



