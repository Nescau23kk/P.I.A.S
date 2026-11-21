#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 100
#define MAX_CATEG 10
#define TAM_NOME 50
#define TAM_CATEG 30

// VETOR DE CATEGORIAS
char categoria[MAX_CATEG][TAM_CATEG];
int total_categoria = 0;

// VETORES PARALELOS DE PRODUTOS
char nome[MAX_PROD][TAM_NOME];
int categoria_produto[MAX_PROD];
int estoque[MAX_PROD];
float precos[MAX_PROD];
int compra[MAX_PROD] = {0};
int total_produtos = 0;

// FUNCOES UTILITARIAS

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

void mostrar_logo() {
    FILE *arquivo = fopen("logo.txt", "r");

    if (arquivo == NULL) {
        arquivo = fopen("logo.txt", "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "=======================================\n");
            fprintf(arquivo, " Vital Bites - Lanches e Sucos Naturais\n");
            fprintf(arquivo, "=======================================\n");
            fprintf(arquivo, "       Da natureza para sua mesa!\n");
            fclose(arquivo);
            arquivo = fopen("logo.txt", "r");
        }
    }

    if (arquivo != NULL) {
        char linha[128];
        while (fgets(linha, sizeof(linha), arquivo) != NULL)
            printf("%s", linha);
        fclose(arquivo);
    }
    printf("\n");
}

// CADASTRO E LISTAGEM DE CATEGORIAS

void cadastrar_categoria() {
    limpar_tela();
    mostrar_logo();
    printf("--- NOVA CATEGORIA ---\n");

    if (total_categoria >= MAX_CATEG) {
        printf("[AVISO] Limite de %d categorias atingido!\n", MAX_CATEG);
        pausar();
        return;
    }

    printf("Nome da categoria: ");
    fgets(categoria[total_categoria], TAM_CATEG, stdin);
    categoria[total_categoria][strcspn(categoria[total_categoria], "\n")] = '\0';

    printf("Categoria cadastrada com o codigo ID: %d\n", total_categoria);
    total_categoria++;
    pausar();
}

void listar_categorias() {
    printf("\n--- CATEGORIAS DISPONIVEIS ---\n");

    if (total_categoria == 0) {
        printf("(Nenhuma categoria cadastrada ainda)\n");
        return;
    }

    for (int i = 0; i < total_categoria; i++)
        printf("[%d] %s\n", i, categoria[i]);
}

// CADASTRO E LISTAGEM DE PRODUTOS

void repor_estoque() {
    int id, quantidade;

    listar_produtos();

    printf("\nDigite o ID do produto: ");
    scanf("%d", &id);

    if (id < 1 || id > total_produtos) {
        printf("ID invalido!\n");
        pausar();
        return;
    }

    printf("Quantidade que deseja adicionar: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
    } else {
        estoque[id - 1] += quantidade;
        printf("\nEstoque atualizado com sucesso!\n");
        printf("Novo estoque de %s: %d\n",
               nome[id - 1], estoque[id - 1]);
    }

    while (getchar() != '\n');
    pausar();
}

void cadastrar_produto() {
    int cod_categ;

    limpar_tela();
    mostrar_logo();
    printf("--- CADASTRAR PRODUTO (%d de %d) ---\n", total_produtos + 1, MAX_PROD);

    if (total_categoria == 0) {
        printf("[ERRO] Cadastre ao menos uma categoria antes de adicionar produtos!\n");
        pausar();
        return;
    }

    if (total_produtos >= MAX_PROD) {
        printf("[AVISO] Limite maximo de produtos atingido!\n");
        pausar();
        return;
    }

    printf("Nome do produto: ");
    fgets(nome[total_produtos], TAM_NOME, stdin);
    nome[total_produtos][strcspn(nome[total_produtos], "\n")] = '\0';

    listar_categorias();

    do {
        printf("Digite o codigo da categoria correspondente: ");
        scanf("%d", &cod_categ);
        while (getchar() != '\n');

        if (cod_categ < 0 || cod_categ >= total_categoria)
            printf("Codigo invalido! Escolha um dos numeros da lista.\n");
    } while (cod_categ < 0 || cod_categ >= total_categoria);

    categoria_produto[total_produtos] = cod_categ;

    printf("Quantidade em estoque: ");
    scanf("%d", &estoque[total_produtos]);

    printf("Preco unitario (R$): ");
    scanf("%f", &precos[total_produtos]);
    while (getchar() != '\n');

    total_produtos++;
    printf("\nProduto cadastrado com sucesso!\n");
    pausar();
}

void listar_produtos() {
    limpar_tela();
    mostrar_logo();

    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado ate o momento.\n");
        pausar();
        return;
    }

    printf("============================= LISTA DE PRODUTOS =============================\n");
    printf("%-4s | %-20s | %-16s | %-8s | %-10s\n",
           "ID", "Nome", "Categoria", "Estoque", "Preco");
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < total_produtos; i++) {
        printf("%-4d | %-20s | %-16s | %-8d | R$ %8.2f\n",
               i + 1, nome[i], categoria[categoria_produto[i]],
               estoque[i], precos[i]);
    }
    printf("=============================================================================\n");
    pausar();
}

// CARDAPIO, PEDIDOS E CARRINHO

void mostra_tipo() {
    int escolha;

    listar_categorias();
    if (total_categoria == 0) return;

    printf("\nEscolha a categoria: ");
    scanf("%d", &escolha);
    while (getchar() != '\n');

    if (escolha < 0 || escolha >= total_categoria) {
        printf("Categoria invalida!\n");
        return;
    }

    printf("\n--- %s ---\n", categoria[escolha]);
    for (int i = 0; i < total_produtos; i++) {
        if (categoria_produto[i] == escolha)
            printf("%d - %s | R$ %.2f | Estoque: %d\n",
                   i + 1, nome[i], precos[i], estoque[i]);
    }
}

void comprasCarrinho() {
    float valorTotal = 0;

    for (int i = 0; i < total_produtos; i++) {
        if (compra[i] != 0) {
            float pagar = compra[i] * precos[i];
            printf("\n%d- %s -- %d\n -- valor a pagar %.2f\n",
                   i + 1, nome[i], compra[i], pagar);
            valorTotal += pagar;
        }
    }

    printf("\nO valor total e: R$ %.2f\n", valorTotal);
}

void fazerPedido() {
    int produto, quantidade, resposta;

    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        pausar();
        return;
    }

    do {
        listar_produtos();

        printf("\nEscolha o ID do produto desejado: ");
        scanf("%d", &produto);
        printf("Digite a quantidade desejada: ");
        scanf("%d", &quantidade);
        while (getchar() != '\n');

        produto--;

        if (produto < 0 || produto >= total_produtos) {
            printf("Produto invalido!\n");
        } else if (quantidade <= 0 || quantidade > estoque[produto]) {
            printf("Quantidade invalida ou estoque insuficiente!\n");
        } else {
            compra[produto] += quantidade;
            estoque[produto] -= quantidade;
            printf("Produto adicionado ao carrinho!\n");
        }

        printf("\nDeseja fazer outro pedido? Digite 1 para sim e 0 para nao: ");
        scanf("%d", &resposta);
        while (getchar() != '\n');

    } while (resposta != 0);
}

// SALVAR E CARREGAR DADOS EM TXT

void salvar_dados() {
    FILE *arq_categ = fopen("categorias.txt", "w");
    FILE *arq_prod = fopen("loja.txt", "w");

    limpar_tela();
    mostrar_logo();

    if (arq_categ == NULL || arq_prod == NULL) {
        printf("[ERRO] Nao foi possivel abrir os arquivos para salvar.\n");
        if (arq_categ != NULL) fclose(arq_categ);
        if (arq_prod != NULL) fclose(arq_prod);
        pausar();
        return;
    }

    for (int i = 0; i < total_categoria; i++)
        fprintf(arq_categ, "%s\n", categoria[i]);

    for (int i = 0; i < total_produtos; i++)
        fprintf(arq_prod, "%s;%d;%d;%.2f\n",
                nome[i], categoria_produto[i], estoque[i], precos[i]);

    fclose(arq_categ);
    fclose(arq_prod);

    printf("Categorias e produtos salvos com sucesso nos arquivos TXT!\n");
    pausar();
}

void carregar_dados() {
    FILE *arq_categ;
    FILE *arq_prod;

    limpar_tela();
    mostrar_logo();

    total_categoria = 0;
    arq_categ = fopen("categorias.txt", "r");

    if (arq_categ != NULL) {
        while (total_categoria < MAX_CATEG &&
               fgets(categoria[total_categoria], TAM_CATEG, arq_categ) != NULL) {
            categoria[total_categoria][strcspn(categoria[total_categoria], "\n")] = '\0';
            total_categoria++;
        }
        fclose(arq_categ);
    }

    total_produtos = 0;
    arq_prod = fopen("loja.txt", "r");

    if (arq_prod != NULL) {
        while (total_produtos < MAX_PROD &&
               fscanf(arq_prod, " %49[^;];%d;%d;%f",
                      nome[total_produtos],
                      &categoria_produto[total_produtos],
                      &estoque[total_produtos],
                      &precos[total_produtos]) == 4) {
            total_produtos++;
        }
        fclose(arq_prod);
    }

    printf("Dados carregados: %d categoria(s) e %d produto(s).\n",
           total_categoria, total_produtos);
    pausar();
}

// CONTA DO FUNCIONARIO

void conta_func() {
    int opcao;

    do {
        limpar_tela();
        mostrar_logo();

        printf("--- CONTA FUNCIONARIO ---\n");
        printf("1. Cadastrar categoria\n");
        printf("2. Cadastrar produto\n");
        printf("3. Listar produtos\n");
        printf("4. Salvar dados em TXT\n");
        printf("5. Carregar dados de TXT\n");
        printf("6. Repor estoque\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1: cadastrar_categoria(); break;
            case 2: cadastrar_produto(); break;
            case 3: listar_produtos(); break;
            case 4: salvar_dados(); break;
            case 5: carregar_dados(); break;
            case 6: repor_estoque(); break;
            case 0: break;
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while (opcao != 0);
}

void entrarConta() {
    int resposta;

    printf("\nVoce deseja entrar em qual conta?\n");
    printf("1. Conta Funcionario\n");
    printf("2. Conta Cliente\n");
    scanf("%d", &resposta);
    while (getchar() != '\n');

    if (resposta == 1)
        conta_func();
    else if (resposta == 2)
        printf("\nBem-vindo(a) a Vital Bites!\n");
    else
        printf("\nOpcao invalida!\n");
}

// MENU PRINCIPAL

void iniciarSistema() {
    int opcao = 0;

    do {
        limpar_tela();
        mostrar_logo();

        printf("1. Ver cardapio\n");
        printf("2. Fazer pedido\n");
        printf("3. Acessar carrinho\n");
        printf("4. Acessar Conta\n");
        printf("5. Sair\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                mostra_tipo();
                pausar();
                break;
            case 2:
                fazerPedido();
                break;
            case 3:
                comprasCarrinho();
                pausar();
                break;
            case 4:
                entrarConta();
                break;
            case 5:
                printf("\nObrigado por utilizar a Vital Bites! Volte sempre!\n");
                break;
            default:
                printf("\nOpcao invalida, tente novamente!\n");
                pausar();
                break;
        }
    } while (opcao != 5);
}

int main() {
    iniciarSistema();
    return 0;
}
