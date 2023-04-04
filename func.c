#include "func.h"

void inicializaLugares(char matriz[LIN][COL]){
    int i, j;

    for(i = 0; i < LIN; i++){
        for(j = 0; j < COL; j++){
            matriz[i][j] = 'O';
        }
    }
}

void inicializaClientes(Cliente clientes[LIN*COL]){
    for(int i = 0; i < LIN*COL; i++){
        clientes[i].codigo = -1;
    }
}

void mostraLugares(char matriz[LIN][COL]){
    int i, j;
    
    printf("\t");

    for(i = 0; i < COL; i++){
        printf("%d\t", i+1);
    }

    printf("\n\n");

    for(i = 0; i < LIN; i++){
        printf("%d\t", i+1);

        for(j = 0; j < COL; j++){
            printf("%c\t", matriz[i][j]);
        }

        printf("\n\n");
    }
}

void menu(){
    int user, posicao=0;
    char matriz[LIN][COL];
    Cliente clientes[LIN*COL];

    inicializaClientes(clientes);
    inicializaLugares(matriz);

    do{
        system("clear");
        mostraLugares(matriz);
        printf("\n\n=================================================================\n\n");
        printf("O que deseja fazer?\n");
        printf("1 - Incluir\n");
        printf("2 - Pesquisar\n");
        printf("3 - Cancelar\n");
        printf("4 - Alterar\n");
        printf("5 - Mostrar poltronas reservadas\n");
        printf("6 - Sair\n");

        scanf("%d", &user);

        switch(user){
            case 1:
                 while(clientes[posicao].codigo != -1){
                    posicao++;
                }
                clientes[posicao] = cadastro(matriz, posicao);
                matriz[clientes[posicao].p.x - 1][clientes[posicao].p.y - 1] = 'X';
                break;
            case 2:
                pesquisar(clientes);
                break;
            case 3:
                int aux;
                aux = cancelar(clientes);
                if(aux != -1){
                    matriz[clientes[aux].p.x - 1][clientes[aux].p.y - 1] = 'O';
                    posicao = 0;
                }
                break;
            case 4:
                alterar(clientes, matriz);
                break;
            case 5:
                mostraTodosClientes(clientes);
                break;
            case 6:
                break;
            default:
                printf("Opção inválida\n");
        }
    }while(user != 6);
}

Cliente cadastro(char matriz[LIN][COL], int pos){
    Cliente cliente;
    int valida = 0;

    printf("Digite seu nome: ");
    scanf("%s", cliente.nome);

    do{
        printf("Digite seu CPF: ");
        scanf("%s", cliente.cpf);
        valida = validarCPF(cliente.cpf);
    }while(valida == 0);
    do{
        printf("Telefone (Sem ddd): ");
		scanf("%ld/n", &cliente.telefone);

        valida = validarTelefone(cliente.telefone);
    }while(valida == 0);
    do{
        printf("Sexo (M/F): ");
        scanf("%s", &cliente.sexo);

        if(cliente.sexo == 'M' || cliente.sexo == 'F')
            valida = 1;
        else{
            printf("Só pode digiter M ou F.\n");
            valida = 0;
        }
    }while(valida == 0);
    do{
        printf("Digite sua data de nascimento(dia/mes/ano): ");
        scanf("%d/%d/%d", &cliente.data.dia, &cliente.data.mes, &cliente.data.ano);

        valida = validarNasc(cliente.data.dia, cliente.data.mes, cliente.data.ano);
    }while(valida == 0);
    do{
        printf("Qual poltrona deseja?\n");
        cliente.p.x = pegaLinha();
        cliente.p.y = pegaColuna();

        if(matriz[cliente.p.x - 1][cliente.p.y - 1] == 'X'){
            printf("Local ocupado.\n");
            valida = 0;
        }
        else{
            valida = 1;
        }
    }while(valida == 0);

    cliente.codigo = pos + 1000;
    //imprimeClientes(cliente);

    return cliente;
}

int validarCPF(char *cpf){
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11){
        printf("CPF inválido!\n");
        return 0;
    }
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0)){
        printf("CPF inválido!\n");
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    }
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2){
            printf("CPF inválido!\n");
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
        }
    }
    return 1;
}

int validarTelefone(long int tel){
    int cont, aux, valido;

        aux = tel;
		cont = 0;

		while(aux != 0){
			aux /= 10;
			cont++;
		}

		if(cont != 9){
            printf("Telefone inválido.\n");
			valido = 0;
		}
		else{
			valido = 1;
		}

        return valido;
}

int validarNasc(int dia, int mes, int ano){
    if(dia < 0 || mes < 0 || ano < 0 || dia > 31 || mes > 12){
        printf("Data inválida.\n");
        return 0;
    }
    else if(mes == 2 && dia > 29){
        printf("Data inválida.\n");
        return 0;
    }
    else{
        return 1;
    }
}

int pegaLinha(){
    int linha, valido;

    do{
        printf("Linha: ");
        scanf("%d", &linha);

        if(linha > LIN || linha < 0){
            printf("Linha inválida.\n");
            valido = 0;
        }
        else{
            valido = 1;
        }
    }while(valido == 0);

    return linha;
}

int pegaColuna(){
    int coluna, valido;

    do{
        printf("Coluna: ");
        scanf("%d", &coluna);

        if(coluna > LIN || coluna < 0){
            printf("Coluna inválida.\n");
            valido = 0;
        }
        else{
            valido = 1;
        }
    }while(valido == 0);

    return coluna;
}

void pesquisar(Cliente clientes[LIN*COL]){
    int user, encontrou;
    
    do{
        printf("Pesquisar com o que?\n");
        printf("1 - CPF\n");
        printf("2 - Código\n");
        printf("3 - Sair\n");
        scanf("%d", &user);

        switch(user){
            case 1:
                char aux[11];
                encontrou = 0;

                printf("Digite o CPF: ");
                scanf("%s", aux);

                for(int i = 0; i < LIN*COL; i++){
                    if(strcmp(aux, clientes[i].cpf) == 0 && clientes[i].codigo != -1){
                        imprimeClientes(clientes[i]);
                        encontrou = 1;
                        break;
                    }
                }
                if(!encontrou){
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 2:
                int aux1;
                encontrou = 0;

                do{
                    printf("(Entre 1000-1400)\n");
                    printf("Digite o código: ");
                    scanf("%d", &aux1);
                }while(aux1 < 1000 || aux1 > 1400);

                for(int i = 0; i < LIN*COL; i++){
                    if(aux1 == clientes[i].codigo){
                        imprimeClientes(clientes[i]);
                        encontrou = 1;
                        break;
                    }
                }

                if(!encontrou){
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 3:
                break;
            default:
                printf("Número inválido.\n");
        }
    }while(user != 3);
}

void imprimeClientes(Cliente cliente){
    printf("Nome: %s\n", cliente.nome);
    printf("Sexo: %c\n", cliente.sexo);
    printf("Data Nascimento: %d/%d/%d\n", cliente.data.dia, cliente.data.mes, cliente.data.ano);
    printf("Poltrona: %d-%d\n", cliente.p.x, cliente.p.y);
    //printf("CPF: %s\n", cliente.cpf);
}

int cancelar(Cliente clientes[LIN*COL]){
    int codigo;

    printf("Digite o código do cliente: ");
    scanf("%d", &codigo);

    if(clientes[codigo-1000].codigo == -1){
        printf("Cliente não encontrado.\n");
        return -1;
    }
    else{
        clientes[codigo-1000].codigo = -1;
        printf("Cliente cancelado com sucesso.\n");
        return codigo-1000;
    }
}

void alterar(Cliente clientes[LIN*COL], char matriz[LIN][COL]){
    int cod, x, y, valida;

    printf("Digite o código: ");
    scanf("%d", &cod);
    cod = cod - 1000;

    if(clientes[cod].codigo == -1){
        printf("Cliente não encontrado.\n");
        return;
    }
    else{
        matriz[clientes[cod].p.x - 1][clientes[cod].p.y - 1] = 'O';
        do{
            printf("Para qual poltrona deseja ir?\n");
            clientes[cod].p.x = pegaLinha();
            clientes[cod].p.y = pegaColuna();

            if(matriz[clientes[cod].p.x - 1][clientes[cod].p.y - 1] == 'X'){
                printf("Local ocupado.\n");
                valida = 0;
            }
            else{
                valida = 1;
            }
        }while(valida == 0);

        matriz[clientes[cod].p.x - 1][clientes[cod].p.y - 1] = 'X';
    }
}

void mostraTodosClientes(Cliente clientes[LIN*COL]){
    int encontrou = 0;

    for(int i = 0; i < LIN*COL; i++){
        if(clientes[i].codigo != -1){
            encontrou = 1;
            imprimeClientes(clientes[i]);
            printf("============================================\n");
        }
    }

    if(!encontrou){
        printf("Nenhum cliente.\n");
    }
}