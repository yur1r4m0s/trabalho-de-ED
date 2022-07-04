
int menu(){
    add_funcionario("Gilmario", 123, 12, 3);
    add_funcionario("Alonso", 125, 25, 2);
    add_funcionario("Ze", 888, 88, 2);
    add_funcionario("Yuri", 124, 24, 1);
    add_funcionario("Paula", 126, 26, 1);
    add_funcionario("Felipe", 222, 22, 1);
    add_funcionario("Levi", 555, 55, 1);
    add_funcionario("Alice", 333, 33, 1);
    system("clear");
    int cpf_resp;
    int opc = -1;
    int cont = 0;
    char nome_fun[100];
    int id, cpf_fun, senha_fun, cargo;

    while(opc != 0){
        printf("\n[ 1 ] Cadastrar encomenda\n[ 2 ] Mostrar encomendas\n[ 3 ] Deletar encomenda\n[ 4 ] Ver fila de prioridade\n[ 5 ] Remover da fila\n[ 6 ] Cadastrar funcionario\n[ 0 ] Sair\nEscolha uma opcao >> ");
        scanf("%d", &opc);
        printf("\n");
        switch(opc){
            case 1:
                system("clear");
                if(raiz == NULL)
                    id = 500;
                else if(cont % 2 == 0)
                    id = mais500();
                else
                    id = menos500();

                cont++;
                cadastrar_encomenda(id);
                break;
            case 2:
                system("clear");
                if(raiz != NULL){
                    printf("----ENCOMENDAS----\n");
                    printf(VERMELHO"-------------------------------"RESET"\n");
                    in_ordem(raiz);
                    cont = 1;
                    while(cont != 0){
                        printf(VERMELHO"Digite 0 para sair: "RESET);
                        scanf("%d", &cont); 
                    }      
                    system("clear");
                }else{
                    printf(VERMELHO"Nenhuma encomenda cadastrada"RESET"\n");
                }
                break;
            case 3:
                if(raiz != NULL){
                    system("clear");
                    cpf_resp = login(2);
                    if(cpf_resp > 1){
                        printf("\n----ENCOMENDAS----\n");
                        printf(VERMELHO"-------------------------------"RESET"\n");
                        in_ordem(raiz);
                        printf("\n----REMOVER----\n");
                        printf("Digite o id: ");
                        scanf("%d", &id);
                        
                        printf("\n");
                        system("clear");

                        raiz = remover(raiz, id, cpf_resp);
                    }else if(cpf_resp == 0){
                        system("clear");
                        printf(VERMELHO"Cpf ou senha incorreto"RESET"\n");
                    }
                }else{
                    system("clear");
                    printf(VERMELHO"Nenhuma encomenda cadastrada"RESET"\n");
                }
                break;
            case 4:
                system("clear");
                ver_fila();
                int i = 1;
                if(tam_fila > 0){
                    while(i != 0){
                        printf(VERMELHO"Digite 0 para sair: "RESET);
                        scanf("%d", &i);
                    }
                    system("clear");
                }
                break;
            case 5:
                system("clear");
                if(tam_fila == 0){
                    printf(VERMELHO"A fila esta vazia"RESET"\n");
                }else{
                    cpf_resp = login(1);
                    if(cpf_resp > 1){
                        remover_fila();
                    }else if(cpf_resp == 0){
                        system("clear");
                        printf(VERMELHO"Cpf ou senha incorrreto"RESET"\n");
                    }
                }
                break;
            case 6:
                system("clear");
                cpf_resp = login(3);
                if(cpf_resp > 1){
                    printf("\n----CADASTRAR FUNCIONARIO----\n\n");
                    printf("Nome: ");
                    scanf(" %[^\n]s",nome_fun);
                    printf("Cpf: ");
                    scanf("%d", &cpf_fun);
                    printf("Senha: ");
                    scanf("%d", &senha_fun);
                    printf("\n1- Transportador\n2- Secretario\nCargo >> ");
                    scanf("%d", &cargo);

                    if(buscar_resp(cpf_fun) == "0"){
                        add_funcionario(nome_fun, cpf_fun, senha_fun, cargo);
                        system("clear");
                        printf(VERDE"Funcionario Cadastrado"RESET"\n");
                    }else{
                        system("clear");
                        printf(VERMELHO"Esse funcionario ja esta cadastrado"RESET"\n");
                    }
                }else if(cpf_resp == 0){
                    system("clear");
                    printf(VERMELHO"Cpf ou senha incorrreto"RESET"\n");
                }    
                break;
            case 0:
                return 0;
                break;
            default:
                system("clear");
                printf(VERMELHO"Opção Invalida"RESET"\n");
                break;
        }
    }
}
