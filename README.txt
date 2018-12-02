#Autores:
    -Arnaldo Barbosa Eloi de Souza
        Implementação aprimorada dos filtros nas buscas.
    
    -Nathanael Derick Medeiros do Nascimento
        Listagem de dados aprimorada com tamanho dinâmico das colunas.

    *É importante dizer que, embora algumas funcionalidades tenham sido feitas em maioria por algum dos integrantes, todos tiveram contribuição igualitária no todo do trabalho. Assim, algumas funções foram completamente implementadas por um ou por outro, entretanto, em outras foi necessára contribuição múltua. 
    
#Uso de recursos da linguagem C:
    Foram utilizados todos os conhecimentos ensinados no decorrer do semestre, incluindo o uso de funções recursivas (algumas funções de string.c), uso de typedefs e structs, alocação de memória, entre outros.
    *Optou-se por não utilizar a stderr, visto que as mensagens de erro estão usando a saída padrão.
     
#O que foi feito?

    -Funcionalidades Solicitadas
        Todas as funcionalidades solicitadas foram implementadas.

    -Funcionalidades Extras:
        1) Banco de Dados:
            -Descrição:
                Nosso SGBD divide as tabelas por bancos de dados. Cada tabela (ou conjunto de tabelas) tem um banco de dados associado.
            -Justificativa:
                Agrupar as tabelas por contextos é amplamente utilizado no mercado, pois cada sistema possui um conjunto de tabelas para seu determinado contexto.

        2) Sintaxe própria:
            -Descrição:
                Sintaxe própria que lê comandos "verbais" e os interpretam executando funções.
            -Justificativa:
                Com a sintaxe própria, é possível entender de frente as funcionalidade digitadas, bem como exportar comandos para diferentes contextos de aplicação.

        3) Filtros empilhados:
            -Descrição:
                No nosso banco de dados, é possível agrupar vários filtros e selecionar os dados com mais de uma condição (os dados, por exemplo, com id>=5 E com o nome que comece com 'A').
            -Justificativa:
                Poder buscar com mais de um filtro torna a pesquisa mais exata.
        
        4) Apagar dados em massa:
            -Descrição:
                É possível apagar vários dados de uma só vez utilizando filtros.
            -Justificativa:
                Muitas vezes é necessário apagar vários dados, e fazê-lo um a um conclui-se como uma grande perda de tempo. Apagar vários dados de uma só vez utilizando fitros é ideal, pois economiza tempo.

        5) Menu help:
            -Descrição:
                Caso o usuário esqueça como utilizar a sintaxe do SGBD, 'help' traz as principais funções para eles, como uma mini documentação.
            -Justificativa:
                Caso o usuário esqueça como utilizar a sintaxe do SGBD, 'help' traz as principais funções para eles, como uma mini documentação.
        
        6) Listar todos as tabelas por banco de dados:
            -Descrição:
                Como o sistema é organizado em banco de dados, a listagem por banco de dados acaba sendo importante.
            -Justificativa:
                É importante saber de que banco cada tabela pertence, pois cada um tem seu contexto.
        
        7) Importar e executar arquivo externo de funções no sistema:
            -Descrição:
                É possível escrever todas as funções desejadas num arquivo externo e importá-las para o programa, executando as funções uma a uma.
            -Justificativa:
                Muitas vezes, escrever em um editor externo de preferência as funções é mais interessante que escrever no terminal, poder executar o mesmo conjunto de funções várias vezes também é uma possibilidade para testes.
        
        8) Alterar tabela após criação:
            -Descrição:
                É possível alterar a assinatura de uma tabela após sua criação, i.e., adicionar, remover ou editar um tipo de alguma coluna.
            -Justificativa:
                Muitas vezes o tipo criado originalmente já não é mais válido para um novo contexto.
        
        9) Busca aprimorada para strings:
            -Descrição:
                Separação na busca por strings utilizando as opções de ignorar o 'case' das letras, opções de busca no fim das strings e no início das strings.
            -Justificativa:
                Aprimorar a busca das strings torna mais eficaz a busca pelos dados desejados.

        10) Listagem aprimorada dos dados:
            -Descrição:
                É possível listar apenas algumas colunas da tabela desejada, omitindo as outras indesejadas. Além disso, a listagem tem largura dinâmica para as palavras de cada string (a maior string de uma tabela define seu tamanho).
            -Justificativa:
                Às vezes, não queremos nos atrapalhar com muitos dados na leitura de arquivos, possibilitando focar nas colunas que realmente importam para o contexto.

#O que faria de forma diferente:

    -Modularização mais organizada do código, visto a atual repetição desnecessária de comandos nas funções de filtro. 
    -Implementação completa do tipo de dados Date, para datas.
    -Implementação do update para linhas das tabelas.
    -Tratamento mais eficaz de casos de erros (quando a sintaxe não ocorre como esperado).

#Como compilar o projeto:
    O projeto foi testado no GCC 7.3.0 e no GCC 7.2.0, mas acreditamos que funcione em outras versões mais recentes, embora não tenha sido testado.

    Para compilar, vá até a pasta raíz do projet e digite no terminal:
        gcc main.c libs/common.c libs/database_operations.c libs/colors.c libs/strings.c -o exec -g -W
    