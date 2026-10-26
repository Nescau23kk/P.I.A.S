#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    //define as cores do programa
    #define COR_VERDE_BRILHANTE    "\033[92m"
    #define COR_PRETO              "\033[30m"
    #define COR_VERDE              "\033[32m"
    #define COR_BRANCO             "\033[37m"
    #define COR_PISCANTE           "\033[5m"
    #define FUNDO_VERDE_BRILHANTE  "\033[102m"
    #define COR_RESETAR            "\033[0m"
    
    char produtos [29][50] = {"sanduíche de frango", "sanduíche de atum", "sanduíche caprese", "sanduíche de queijo branco", "sanduíche vegano", "wrap natural",
    "tapioca integral", "pão de queijo fit", "wrap de vegetais", "salada no pote",
    "mix de folhas", "frango desfiado", "atum temperado", "combo leve",
    "sanduíche veggie", "wrap veggie", "salada rica", "suco detox verde",
    "suco de laranja", "suco de limão", "suco de maracujá", "suco de morango", "suco de abacaxi com hortelã", "suco de melancia",
    "brownie fit", "cookie integral", "salada de frutas", "mousse light", "açaí puro"};
    
    float precos [29] = {16.00, 17.00, 18.00, 16.00, 17.00, 16.00,
    15.00, 6.00, 15.00, 14.00,
    14.00, 15.00, 16.00, 22.00, 
    16.00, 15.00, 16.00, 12.00,
    10.00, 10.00, 11.00, 11.00, 12.00, 11.00,
    10.00, 8.00, 9.00, 11.00, 14.00};
    
    char categoria [29][35] = {"lanches naturais", "naturais leves", "porções especiais", "vegetarianos fit", "sucos", "sobremesas"};
    
    int num_categoria [29] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    
    int compra [29] = {0};
    
    int estoque [29] = {30};
    
    float pagar[29] = {0.0};
    
    
    void mostra_produto_categoria(int escolhi_a_categoria);
    
    //limpa a tela
    
    void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

    //função de abrir a conta do Funcionário
    void conta_func(){
        
        int senhaAcessoDig;
        int senhaAcesso = 83970;
        int escolha;
        
        printf("\nConta do Funcionário\n");
        printf("\nDigite a Senha de Acesso: \n");
        scanf("%d", &senhaAcessoDig);
        
        switch(senhaAcessoDig){
            
            case 83970:
            printf("\n[Acesso Permitido] Bem-vindo ao Sistema\n");
            break;
            
            default:
            printf("\n[Acesso Negado] Senha Incorreta, Saindo...\n");
            return;
        }
        
        printf("\nOpções Disponíveis: \n");
        printf("\n1. Movimentar Estoque\n");
        printf("\n2.Cadastrar Produtos\n");
        printf("\nDigite a opção desejada: \n");
        scanf("%d", &escolha);
        
        limpar_tela();
    }
    
    //função de escolher a categoria
    void mostra_tipo(){
        int escolha;
        
        printf("Escolha o produtos desejado: \n");
        for(int i = 0; i < 6; i++){
            printf("\n%d- %s \n", i, categoria[i]);
        }
        printf("\n");
        scanf("%d", &escolha);
        mostra_produto_categoria(escolha);
        
        
    }
    
    //função de mostrar os produtos
    void mostra_produto_categoria(int escolhi_a_categoria){
        for(int i = 0; i < 29; i++){
            if(num_categoria[i] == escolhi_a_categoria){
                printf("\n%d - %s\n", i, produtos[i]);
            }
        }
        
    }
    
    
    //função carregando Conta
    void entrarConta(){
        int resposta;
        
        printf("\nVocê deseja entrar em qual conta: \n");
        printf("\n1. Conta Funcionário\n");
        printf("\n2. Conta Cliente\n");
        scanf("%d", &resposta);
            
        if(resposta == 1){
            conta_func();
        }
        limpar_tela();
    }
    
    //função de mostrar compras/carrinho
    void comprasCarrinho(){
        float valorTotal = 0;
        
        for(int i = 0; i<29; i++){
            if(compra[i] != 0){
                pagar[i] = compra[i] * precos[i];
                printf("\n%d- %s --%d\n -- valor a pagar %.2f\n", i, produtos[i], compra[i], pagar[i]);
            valorTotal = valorTotal + pagar[i];
            
            }
        }
        printf("\nO valor total é: R$%.2f\n", valorTotal);
        
    }
    
    //função de fazer pedido
    void fazerPedido(){
        int produto;
        int quantidade;
        int resposta;
        
        do{
        printf("\nEscolha o produto desejado: \n");
        scanf("%d", &produto);
        printf("\nDigite a quantidade desejada: \n");
        scanf("%d", &quantidade);
        compra[produto] = quantidade;
        estoque[produto] = estoque[produto] - quantidade;
        printf("\nDeseja fazer o pedido de outro produto? Digite 1 para sim e 0 para não\n");
        scanf("%d", &resposta);
        
        }while (resposta != 0);
        
        
    }
    
    

    //função de Iniciar o Menu
    void iniciarSistema(){
        
        int opcao = 0;
        
        do{
        printf("\n=======================================\n");
        printf("\n Vital Bites - Lanches e Sucos Naturais \n");
        printf("\n=======================================\n");
        printf("\n    Da natureza para sua mesa!  \n");
        printf("\n");
        printf("\n1. Ver cardápio\n");
        printf("\n2. Fazer pedido\n");
        printf("\n3. Acessar carrinho\n");
        printf("\n4. Acessar Conta\n");
        printf("\n5. Sair\n");
        printf("\n Digite a opção desejada: \n");
        scanf ("%d", &opcao);
        
        switch(opcao){
            
            case 1:
            printf("\nAbrindo cardápio...\n");
            mostra_tipo();
            break;
            
            case 2:
            printf("\nPronto para fazer o melhor pedido do mundo? Vamos lá...\n");
            fazerPedido();
            break;
            
            case 3:
            printf("\nVamos dar uma olhadinha nas compras...\n");
            comprasCarrinho();
            break;
            
            case 4:
            printf("\nSinta-se em casa e entre quando quiser...\n");
            entrarConta();
            break;
            
            case 5:
            printf("\nVou sentir sua falta, então volte logo ^-^\n");
            break;
            
            default: 
            printf("\nOpção Inválida, tente novamente!\n");
            break;
             }
        }while(opcao != 5);
        
        limpar_tela();
    } 
    
    int main(){
        iniciarSistema();
        
        return 0;
    }
    