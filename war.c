// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

//============= NÍVEL NOVATO 27/04/2026=====================

//----------------------------BIBLIOTECAS---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define tString 30 //#define para tornar esse valor uma constante ==> não termina com ;

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorio {  
    char nome[tString];
    char cor[tString];
    int Ntropas;
};
struct territorio *pterritorio; //ponteiro do struct territorio

//Definição de variáveis
int opcao;
int Nterritorio = 0;
int Nterritorios = 1;

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

void alocarMapa(){
    pterritorio = (struct territorio*) calloc(Nterritorios, sizeof(struct territorio));
    if (pterritorio == NULL) {
        printf("Erro ao alocar memória. \n");
    }
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

void exibirMenuPrincipal(){
    printf("-----------------------------\n");
    printf("MENU CADASTRO DE TERRITÓRIOS\n");
    printf("-----------------------------\n");
    printf("1 - Cadastrar os territórios\n");
    printf("2 - Listar os territórios\n");
    printf("3 - Iniciar fase de ataque\n");
    printf("4 - Sair\n");
    printf("-----------------------------\n");
    scanf("%d", &opcao);
    limparBufferEntrada();
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(){
            
            if (Nterritorio >= Nterritorios) {
            printf("\nLimite de territórios atingido!\n");
            return;
            }

            printf("\n-----------------------------\n");
            printf("TERRITÓRIO %d", Nterritorio+1);
            printf("\nDigite o nome:");
            fgets(pterritorio[Nterritorio].nome, tString, stdin);
            printf("Digite a cor:");
            fgets(pterritorio[Nterritorio].cor, tString, stdin);
            printf("Quantas tropas ocupam o território:");
            scanf("%d", &pterritorio[Nterritorio].Ntropas);
            Nterritorio++;
            limparBufferEntrada();
            printf("\nPressione Enter para continuar...\n");
            
}

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(){
    if (Nterritorio == 0) {
                printf("\nNenhum território cadastrado.");
                printf("\nPressione Enter para continuar...");
            } else {
                for (int i=0; i < Nterritorio; i++) {
                printf("-----------------------------\n");
                printf("TERRITÓRIO %d", i+1);
                printf("\nnome %s", pterritorio[i].nome);
                printf("cor %s", pterritorio[i].cor);
                printf("Número de tropas %d", pterritorio[i].Ntropas);
                printf("\n-----------------------------");
                }
                printf("\nPressione Enter para continuar...");
            }
            limparBufferEntrada();
}

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(){
    free(pterritorio);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    alocarMapa();

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
    do{
        exibirMenuPrincipal();
        switch (opcao)
        {
        case 1:
            printf("\nQuantos territórios no total:");
            scanf("%d", &Nterritorios);
            alocarMapa();
            inicializarTerritorios();
            break;
        case 2:
            exibirMapa();
            break;
        case 3:
            printf("\nsaindo do sistema");
            break;
        default:
            printf("Opção inválida");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        } 
        
    } while (opcao != 3);

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    liberarMemoria();
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

