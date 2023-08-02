# minishell

Neste projeto irei construir meu próprio Shell, o MiniShell. 
O Shell é um programa que interage com o usuário por meio do terminal, obtém a entrada de um arquivo e executa uma sequência de comandos que são passados par ao Sistema Operacional.

A implementação do shell é dividida em 3 partes:
- O Parser: componente que lê a linha de comando como o "ls" e a coloca em uma estrutura de dados chamada Command Table.

- O Executor: pegará a tabela de comandos gerada pelo Parser e para cada SimpleCommand no array, ele criará um novo processo. ele também criará Pipes para comunicar a saída de um processo para a entrada do próximo. Além disso, ele redirecionará a entrada padrão, a saída padrão e o erro padrão se houver algum redirecionamento.

- O Shell Subsystems: variáveis de ambientes, caracters curingas (*, ?..), subshells.