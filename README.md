# SGBD ITP

Projeto orientado pela professora Marjory Cristiany da Costa Abreu com o intuito de criar um banco de dados utilizando C capaz de armazenar, consultar e deletar dados.

## Utilizando o SGBD

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Pré-requisitos

O projeto foi desenvolvido e testado no Deepin com a seguite versão do GCC:

```
gcc version 7.3.0 (Debian 7.3.0-19) 
```
O projeto não foi testado em versões anteriores; portanto, use por sua conta e risco. Espera-se que em versões superiores não haja problemas para compilar o projeto.

### Instalação

Passos para a instalação

Descompacte o projeto em uma pasta com as permissões de leitura e escrita e execute o compile

```
./compile
```

Para iniciar a aplicação, use o comando

```
./exec
```

Se tudo deu certo até agora, já é possível utilizar todos os comandos do SGBD.

## Utilizando o sistema

O sistema permite várias operações de banco. Verifique abaixo a sintaxe dessas operações.

### Criação de Banco de Dados

Para guardar dados, precisaremos de uma tabela. Para criar uma tabela, precisaremos de um banco.
Para criar um banco use, durante a execução 

```
create database nome_do_banco 
```
Substitua nome_do_banco pelo nome do banco que você deseja criar.

### Criação de Tabelas

Para criar uma tabela use, durante a execução 

```
create table nome_do_tabela (int id pk, string name, char caracter, double account, float account_data, ...) 
```
*...* Crie quantas colunas achar convenientes na tabela.

O uso de uma *Primary Key* ou *Chave Primária* (pk) é obrigatória e deve ser do tipo inteiro. Note que a chave primária é única.
Os tipos de dados permitidos pelo SGBD são *char*, *int*, *double*, *float* e *string* e devem sempre estar antes do nome da coluna.

Quaisquer outros tipos de dados utilizados ou erros de sintaxe acarretarão na não criação da tabela no banco desejado.


### Listar todas as Tabelas

Para listar todas as tabelas execute, durante a execução 

```
list tables
```

Serão listadas as pastas equivalentes aos bancos de dados e os arquivos equivalentes às tabelas.


## Autores

* **Arnaldo Souza** - *Autor* - [Arnaldoeloi](https://github.com/arnaldoeloi)
* **Nathanael Derick** - *Autor* - [DerickMaster](https://github.com/derickmaster)

## Licença

O projeto é livre para consulta e estudos.

