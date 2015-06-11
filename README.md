# Simulador de Memória Virtual
Projeto Simulador de Memória Virtual em linguagem C desenvolvida para a disciplina Introdução à Organização e Arquitetura de Computadores 2015.1. Bacharelado em Tecnologia da Informação. Instituto Metrópole Digital. Universidade Federal do Rio Grande do Norte.
# Descrição
O objetivo do projeto é simular operações de leitura e escrita na memória principal, quando se faz uso do recurso de memória virtual. O objetivo é, a partir de um conjunto de operações de leitura e escrita em endereços na memória principal (páginas), oferecer um relatório com números de page hits, page misses e page faults, permitindo comparar os algoritmos de substituição LRU, FIFO e Random.
# O código
O programa foi desenvolvido completamente em C e é composto por apenas um arquivo (SMV.c), que pode ser compilado a partir do gcc ou g++, por exemplo.

Foi utilizada a estrutura de dados Lista Encadeada para simular as páginas da memória, o que permitiu ganho de desempenho nos algoritmos LRU e FIFO. Utilizar um vetor geraria ganho de desempenho no Random e perda nos demais, mas seria igualmente possível utilizar essa estrutura.

# Execução
Para executar o programa, após compilado, deve-se usar a seguinte estrutura de comando no terminal/console:

`virtual [algoritmo] [arquivo] [tam_pagina] [tam_memoria]`

Onde:
* algoritmo: algorítmo de substituição a ser utilizado. Valores possíveis: lru, fifo e random.
* arquivo: arquivo contendo as instruções de leitura e escrita (seguir modelo do arquivo.log).
* tam_pagina: tamanho de cada página. Valores aceitáveis: 2 a 64.
* tam_memoria: tamanho total da memória disponível. Valores aceitáveis: 128 a 16384.

Exemplo de execução:
`virtual lru arquivo.log 32 128`
