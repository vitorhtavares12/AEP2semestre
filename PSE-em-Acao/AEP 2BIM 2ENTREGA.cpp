#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

struct cadastro {
	int codigo;
	char escola[100];
	char dataprevista[20];
	char publicoalvo[100];
	char responsavel[50];
	int quantidadeprevista;
	int quantidadeefetiva;
	int tema;
	int situacao;
};

struct cadastro cadastros[TAM];

void cadastrar();
void atualizar();
void pesquisas();
void pesquisacodigo();
void pesquisaescola();
void pesquisatema();
void listagens();
void listartodasacoes();
void listarresumogeral();
void exibircadastro(int codigo);
void descricaosituacao(int situacao, char descsituacao[30]);
void descricaotema(int tema, char desctema[30]);
void limpatela();
void salvardados();
void lerdados();

int main(){
	lerdados();
	
	int opcao;
	
	do{
		limpatela();
		
		printf("\n+------ PSE EM ACAO ------+\n");
		printf("|                         |\n");
		printf("| 1 - Cadastrar acao      |\n");
		printf("| 2 - Atualizar situacao  |\n");
		printf("| 3 - Pesquisas           |\n");
		printf("| 4 - Listagens           |\n");
		printf("| 0 - Sair                |\n");
		printf("|                         |\n");
		printf("+-------------------------+\n\n");
		
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			
			case 1:
				cadastrar();
				break;
				
			case 2:
				atualizar();
				break;
				
			case 3:
				pesquisas();
				break;
					
			case 4:
				listagens();
				break;
				
			case 0:
				limpatela();
				printf("Encerrando o sistema...\n");
				break;
							
			default:
				printf("\n*** Opcao invalida! ***\n\n");
  				system("pause");

		}
	} while(opcao != 0);
	
	salvardados();
	return 0;
}

void cadastrar(){
	cadastro cadastroatual;
	char opcao;

	limpatela();

	printf("===== CADASTRO =====\n\n");
	
	printf("Informe o codigo da acao...........: ");
	scanf("%d", &cadastroatual.codigo);
	getchar(); // Consome o Enter pendente
	
	if (cadastros[cadastroatual.codigo - 1].codigo == 0) {
		printf("Informe o nome da escola...........: ");
		fgets(cadastroatual.escola, sizeof(cadastroatual.escola), stdin);
		cadastroatual.escola[strcspn(cadastroatual.escola, "\r\n")] = '\0'; // remove o \r\n deixado na string pelo fgets
		printf("Informe a data prevista............: ");
		fgets(cadastroatual.dataprevista, sizeof(cadastroatual.dataprevista), stdin);
		cadastroatual.dataprevista[strcspn(cadastroatual.dataprevista, "\r\n")] = '\0'; // remove o \r\n deixado na string pelo fgets
		printf("Informe o publico alvo.............: ");
		fgets(cadastroatual.publicoalvo, sizeof(cadastroatual.publicoalvo), stdin);
		cadastroatual.publicoalvo[strcspn(cadastroatual.publicoalvo, "\r\n")] = '\0'; // remove o \r\n deixado na string pelo fgets
		printf("Informe o responsavel..............: ");
		fgets(cadastroatual.responsavel, sizeof(cadastroatual.responsavel), stdin);
		cadastroatual.responsavel[strcspn(cadastroatual.responsavel, "\r\n")] = '\0'; // remove o \r\n deixado na string pelo fgets
		do {
			printf("Informe a quantidade prevista (> 0): ");
			scanf("%d", &cadastroatual.quantidadeprevista);
		} while (cadastroatual.quantidadeprevista < 1);
		cadastroatual.quantidadeefetiva = 0;
		printf("Quantidade Efetiva.................: %d\n", cadastroatual.quantidadeefetiva);
		cadastroatual.situacao = 1;
		printf("Situacao inicial...................: %d - Planejada\n", cadastroatual.situacao);
		getchar(); // Consome o Enter pendente

		printf("\n+-------- TEMA DA ACAO---------+\n");
		printf("|                              |\n");
		printf("| 1 - Alimentacao Saudavel     |\n");
		printf("| 2 - Atividade Fisica         |\n");
		printf("| 3 - Saude Mental             |\n");
		printf("| 4 - Cultura de Paz           |\n");
		printf("| 5 - Vacinacao                |\n");
		printf("| 6 - Saude Bucal              |\n");
		printf("| 7 - Prevencao das Violencias |\n");
		printf("|                              |\n");
		printf("+------------------------------+\n\n");
		
		do {
			printf("Escolha o tema desta acao: ");
			scanf("%d", &cadastroatual.tema);
			getchar(); // Consome o Enter pendente
		} while ((cadastroatual.tema < 1) || (cadastroatual.tema > 7));
		
		do {
			printf("\nConfirma o cadastro desta acao? [S/N]: ");
			scanf("%c", &opcao);
		} while ((opcao != 'S') && (opcao != 's') && (opcao != 'N') && (opcao != 'n'));
		
		if ((opcao == 'S') || (opcao == 's')) {
			cadastros[cadastroatual.codigo - 1] = cadastroatual;
		} 
	} else {
		printf("\n*** Este cadastro ja existe no banco de dados. ***\n\n");
		system("pause");
	}
}

void atualizar(){
	int codigo, situacao, quantidade;
	char opcao;

	limpatela();

	printf("===== ATUALIZAR SITUACAO =====\n\n");
	
	printf("Informe o codigo da acao..: ");
	scanf("%d", &codigo);
	
	if (cadastros[codigo - 1].codigo != 0) {
		printf("\n+---- SITUACAO ----+\n");
		printf("|                  |\n");
		printf("| 1 - Planejada    |\n");
		printf("| 2 - Realizada    |\n");
		printf("| 3 - Cancelada    |\n");
		printf("|                  |\n");
		printf("+------------------+\n\n");
		
		do {
			printf("Escolha a nova situacao desta acao: ");
			scanf("%d", &situacao);
			getchar(); // Consome o Enter pendente
		} while ((situacao < 1) || (situacao > 3));
		
		if (situacao == 2) {
			do {
				printf("Informe a quantidade efetiva (> 0): ");
				scanf("%d", &quantidade);
				getchar(); // Consome o Enter pendente
			} while (quantidade < 1);
		}
		
		do {
			printf("\nConfirma a atualizacao desta acao? [S/N]: ");
			scanf("%c", &opcao);
		} while ((opcao != 'S') && (opcao != 's') && (opcao != 'N') && (opcao != 'n'));
		
		if ((opcao == 'S') || (opcao == 's')) {
			cadastros[codigo - 1].situacao = situacao;
			if (situacao == 2) {
				cadastros[codigo - 1].quantidadeefetiva = quantidade;
			}
		} 
	} else {
		printf("\n*** Este cadastro nao existe no banco de dados. ***\n\n");
		system("pause");
	}
}

void pesquisas(){
	int opcao;
	
	do{
		limpatela();
		
		printf("\n+--- PESQUISAS ---+\n");
		printf("|                 |\n");
		printf("| 1 - Por codigo  |\n");
		printf("| 2 - Por escola  |\n");
		printf("| 3 - Por tema    |\n");
		printf("| 0 - Voltar      |\n");
		printf("|                 |\n");
		printf("+-----------------+\n\n");
		
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		getchar(); // Consome o Enter pendente
		
		switch(opcao){
			
			case 1:
				pesquisacodigo();
				break;
				
			case 2:
				pesquisaescola();
				break;
				
			case 3:
				pesquisatema();
				break;
					
			case 0:
				break;
							
			default:
				printf("\n*** Opcao invalida! ***\n\n");
  				system("pause");

		}
	} while(opcao != 0);
}

void pesquisacodigo(){
	int codigo;

	do {
		limpatela();
	
		printf("===== PESQUISA POR CODIGO =====\n\n");
		
		printf("Informe o codigo da acao (0 para voltar)..: ");
		scanf("%d", &codigo);
		
		if (codigo > 0) {
			if (cadastros[codigo - 1].codigo != 0) {
				limpatela();
				printf("===== PESQUISA POR CODIGO =====\n\n");
				exibircadastro(codigo);
			} else {
				printf("\n*** Este cadastro nao existe no banco de dados. ***\n\n");
				system("pause");
			}
		}
	} while (codigo != 0);
};

void pesquisaescola(){
	int codigo;
	char descsituacao[30];
	char desctema[30];
	char escola[100];

	do {
		limpatela();
	
		printf("===== PESQUISA POR ESCOLA =====\n\n");
		
		printf("Informe a escola (0 para voltar)..: ");
		fgets(escola, sizeof(escola), stdin);
		escola[strcspn(escola, "\r\n")] = '\0'; // remove o \r\n deixado na string pelo fgets

		if (escola[0] != '0'){
			printf("\nCODIGO ESCOLA                    TEMA                     DATA PREVISTA  SITUACAO\n");
			printf("-----------------------------------------------------------------------------------\n");
			for (int i=0; i < TAM; i++){
				if (strcmp(cadastros[i].escola, escola) == 0){
					descricaosituacao(cadastros[i].situacao, descsituacao);
					descricaotema(cadastros[i].tema, desctema);
					printf("%6d %-25.25s %-24.24s   %-10.10s   %-10.10s\n", cadastros[i].codigo, cadastros[i].escola, desctema, cadastros[i].dataprevista, descsituacao);
				}
			}
			printf("-----------------------------------------------------------------------------------\n\n");

			printf("Informe um codigo para visualizar os detalhes (0 para voltar)..: ");
			scanf("%d", &codigo);
			getchar(); // Consome o Enter pendente
			
			if (codigo > 0) {
				if (cadastros[codigo - 1].codigo != 0) {
					limpatela();
					printf("===== PESQUISA POR ESCOLA =====\n\n");
					exibircadastro(codigo);
				}
			}
		}
	} while (escola[0] != '0');
};

void pesquisatema(){
	int tema, codigo;
	char descsituacao[30];
	char desctema[30];
	
	do {
		limpatela();
	
		printf("===== PESQUISA POR TEMA =====\n\n");
		
				printf("\n+-------- TEMA DA ACAO---------+\n");
		printf("|                              |\n");
		printf("| 1 - Alimentacao Saudavel     |\n");
		printf("| 2 - Atividade Fisica         |\n");
		printf("| 3 - Saude Mental             |\n");
		printf("| 4 - Cultura de Paz           |\n");
		printf("| 5 - Vacinacao                |\n");
		printf("| 6 - Saude Bucal              |\n");
		printf("| 7 - Prevencao das Violencias |\n");
		printf("|                              |\n");
		printf("+------------------------------+\n\n");
		
		do {
			printf("Escolha o tema (0 para voltar): ");
			scanf("%d", &tema);
			getchar(); // Consome o Enter pendente
		} while ((tema < 0) || (tema > 7));

		if (tema != 0){
			printf("\nCODIGO ESCOLA                    TEMA                     DATA PREVISTA  SITUACAO\n");
			printf("-----------------------------------------------------------------------------------\n");
			for (int i=0; i < TAM; i++){
				if (cadastros[i].tema == tema){
					descricaosituacao(cadastros[i].situacao, descsituacao);
					descricaotema(cadastros[i].tema, desctema);
					printf("%6d %-25.25s %-24.24s   %-10.10s   %-10.10s\n", cadastros[i].codigo, cadastros[i].escola, desctema, cadastros[i].dataprevista, descsituacao);
				}
			}
			printf("-----------------------------------------------------------------------------------\n\n");

			printf("Informe um codigo para visualizar os detalhes (0 para voltar)..: ");
			scanf("%d", &codigo);
			getchar(); // Consome o Enter pendente
			
			if (codigo > 0) {
				if (cadastros[codigo - 1].codigo != 0) {
					limpatela();
					printf("===== PESQUISA POR TEMA =====\n\n");
					exibircadastro(codigo);
				}
			}
		}
	} while (tema != 0);
};

void listagens(){
	int opcao;
	
	do{
		limpatela();
		
		printf("\n+----- LISTAGENS -----+\n");
		printf("|                     |\n");
		printf("| 1 - Todas as acoes  |\n");
		printf("| 2 - Resumo Geral    |\n");
		printf("| 0 - Voltar          |\n");
		printf("|                     |\n");
		printf("+---------------------+\n\n");
		
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		getchar(); // Consome o Enter pendente
		
		switch(opcao){
			
			case 1:
				listartodasacoes();
				break;
				
			case 2:
				listarresumogeral();
				break;
				
			case 0:
				break;
							
			default:
				printf("\n*** Opcao invalida! ***\n\n");
  				system("pause");

		}
	} while(opcao != 0);
}

void listartodasacoes(){
	char descsituacao[30];
	char desctema[30];
	int totalacoes = 0;
	
	limpatela();

	printf("+--------------------------------------------------------------------------------------------------------------------+\n");
	printf("|                                                P S E    E M    A C A O                                             |\n");
	printf("|                                                LISTAGEM GERAL DE ACOES                                             |\n");
	printf("+--------------------------------------------------------------------------------------------------------------------+\n\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("COD ESCOLA              DATA PREV. PUBLICO ALVO       RESPONSAVEL        PREV EFET SITUACAO   TEMA\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");

	for (int i=0; i < TAM; i++){
		if (cadastros[i].codigo != 0){
			descricaosituacao(cadastros[i].situacao, descsituacao);
			descricaotema(cadastros[i].tema, desctema);
			printf("%3d %-19.19s %-10.10s %-18.18s %-18.18s %4d %4d %-10.10s %-24.24s\n", cadastros[i].codigo, cadastros[i].escola, cadastros[i].dataprevista, cadastros[i].publicoalvo, cadastros[i].responsavel, cadastros[i].quantidadeprevista, cadastros[i].quantidadeefetiva, descsituacao, desctema);
			totalacoes++;
		}
	}
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("                                             TOTAL DE %d ACOES CADASTRADAS\n\n", totalacoes);
	
	system("pause");
}

void listarresumogeral(){
	char descsituacao[30];
	char desctema[30];
	int planejadas = 0;
	int realizadas = 0;
	int canceladas = 0;
	int totais = 0;
	int previstosplan = 0;
	int previstosreal = 0;
	int efetivosreal = 0;
	float percentualreal = 0;
	int previstoscanc = 0;
	int previstostot = 0;
	int efetivostot = 0;
	float percentualtot = 0;
	
	limpatela();

	for (int i=0; i < TAM; i++){
		if (cadastros[i].codigo != 0) {
			switch(cadastros[i].situacao){
				case 1:
					planejadas++;
					previstosplan = previstosplan + cadastros[i].quantidadeprevista;
					break;
					
				case 2:
					realizadas++;
					previstosreal = previstosreal + cadastros[i].quantidadeprevista;
					efetivosreal = efetivosreal + cadastros[i].quantidadeefetiva;
					break;
					
				case 3:
					canceladas++;
					previstoscanc = previstoscanc + cadastros[i].quantidadeprevista;
					break;
			}
		}
	}
	percentualreal = (efetivosreal * 100) / previstosreal;
	totais = planejadas + realizadas + canceladas;
	previstostot = previstosplan + previstosreal + previstoscanc;
	efetivostot = efetivosreal;
	percentualtot = (efetivostot * 100) / previstostot;

	printf("+--------------------------------------------------------------------------------------------------------------------+\n");
	printf("|                                                P S E    E M    A C A O                                             |\n");
	printf("|                                                     RESUMO GERAL                                                   |\n");
	printf("+--------------------------------------------------------------------------------------------------------------------+\n\n");
	printf("                                        PLANEJADOS:\n");
	printf("                                            TOTAL DE ACOES.........: %d\n", planejadas);
	printf("                                            PARTICIPANTES PREVISTOS: %d\n\n", previstosplan);
	printf("                                        REALIZADOS:\n");
	printf("                                            TOTAL DE ACOES.........: %d\n", realizadas);
	printf("                                            PARTICIPANTES PREVISTOS: %d\n", previstosreal);
	printf("                                            PARTICIPANTES EFETIVOS.: %d\n", efetivosreal);
	printf("                                            PERCENTUAL PARTICIPACAO: %.2f%%\n\n", percentualreal);
	printf("                                        CANCELADOS:\n");
	printf("                                            TOTAL DE ACOES.........: %d\n", canceladas);
	printf("                                            PARTICIPANTES PREVISTOS: %d\n\n", previstoscanc);
	printf("                                        GERAL:\n");
	printf("                                            TOTAL DE ACOES.........: %d\n", totais);
	printf("                                            PARTICIPANTES PREVISTOS: %d\n", previstostot);
	printf("                                            PARTICIPANTES EFETIVOS.: %d\n", efetivostot);
	printf("                                            PERCENTUAL PARTICIPACAO: %.2f%%\n\n", percentualtot);
	system("pause");
}

void exibircadastro(int codigo){
	char descsituacao[30];
	char desctema[30];

	printf("===== DADOS DA ACAO =====\n\n");
	
	printf("Codigo da acao............................: %d\n", cadastros[codigo - 1].codigo);
	printf("Nome da escola............................: %s\n", cadastros[codigo - 1].escola);
	printf("Data prevista.............................: %s\n", cadastros[codigo - 1].dataprevista);
	printf("Publico alvo..............................: %s\n", cadastros[codigo - 1].publicoalvo);
	printf("Responsavel...............................: %s\n", cadastros[codigo - 1].responsavel);
	printf("Quantidade prevista.......................: %d\n", cadastros[codigo - 1].quantidadeprevista);
	printf("Quantidade efetiva........................: %d\n", cadastros[codigo - 1].quantidadeefetiva);
	descricaosituacao(cadastros[codigo - 1].situacao, descsituacao);
	printf("Situacao..................................: %d - %s\n", cadastros[codigo - 1].situacao, descsituacao);
	descricaotema(cadastros[codigo - 1].tema, desctema);
	printf("Tema......................................: %d - %s\n\n", cadastros[codigo - 1].tema, desctema);
	system("pause");
}

void descricaosituacao(int situacao, char descsituacao[30]) {
	switch(situacao){
		case 1:
			strcpy(descsituacao, "Planejada");
			break;

		case 2:
			strcpy(descsituacao, "Realizada");
			break;

		case 3:
			strcpy(descsituacao, "Cancelada");
			break;
			
		default:
			strcpy(descsituacao, "Invalida");
			break;
	}
}

void descricaotema(int tema, char desctema[30]) {
	switch(tema){
		case 1:
			strcpy(desctema, "Alimentacao Saudavel");
			break;
			
		case 2:
			strcpy(desctema, "Atividade Fisica");
			break;

		case 3:
			strcpy(desctema, "Saude Mental");
			break;

		case 4:
			strcpy(desctema, "Cultura de Paz");
			break;
			
		case 5:
			strcpy(desctema, "Vacinacao");
			break;
			
		case 6:
			strcpy(desctema, "Saude Bucal");
			break;
			
		case 7:
			strcpy(desctema, "Prevencao das Violencias");
			break;
			
		default:
			strcpy(desctema, "Invalido");
			break;
	}
}

void limpatela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void salvardados() {
    FILE *arquivo = fopen("pse.txt", "w");

    if (arquivo == NULL) {
        printf("**** Erro ao salvar o arquivo PSE.TXT! ****\n\n");
        system("pause");
    }

    for (int i = 0; i < TAM; i++) {
        fprintf(arquivo, 
			"%d,%s,%s,%s,%s,%d,%d,%d,%d\n", 
			cadastros[i].codigo, 
			cadastros[i].escola, 
			cadastros[i].dataprevista,
			cadastros[i].publicoalvo,
			cadastros[i].responsavel,
			cadastros[i].quantidadeprevista,
			cadastros[i].quantidadeefetiva,
			cadastros[i].tema,
			cadastros[i].situacao
		);
    }

    fclose(arquivo);
}

void lerdados() {
	int i = 0;
	
    FILE *arquivo = fopen("pse.txt", "r");

    if (arquivo == NULL) {
        printf("**** Erro ao ler o arquivo PSE.TXT! ****\n\n");
        printf("Caso seja o primeiro acesso o arquivo PSE.TXT sera criado automaticamente.\n\n");
        system("pause");
    }

    while (i < TAM && fscanf(arquivo, 
							 	"%d,%100[^,],%20[^,],%100[^,],%50[^,],%d,%d,%d,%d", 
								&cadastros[i].codigo, 
								cadastros[i].escola, 
								cadastros[i].dataprevista,
								cadastros[i].publicoalvo,
								cadastros[i].responsavel,
								&cadastros[i].quantidadeprevista,
								&cadastros[i].quantidadeefetiva,
								&cadastros[i].tema,
								&cadastros[i].situacao
							) == 9
		  ) 
	{
        i++;
    }

    fclose(arquivo);
}


