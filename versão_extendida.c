#include "../includes/minishell.h"

void	ctrl_d(char *input_line)
{	
	if (input_line == NULL)
	{
		printf("Você digitou ctrl+d, adeus!\n");
		exit(EXIT_SUCCESS);
	}
}

void	sigquit_handler(int signal)
{
	printf("\rVocê pressionou Ctrl + \\, mas esse sinal foi ignorado.\n");
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	sigint_handler(int signal)
{
	printf("\rVocê pressionou Ctrl + C, mas esse sinal foi ignorado.\n");
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}


void   ft_cd(char **args) //recebe um array de strings 'args'                       
{
    //nenhum argumento passado além do cd, então vamos para HOME
    if (args[1] == NULL)
    {
        const char *go_home = getenv("HOME");
        if (go_home != NULL) //Verificamos se conseguimos obter o caminho do diretório HOME (ou seja, se não é NULL)
        {
            if (chdir(go_home) != 0) //Se retornar um valor diferente de zero, significa que ocorreu um erro durante a mudança de diretório.
            {
                perror("cd");
            }
        }
        else
        {
            ft_putendl_fd("cd: could not determine home directory\n", 2);
        }
    }
    else if (args[1] != NULL && chdir(args[1]) != 0) //se a função chdir retornar um valor diferente de zero, isso significa que ocorreu um erro 
    {
        perror("cd");
    }
}

void    ft_echo(char **args)
{
    int i;
    int add_newline; //flag para adiconar quebra de linha
    
    i = 1;
    add_newline = 1;
    
    // Verifica se a primeira argumento é a flag -n
    if (args[i] != NULL && strcmp(args[i], "-n") == 0)
    {
        add_newline = 0; // Desativa a adição de quebra de linha. Se for 1, ativa.
        i++; // Avança para o próximo argumento
    }

    while (args[i] != NULL)
    {
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (add_newline) //
        printf("\n");
}
int	env_count_var(char **envp)
{
	int	count;

	count = 0;
	while(envp[count] != NULL)
	{
		count++;
	}
	return (count);
	
	printf("%i\n", count);
}

// função para duplicar as variáveis dentro do env
char	**env_duplicate(char **envp)
{
	int		count;
	char	**envp_copy;
	int		i;
	
	count = env_count_var(envp);
	envp_copy = (char **)malloc(sizeof(char *)*(count + 1));

	if(envp_copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while(i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
			i++;
		if(envp_copy == NULL)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
	}
	envp_copy[count] = NULL;
	return (envp_copy);
}

//função para dar free
void	envp_free(char **envp_copy)
{
	int	i;

	i = 0;
	while(envp_copy[i] != NULL)
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
}

// essa função lista as variáveis de ambiente
void    ft_env(char **envp)
{

	int	i;

	i = 0;
	while(envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	is_number(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit (char **input_line)
{
	int	arg_count;

	arg_count = count_args(input_line);
	if (arg_count > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return 0;// Não precisa retornar um valor aqui, já que a função é void
	}

    if (arg_count == 1)
    {
        ft_putendl_fd("Bye!!!", 1);
        // Não é recomendado liberar memória que não foi alocada por malloc (input_line foi lido pelo readline)
        exit(EXIT_SUCCESS);
    }

    if (!is_number(input_line[1]))
    {
        ft_putendl_fd("exit: numeric argument required", 2);
        return 0; // Mesmo aqui, não precisa retornar um valor
    }

    int exit_code = atoi(input_line[1]);
    free(input_line); // Lembre-se de liberar a memória antes de sair
    exit(exit_code);
}

void ft_pwd()
{
    char current_dir[1024];

    if(getcwd(current_dir, sizeof(current_dir)) != NULL)
    {
        printf("%s\n", current_dir);
    }
    else
        perror("getcwd");
}
int find_env_variable(char **envp_copy, const char *var_name) {
    int index = 0;
    while (envp_copy[index] != NULL) {
        if (strncmp(envp_copy[index], var_name, strlen(var_name)) == 0 && envp_copy[index][strlen(var_name)] == '=')
            return index;
        index++;
    }
    return -1; // Variável não encontrada
}

void ft_export(char ***envp_copy, char *token_args)
{
    char *equal_sign;
    char *var_name;
    int index;
    int i;
    int envp_copy_count;
    char **new_envp_copy;

    equal_sign = ft_strchr(token_args, '=');
    if (equal_sign != NULL)
    {
        *equal_sign = '\0';
        var_name = ft_strdup(token_args);

        index = find_env_variable(*envp_copy, var_name);

        if (index >= 0)
        {
            // Atualizar a variável existente
            free((*envp_copy)[index]);
            (*envp_copy)[index] = ft_strdup(token_args);
        }
        else
        {
            envp_copy_count = env_count_var(*envp_copy);
            new_envp_copy = (char **)malloc(sizeof(char *) * (envp_copy_count + 2)); // +2 para a nova variável e NULL no final

            for (i = 0; (*envp_copy)[i] != NULL; i++)
            {
                new_envp_copy[i] = ft_strdup((*envp_copy)[i]);
            }
            new_envp_copy[i] = ft_strdup(token_args);
            new_envp_copy[i + 1] = NULL;

            // Libere a memória do antigo array
            for (i = 0; (*envp_copy)[i] != NULL; i++)
            {
                free((*envp_copy)[i]);
            }
            free(*envp_copy);

            // Atualize o ponteiro para o novo array
            *envp_copy = new_envp_copy;
        }

        free(var_name);
    }
}

int main(int argc, char **argv, char **envp)
{
    char *input_line;
    signal(SIGQUIT, sigquit_handler);
    signal(SIGINT, sigint_handler);

    char    **envp_copy;

    envp_copy = envp; //para inicializar minha variável.

    while(1)
    {
        (void) argv;
        (void) envp;
        
        if(argc != 1)
            return(1);
            
        // Exibir o prompt e aguardar um comando usando readline
        input_line = readline("minishell$ ");

        if (input_line == NULL)
        {
            ctrl_d(input_line);
        }
        
        // IF BILTINS??? (fazer um arquivo só para isso e compilar em uma linha só auqi na main)

        // if (builtins?)
        char **token_args = ft_split(input_line, ' ');
        if (strcmp(token_args[0], "exit") == 0)
        {
            ft_exit(token_args);
            free(token_args[0]);
            free(token_args);
        }
        //checando se o usuário digitou pwd.
        if (strcmp(token_args[0], "pwd") == 0)
        {
            ft_pwd(token_args);
            free(token_args[0]);
            free(token_args);
        }
        if (strcmp(token_args[0], "cd") == 0)
        {
            ft_cd(token_args);
            free(token_args[0]);
            free(token_args);
        }
        if (strcmp(token_args[0], "echo") == 0)
        {
            ft_echo(token_args);
            free(token_args[0]);
            free(token_args);
        }
        // if (strcmp(token_args[0], "unset") == 0)
        // {
        //     ft_unset(envp_copy, token_args[1]);
        //     free(token_args[0]);
        //     free(token_args);
        //     envp_free(envp_copy);
        // }
        if (strcmp(token_args[0], "env") == 0)
        {
            char **envp_copy;
            envp_copy = envp; // para inicializar a função.

            ft_env(envp_copy);
            free(token_args[0]);
            free(token_args);
        }
        if (strcmp(token_args[0], "export") == 0) {
            if (token_args[1] != NULL) {
                // Se houver argumento após "export", chame a função ft_export
                ft_export(envp_copy, token_args[1]);
                free(token_args[0]);
                free(token_args);
            } else {
                // Se não houver argumentos, liste as variáveis de ambiente
                ft_env(envp_copy);
                free(token_args[0]);
                free(token_args);
            }
        }
        //if (strcmp(token_args[0], "export") == 0)
        //{
        //    if(token_args[1] != NULL)
        //    {
        //        ft_export(envp_copy, token_args[1]);
        //       free(token_args[0]);
         //       free(token_args);  
         //   }
        //}
       // else
        //{
        //    int i = 0;
         //   //verificar se o comando export foi dado argumentos
         //   if(token_args[0][0] == '\0')
           // {
                //imprimir variáveis de ambiente existentes
          //      i = 0;
          //      while(envp_copy[i] != NULL)
           //     {
           //         printf("%s\n", envp_copy[i]);
            //        i++;
            //    }
            //}
            //else
            //{
            //    ft_env(envp_copy);    
            //}
        
        if(input_line)
        {
            printf("%s\n", input_line); 
               
            // Adicionando o comando ao histórico do readline
            if (ft_strlen(input_line) > 0) //adaptar ao ft_strlen
            {
                add_history(input_line);
            }
            free(input_line);
        }
    }
    return(0);
}

