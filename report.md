# Report of each commit od alterations
Objetivo desse *README* é fazer um relatório do commit, assim apresentando as principais alterações/criações no código, além de descrever os problemas que encontrados no momento de implementar as alterações e criações.
# About Commit

1. Separar as structs que definem os nó na árvore;
2. Criar a árvore AVL para o registro de usuários e erros críticos que estavam despecebidos no código AVL
3. Criação da lista dupĺamente encadeada para o registro de livro/Usuário;

Date: nov/05/2026

## Separating structs
&nbsp; Nesse trecho foi separado o parte principal do código em que structs que definem a estrutura das arvore foram colocadas em um arquivo e definido como uma biblioteca externa ao c, e incluida nos arquivos work.c e userBib.c;

&nbsp; Outrossim, foi alterado a propriedade booleana para dizer se o livro estava disponível ou não, isto é, pelo fato de já haver uma variável de controle para isto a variável "amountLent", por conseguinte falando com o professor ele sugerio que seria melhor dessa forma, incluse ápos a retirada desse vetor foi subtituida por um ponteiro para uma lista duplamente encadeada, em que será implementada futuramente.

&nbsp; Ainda, é possível ter problema nesse metódo que foi pensado da lista duplamente encadeada, no qual para fazer o delete a última ação a ser tomada deve ser a de apagar a ponteiro desse dado, por que se fizer a deleção primeiro os outros ponteiros da lista e árvore são perdidos e ocorre um segmentation fault por tentar acessar memória invalida.

## Arbor AVL user and error in the code
&nbsp; Para a criação da árvore foi tranquila, à implementação do user foi adicionada as mesmas funções do livro, mas na hora de verificar qual a string maior foi usada uma variavel, além de o getBalance da função ser reutilizável para inserção e deleção. Um dois principais erros e que a árvore não estava balanceando, isto pelo fato de o int comparador estar invertido com o outro, além de dos right e left estarem trocados em outra parte. 

&nbsp; Um dos erros que mais me chamou atenção foi na hora de apagar a memória, na qual a função delete estava fazendo um double free, isso acontecia porque eu mandava apagar um ponterio duas vezes, ao contrário do que havia visto em sala que verificava o dado, trocava os dados e mandava apagar e não a ref de um ponteiro para apagar duas vezes como estava implementado no código, assim para solucinoar só foi preciso de uma variável auxiliar para fazer a troca como se faz para alterar numa heap.

date: nov/06/2026

## list doubly for the registry

&nbsp; O desenvolvimento das funções, criação, inserção, e deleção, para o fim de registro de livros para o usuário que retirou, nesse mesmo inserir esse no livro os usuários que retiraram. Por consequência, a implementção desse registro foi efetuada por meio de uma lista duplamente encadeada, por tanto a inserção desses elementos ocorreu por meio de manipulação de ponteiros, pois passava o endereço do usuários da árvore para uma lista encadeada onde recebia esse ponteiro por referência. Entretanto, para apagar alguns dados tem problema de que deve apagar em uma ordem específica para não perder os dados na hora errada. Por fim, estás foram as principais mudanças/atualizações realizadas no código.

date: nov/07/2026

&nbsp;  Implementação das estruturas de devolução do livro/usuário, para além disso foi também desenvolvido a função de que quando um usuário ou livro é removido remove todos os registros desse para não ter o vazamento de memória

date:nov/08/2026 - nov/11/2026 

&nbsp; Nesse periódo foi separdo estruturas por arquivo .h verificando cada etapa do processo da biblioteca pensando primeiro em adicionar elementos e depois remover, então foi criado as funções de adição, após isso foi pensado na ideia de fazer com que as listas encadeadas usem ponteiros cruzado fazendo a busca instantânea assim a remoção de elementos de forma eficiente;