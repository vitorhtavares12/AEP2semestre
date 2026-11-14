#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct Acao {
    int codigo;
    char escola[50];
    char dataPrevista[11];
    char publicoAlvo[50];
    char responsavel[50];
    int tema;
    int previstos;
    int efetivos;
    int situacao;
};

struct Acao acoes[MAX];
int total = 0;

const char *temas[] = {"Alimentacao saudavel", "Atividade fisica", "Saude mental",
                       "Cultura de paz", "Vacinacao", "Saude bucal", "Prevencao das violencias"};
const char *situacoes[] = {"Planejada", "Realizada", "Cancelada"};

// Le um inteiro entre min e max, repetindo ate ser valido
int lerInt(const char *msg, int min, int max) {
    char linha[50];
    int n;
    while (1) {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) exit(0);
        if (sscanf(linha, "%d", &n) == 1 && n >= min && n <= max) return n;
        printf("Valor invalido! Digite um numero de %d a %d.\n", min, max);
    }
}

// Le um texto, repetindo ate nao ficar vazio
void lerTexto(const char *msg, char *destino, int tam) {
    do {
        printf("%s", msg);
        if (fgets(destino, tam, stdin) == NULL) exit(0);
        destino[strcspn(destino, "\n")] = '\0';
        if (destino[0] == '\0') printf("Campo obrigatorio!\n");
    } while (destino[0] == '\0');
}

int buscarCodigo(int codigo) {
    for (int i = 0; i < total; i++)
        if (acoes[i].codigo == codigo) return i;
    return -1;
}

void mostrarTemas() {
    for (int i = 0; i < 7; i++)
        printf("%d - %s\n", i + 1, temas[i]);
}

void cabecalho() {
    printf("\nCOD   ESCOLA               DATA       PUBLICO         RESPONSAVEL     TEMA                    PREV EFET SITUACAO\n");
}

void mostrar(struct Acao a) {
    printf("%-5d %-20.20s %-10s %-15.15s %-15.15s %-23.23s %4d %4d %s\n",
           a.codigo, a.escola, a.dataPrevista, a.publicoAlvo, a.responsavel,
           temas[a.tema - 1], a.previstos, a.efetivos, situacoes[a.situacao - 1]);
}

void cadastrar() {
    struct Acao a;

    if (total == MAX) {
        printf("Limite de %d acoes atingido!\n", MAX);
        return;
    }
    a.codigo = lerInt("Codigo: ", 1, 99999);
    if (buscarCodigo(a.codigo) != -1) {
        printf("Ja existe uma acao com esse codigo!\n");
        return;
    }
    lerTexto("Escola: ", a.escola, 50);
    lerTexto("Data prevista (dd/mm/aaaa): ", a.dataPrevista, 11);
    lerTexto("Publico-alvo: ", a.publicoAlvo, 50);
    lerTexto("Responsavel: ", a.responsavel, 50);
    mostrarTemas();
    a.tema = lerInt("Tema: ", 1, 7);
    a.previstos = lerInt("Participantes previstos: ", 1, 100000);
    a.efetivos = 0;
    a.situacao = 1;

    acoes[total++] = a;
    printf("Acao cadastrada com sucesso!\n");
}

void listar() {
    cabecalho();
    for (int i = 0; i < total; i++)
        mostrar(acoes[i]);
    printf("\nTotal: %d acoes\n", total);
}

void pesquisar() {
    char texto[50];
    int n = 0, achou = 0;
    int tipo = lerInt("Pesquisar por: 1-Codigo 2-Escola 3-Tema: ", 1, 3);

    if (tipo == 1) {
        n = lerInt("Codigo: ", 1, 99999);
    } else if (tipo == 2) {
        lerTexto("Escola: ", texto, 50);
    } else {
        mostrarTemas();
        n = lerInt("Tema: ", 1, 7);
    }

    cabecalho();
    for (int i = 0; i < total; i++) {
        if ((tipo == 1 && acoes[i].codigo == n) ||
            (tipo == 2 && strstr(acoes[i].escola, texto) != NULL) ||
            (tipo == 3 && acoes[i].tema == n)) {
            mostrar(acoes[i]);
            achou++;
        }
    }
    if (achou == 0) printf("Nenhuma acao encontrada.\n");
}

void atualizar() {
    int i = buscarCodigo(lerInt("Codigo da acao: ", 1, 99999));

    if (i == -1) {
        printf("Acao nao encontrada!\n");
        return;
    }
    acoes[i].situacao = lerInt("Nova situacao (1-Planejada 2-Realizada 3-Cancelada): ", 1, 3);
    if (acoes[i].situacao == 2)
        acoes[i].efetivos = lerInt("Participantes efetivos: ", 0, 100000);
    else
        acoes[i].efetivos = 0;
    printf("Situacao atualizada!\n");
}

void resumo() {
    int qtd[4] = {0, 0, 0, 0};
    int previstosRealizadas = 0, efetivos = 0;

    for (int i = 0; i < total; i++) {
        qtd[acoes[i].situacao]++;
        if (acoes[i].situacao == 2) {
            previstosRealizadas += acoes[i].previstos;
            efetivos += acoes[i].efetivos;
        }
    }

	
    printf("\n===== RESUMO GERAL =====\n");
    printf("Planejadas: %d\n", qtd[1]);
    printf("Realizadas: %d\n", qtd[2]);
    printf("Canceladas: %d\n", qtd[3]);
    printf("Total de participantes: %d\n", efetivos);
    if (previstosRealizadas > 0)
        printf("Participacao em relacao ao previsto: %.1f%%\n", 100.0 * efetivos / previstosRealizadas);
    else
        printf("Participacao em relacao ao previsto: sem acoes realizadas\n");
}

int main() {
    int opcao;

    do {
        printf("\n===== PSE EM ACAO =====\n");
        printf("1 - Cadastrar acao\n");
        printf("2 - Listar acoes\n");
        printf("3 - Pesquisar\n");
        printf("4 - Atualizar situacao\n");
        printf("5 - Resumo geral\n");
        printf("0 - Sair\n");
        opcao = lerInt("Escolha: ", 0, 5);

        switch (opcao) {
            case 1: 
			cadastrar(); 
			break;

            case 2: 
			listar(); 
			break;

            case 3: 
			pesquisar(); 
			break;

            case 4: 
			atualizar(); 
			break;

            case 5: 
			resumo(); 
			break;
        }
    } while (opcao != 0);

    printf("Encerrando...\n");
    return 0;
}