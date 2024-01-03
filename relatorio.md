# Dicionários - AED2

## Alunos

* Jhonnatha Carvalho
* Kaike Ribas
* Lucas Martini
* Paulo Ricardo
* Ricardo Eliel

## Sumário

1. [Introdução](#introducao)
2. [O projeto em si](#projeto)
    
    2.1. [Estruturas de dados e Funções](#estrufuncdado)

    2.1.1. [Funções para Manipulação de Dados e cálculo do TF-IDF](#funcmanipulacao)

    2.2. [Tratamento das palavras](#tratamento)

    2.2.1 [*Stop Words*](#stopwords)

    2.3. [Função *Hash* e *Rerashing*](#hash)

3. [Estudo e resultados](#estudosresultados)

    3.1. [Resultados](#resultados)

4. [Conclusão](#conclusao)

*******

<div id='introducao'/>

## 1. Introdução

Em um mundo cada vez mais repleto de informações, a habilidade de localizar dados específicos em textos extensos torna-se crucial. Imagine-se diante de um densamente escrito livro, um documento longo ou até mesmo uma coleção de artigos, todos abarrotados de palavras e ideias. Nesse cenário, encontrar informações específicas ou identificar tópicos relevantes pode rapidamente se tornar uma tarefa desafiadora. É aí que entra a importância de ferramentas como o Índice Remissivo.

O Índice Remissivo desempenha um papel fundamental como um guia inteligente, organizando os termos e expressões encontrados em um texto e conectando-os às páginas correspondentes. Em essência, ele atua como um mapa que direciona os leitores a seções específicas do conteúdo, economizando tempo e simplificando a compreensão.

Um elemento-chave na construção desse índice é a identificação das chamadas "stop words", palavras comuns do idioma que, embora necessárias na comunicação cotidiana, geralmente não contribuem substancialmente para o entendimento de um texto. Estas incluem preposições, artigos, advérbios, números, pronomes e sinais de pontuação. O reconhecimento e tratamento adequado dessas palavras são fundamentais para garantir que o índice destaque os termos mais relevantes.

Além disso, introduzimos o conceito essencial de TF-IDF, uma métrica estatística que avalia a relevância de uma palavra em um documento em relação a um conjunto mais amplo de documentos. A sigla, que significa "Frequência do Termo - Inversa da Frequência no Documento", combina a frequência de uma palavra (TF) dentro do documento com sua raridade (IDF) em toda a coleção de documentos. O objetivo é identificar as palavras mais singulares e elucidativas no contexto do documento, tornando a compreensão e análise do conteúdo mais acessíveis.

Para calcular o TF-IDF, multiplicamos a frequência do termo (TF) pelo logaritmo da inversa da frequência no documento (IDF). O TF mede quantas vezes uma palavra ocorre em um documento específico, enquanto o IDF é determinado pelo logaritmo do número total de documentos dividido pelo número de documentos que contêm o termo em questão. As "stop words" são tratadas de forma neutra, uma vez que não contribuem significativamente para a relevância da palavra no contexto do documento.

Este projeto tem como objetivo central o desenvolvimento de um programa capaz de criar um índice remissivo a partir de um livro no formato de texto. Para alcançar essa meta, aplicaremos princípios de Tipos Abstratos de Dados (TAD) e técnicas de armazenamento, incluindo o uso de dicionários estáticos e dinâmicos. O resultado final será um conjunto de cinco páginas associadas a cada palavra identificada no livro, organizadas em ordem de relevância. Para garantir a eficiência e o desempenho do programa, tomaremos decisões apropriadas em relação às estruturas de dados e utilizaremos técnicas eficazes para o armazenamento e recuperação das informações necessárias.

Compreender as stop words, calcular o TF-IDF e construir um índice remissivo são etapas cruciais no processamento de texto e na busca eficaz de informações. Este projeto explora esses conceitos, oferecendo uma ferramenta valiosa para organizar e acessar o conhecimento contido em documentos extensos, beneficiando tanto os leitores ávidos quanto aqueles que buscam informações específicas em meio a um mar de palavras.

<div id='projeto'/>  

## 2. O projeto em si

Neste projeto, o objetivo principal é desenvolver um programa capaz de criar um índice remissivo a partir de um livro no formato de texto. Para atingir essa meta, serão aplicados princípios dos Tipos Abstratos de Dados (TAD) e técnicas de armazenamento, incluindo o uso de dicionários estáticos e dinâmicos. O resultado final incluirá um conjunto de cinco páginas associadas a cada palavra identificada no livro, organizadas em ordem de relevância.

<div id='estrudadofunc'/>

### 2.1 Estruturas de dados e Funções

<div id='estrufuncdado'/>

#### 2.1.1 Funções para Manipulação de Dados e cálculo do TF-IDF

Essas funções desempenham papéis específicos no processamento e análise dos dados do documento, permitindo a construção de métricas importantes, como o TF, IDF e TF-IDF, que são fundamentais para a análise de relevância de palavras e páginas em um contexto de processamento de texto e busca de informações, elas são:

   - ***n_containing_page*:** esta função é responsável por contar quantas vezes uma palavra ocorre em uma página específica. Ela percorre o dicionário dinâmico para obter as páginas em que a palavra ocorre e verifica se a página informada está na lista. Fundamental para calcular o TF-IDF posteriormente.

   -  ***n_containing*:** essa função conta quantas vezes uma palavra (identificada por sua chave) ocorre em todas as páginas. Ela é importante para calcular o IDF (Inverse Document Frequency) usado no cálculo do TF-IDF.
   - ***tf*:** calcula a frequência do termo (TF) de uma palavra em uma página específica. O TF mede a importância relativa de uma palavra em relação ao número total de palavras na página. Essa função é fundamental para calcular o TF de cada palavra em todas as páginas.

   - ***idf*:** calcula o Inverse Document Frequency (IDF) de uma palavra. O IDF é usado para avaliar a importância de uma palavra em todo o conjunto de documentos (páginas). Quanto menos frequente uma palavra for em todos os documentos, maior será seu IDF. 

   - ***tf_idf*:** calcula o TF-IDF (Term Frequency-Inverse Document Frequency) de uma palavra em uma página específica. O TF-IDF é uma métrica que combina o TF e o IDF e é usada para determinar a importância de uma palavra em relação a uma página e a todos os documentos. 

   - ***calcula_tf*:** essa função calcula o TF para todas as palavras em todas as páginas do documento. Ela percorre o dicionário dinâmico para obter as páginas em que cada palavra ocorre e calcula o TF para cada página. É crucial para ter o TF de todas as palavras nas páginas, preparando o terreno para o cálculo do TF-IDF.

   - ***calcula_idf*:** calcula o IDF de uma palavra específica usando o número total de páginas (qnt_paginas) e o número de páginas em que a palavra ocorre (n_containing). Essa função é importante para calcular o IDF de cada palavra, que é usado no cálculo do TF-IDF.

   - ***gerarChave*:** gera uma chave única para uma palavra com base no seu conteúdo. Isso é fundamental para indexar e recuperar informações sobre as palavras de maneira eficiente em estruturas de dados, como o dicionário dinâmico.

   Essas funções desempenham papéis específicos no processamento e análise dos dados do documento, permitindo a construção de métricas importantes, como o TF, IDF e TF-IDF, que são fundamentais para a análise de relevância de palavras e páginas em um contexto de processamento de texto e busca de informações.

<div id='tratamento'/>

#### 2.2. Tratamento das palavras

Antes de construir o Índice Remissivo, é essencial preparar o texto original para garantir uma análise precisa e relevante. O tratamento das palavras desempenha um papel fundamental nesse processo. Durante esta etapa, várias operações são realizadas para limpar e estruturar o texto de forma eficiente.

<div id='stopwords'/>

#### 2.2.1 *Stop Words*

 Como mencionado anteriormente, um aspecto importante do projeto é a criação e manipulação de palavras de parada. Essas funções desempenham um papel vital nesse processo:
   
   
   - ***struct* palavra**: esta estrutura é fundamental porque representa uma palavra no contexto do programa. Ela armazena a própria palavra como uma cadeia de caracteres (string) e uma chave associada a ela. A chave é geralmente gerada a partir do conteúdo da palavra e é usada para indexar e recuperar informações relacionadas à palavra de maneira eficiente em estruturas de dados.
   - ***struct* pagina**: ela armazena informações essenciais sobre a página, como o número da página e o número de ocorrências da palavra nessa página. Além disso, a estrutura inclui o valor TF (Frequência do Termo) da palavra na página, que é uma medida estatística crucial para determinar a relevância da palavra em uma página específica. Isso é fundamental para calcular o TF-IDF posteriormente.
   - ***struct* dados**: armazena informações abrangentes sobre o documento. Ela mantém o controle do número total de palavras e páginas no documento, além de incluir listas (como *listaPalavras* e *listaLinhas*) que permitem o armazenamento eficiente de informações relacionadas a palavras e páginas. Essa estrutura é central para o gerenciamento de dados e cálculos subsequentes.
   - ***struct* contador**: é importante porque rastreia a quantidade de palavras em uma página específica. Isso é necessário para calcular a frequência do termo (TF) de uma palavra em uma página e, consequentemente, o TF-IDF.
   - ***struct* nota**: é fundamental para armazenar informações sobre a relevância de uma palavra em relação a uma página específica. Ela inclui o valor TF-IDF da palavra nessa página, que é usado para classificar e identificar as palavras mais importantes no contexto do documento.

Este código tem como objetivo processar e tratar um arquivo de texto, realizando várias operações, como criação e manipulação de stop words, remoção de números e pontuações, conversão para letras minúsculas e geração de um novo arquivo de texto após o tratamento. Vou explicar as principais funcionalidades e o que cada função faz:

#### 2.1.2 Criando e manipulando *Stop Words* 

Um aspecto importante do projeto é a criação e manipulação de palavras de parada (stop words). Essas funções desempenham um papel vital nesse processo:

   - ***criar_sw*:** essa função cria uma nova stop word (palavra de parada) a partir de uma string passada como argumento e a aloca dinamicamente na memória. Retorna um ponteiro para a stop word criada.

   - ***imprimir_sw*:** Imprime uma stop word que é passada como um ponteiro genérico. É útil para depuração e visualização das stop words.

   - ***comparar_sw*:** compara duas stop words passadas como argumentos. Retorna um valor negativo se a primeira for menor, zero se forem iguais e um valor positivo se a primeira for maior. Essa função é usada para ordenar as stop words em uma estrutura de dados.

Função calcular o tamanho do livro:

   - ***tamanho_livro*:** abre o arquivo do livro (cujo nome é passado como argumento) e calcula o número total de palavras no livro. Retorna o tamanho do livro.

Função para Armazenar Stop Words em um Dicionário Estático:

   - ***guardar_sw*:** lê um arquivo de stop words (cujo nome é passado como argumento), cria stop words a partir das palavras lidas e as armazena em um dicionário estático (t_de). O dicionário é criado com base no tamanho do arquivo de stop words e nas funções de impressão e comparação de stop words. Retorna um ponteiro para o dicionário estático.

Funções para Tratar Palavras no Livro:

   - ***tratar_palavra*:** remove números e pontuações de uma palavra passada como argumento. Essa função é usada para limpar as palavras do livro.

   - ***to_lower_case*:** transforma todas as letras maiúsculas de uma palavra em letras minúsculas.

Funções para Tratar o Livro:

   - ***tratar_livro_sw*:** abre o arquivo do livro (cujo nome é passado como argumento), remove números e pontuações, converte letras maiúsculas em minúsculas e escreve o conteúdo tratado em um novo arquivo chamado "livro_processado.txt". Além disso, palavras presentes no dicionário de stop words (sw) são removidas do texto.

   - ***tratar_livro_art*:** funciona de maneira semelhante à função anterior, mas armazena as palavras removidas em um arquivo chamado "livro_auxiliar.txt". Isso implica que as palavras presentes no dicionário de stop words (art) não são removidas do texto, mas são copiadas para o arquivo auxiliar.

Essas funções, em conjunto, permitem processar e tratar um arquivo de texto, aplicando transformações nas palavras e removendo aquelas que estão no dicionário de stop words.

<div id='hash'/>

### 2.3. Função *Hash* e *Rerashing*

A função hash é essencial para a eficiência do projeto, pois ela é responsável por mapear as palavras identificadas no livro para índices específicos em uma tabela de hash. Isso é alcançado através de um cálculo simples, no qual a função hash pega o conteúdo da palavra e o transforma em um número inteiro correspondente ao índice onde a palavra será armazenada na tabela.

Por exemplo, ao processar uma palavra do livro, a função hash realiza um cálculo, geralmente uma operação de divisão, que resulta em um índice único para aquela palavra na tabela de hash. Isso significa que cada palavra será associada a um índice específico, permitindo que a recuperação de informações seja altamente eficiente. Sem a função hash, a busca por palavras no livro seria muito mais lenta, pois seria necessário percorrer todo o texto em busca da palavra desejada.

Além disso, a função hash desempenha um papel fundamental na minimização de colisões, ou seja, situações em que duas palavras diferentes são mapeadas para o mesmo índice. Uma boa função hash distribui as palavras de forma uniforme na tabela de hash, reduzindo as colisões e tornando o acesso aos dados mais rápido.

Já o rehashing é uma técnica crucial para garantir que a tabela de hash continue a funcionar de maneira eficiente à medida que mais palavras são processadas. Ele é acionado quando a tabela de hash atinge um fator de carga crítico, que é uma medida da quão cheia a tabela está. Um fator de carga próximo a 1.0 significa que a tabela está quase cheia demais, o que pode levar a colisões frequentes e a um desempenho insatisfatório.

Quando o rehashing é iniciado, uma nova tabela de hash maior é criada. Geralmente, o tamanho da nova tabela é aproximadamente o dobro do tamanho da tabela original, e normalmente é escolhido como um número primo próximo para garantir uma distribuição uniforme. Em seguida, todas as palavras da tabela original são redistribuídas para a nova tabela usando a função hash atualizada para o novo tamanho.

Essa redistribuição de palavras para a nova tabela alivia a carga na tabela original, reduzindo as colisões e melhorando o desempenho global da estrutura de dados. O rehashing é uma operação que ocorre em segundo plano, de modo que o usuário final não precisa se preocupar com isso, mas é fundamental para manter o sistema funcionando de maneira eficaz, mesmo com grandes volumes de dados.

Em resumo, a função hash é responsável por mapear palavras para índices na tabela de hash, permitindo uma recuperação eficiente de informações, enquanto o rehashing é uma técnica vital para redimensionar a tabela de hash e manter o desempenho conforme o número de palavras cresce.

<div id='estudosresultados'/>

## 3. Estudo e resultados

Nesta seção, abordaremos em detalhes o processo de estudo e os resultados obtidos ao aplicar nosso Índice Remissivo às obras literárias selecionadas. Nosso objetivo principal era avaliar o desempenho do índice em relação ao número de elementos, inserções e buscas em textos literários reais. Além disso, discutiremos os desafios encontrados durante o estudo e possíveis melhorias futuras.

Após a conclusão da implementação do Índice Remissivo, conforme descrito anteriormente, procedemos à utilização de uma base de dados de teste contendo os textos completos de três obras literárias:

   - As Aventuras de Huckleberry Finn.
   - O Guarani.
   - Paralelismo em visão natural e artificial.

O estudo implica em analisar o número de elementos, número de inserções e número de buscas no texto, utilizando funções  citadas anteriormente e, posteriormente, pegando uma média dessa análise.

<div id='resultados'/>

### 3.1. Resultados

Agora, vamos analisar os resultados obtidos ao aplicar o Índice Remissivo às três obras literárias: "As Aventuras de Huckleberry Finn", "O Guarani" e "Paralelismo em visão natural e artificial". Os resultados são apresentados na tabela abaixo:

|                | Huckleberry   | Guarani       |  Paralelismo  |  Média               |
| :-----------:  | :-----------: | :-----------: | :-----------: |  :-----------:       |
|N° de elementos | 11.688        | 11.444        | 8.382         | 10.504        |
|N° de inserções | 11.688        | 11.444        | 8.382         | 10.504        |
|N° de buscas    | 109.116       | 118.504       | 135.734       | 121.118       | 

Através da análise da tabela, podemos tirar algumas conclusões importantes. Primeiro, observamos que o número de elementos e inserções é semelhante em todas as obras literárias. Isso indica que o Índice Remissivo foi capaz de lidar eficazmente com diferentes textos, independentemente do tamanho ou conteúdo.

No entanto, ao observar o número de buscas, percebemos uma variação mais significativa. A obra "Paralelismo em visão natural e artificial" apresentou um número substancialmente maior de buscas em comparação com as outras duas obras. Isso pode ser atribuído à natureza do texto e à complexidade das palavras-chave que foram pesquisadas.

É importante ressaltar que, embora tenhamos obtido resultados satisfatórios na indexação das palavras e na criação do Índice Remissivo, identificamos um desafio significativo relacionado ao tratamento de caracteres acentuados na língua portuguesa. Devido à complexidade e diversidade do idioma e suas nuancias, ainda não incorporamos uma solução completa para lidar com eles, o que afetou a precisão da indexação e busca de palavras acentuadas.

Em resumo, os resultados deste estudo demonstram a eficácia do nosso Índice Remissivo na indexação de obras literárias diversas. No entanto, reconhecemos a necessidade de melhorias futuras para lidar com caracteres acentuados e otimizar ainda mais o desempenho em textos complexos. Estamos comprometidos em explorar abordagens de normalização de caracteres acentuados, garantindo uma indexação precisa e eficaz, independentemente da presença de acentos nas palavras.

<div id='conclusao'/>

## 4. Conclusão

Neste projeto, empreendemos uma jornada na construção de um Índice Remissivo destinado a facilitar a busca e recuperação de informações específicas em documentos extensos. Ao longo desse processo, abordamos conceitos fundamentais de processamento de texto, armazenamento de dados e métricas estatísticas, resultando em uma ferramenta capaz de organizar conteúdo complexo de maneira acessível.

Durante o desenvolvimento, aprofundamo-nos na identificação e tratamento das chamadas "stop words", palavras comuns que geralmente não contribuem significativamente para a relevância de um texto. A aplicação eficaz do cálculo TF-IDF, que combina a frequência de um termo em um documento com sua raridade em uma coleção mais ampla de documentos, permitiu-nos identificar as palavras mais importantes em um contexto específico, melhorando a precisão da busca.

Embora tenhamos obtido sucesso na construção do Índice Remissivo e na indexação das obras literárias selecionadas, reconhecemos a presença de um desafio técnico significativo relacionado ao tratamento de caracteres acentuados na língua portuguesa. Este desafio afeta a precisão da busca de palavras acentuadas e representa uma oportunidade importante de melhoria em trabalhos futuros.

Este projeto não apenas nos permitiu aplicar princípios de Tipos Abstratos de Dados (TAD) e técnicas de armazenamento, incluindo dicionários estáticos e dinâmicos, mas também nos desafiou a enfrentar questões de processamento de linguagem natural, o que é fundamental em muitos contextos de análise de texto.

Em suma, este estudo nos levou a criar uma ferramenta valiosa para a organização e recuperação de conhecimento em documentos extensos, resolvendo os desafios remanescentes e refinando nosso Índice Remissivo para atender às necessidades cada vez mais complexas de processamento de texto e busca de informações.