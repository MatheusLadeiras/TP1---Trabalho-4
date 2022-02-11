#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MAX_PACIENTES = 50;

struct Pacientes {
    char nome[MAX_PACIENTES];
    int data_nascimento[9];
    int idade;
    long long CPF;
};

struct Consulta {
    char cpf[12];
    char data[9];
    int hora_inicial;  
    int hora_final; 
};

void listagemDosPacientes(int max, Pacientes paciente[]) {
	printf("------------------------------------------------------------\n");	
	printf("CPF         Nome                              Dt.Nasc. Idade\n");	
	printf("------------------------------------------------------------\n");	
	for (int u=0; u <= max; u++) { //temporário
		printf("%lld %s   %i %i \n", paciente[u].CPF, paciente[u].nome, paciente[u].data_nascimento, paciente[u].idade); 
	}
	printf("------------------------------------------------------------\n");
}

void listagemIndexada(int max, Pacientes paciente[]) {
    for (int u=0; u <= max; u++) {
    printf( "%i) Paciente: %s, ano de nascimento: %d, CPF: %lld \n", u+1, paciente[u].nome, paciente[u].data_nascimento, paciente[u].CPF); }
    printf("======================================================================================================\n");
} 

void getActualDate(int &dia, int &mes, int &ano, int &hora, int &min) {
    time_t t = time(NULL);
    struct tm lt = *localtime(&t);

    ano = lt.tm_year + 1900;
    mes = lt.tm_mon + 1;
    dia = lt.tm_mday;
    hora = lt.tm_hour;
    min = lt.tm_min;
}

bool cpf_valido(long long cpf) {
    int primeiro_dv, segundo_dv, soma, resto, j, k;
    long long numero_cpf;
    int mult[10] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    if (cpf < 11111111111L || cpf > 99999999999L || cpf % 11111111111L == 0)
        return false;

    primeiro_dv = cpf % 100 / 10,
    segundo_dv  = cpf % 10;

    numero_cpf = cpf / 100; 
    soma = 0;
    for (int i = 0; i < 9; i++)
    {
        soma += (numero_cpf % 10) * mult[i];
        numero_cpf /= 10;
    }

    resto = soma % 11;

    if (resto == 0 || resto == 1)
        j = 0;
    else
        j = 11 - resto;

    if (j != primeiro_dv)
        return false;

    numero_cpf = cpf / 10;  
    soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma += (numero_cpf % 10) * mult[i];
        numero_cpf /= 10;
    }

    resto = soma % 11;

    if (resto == 0 || resto == 1)
        k = 0;
    else
        k = 11 - resto;

    if (k != segundo_dv)
        return false;

    return true;
}

void menuAgenda (Pacientes paciente[]) {
	int menu;
	do{
		printf("Agenda \n");
		printf("1-Agendar consulta \n");
		printf("2-Cancelar agendamento \n");
		printf("3-Listar agenda \n");
		printf("4-Voltar p/ menu principal \n");
		scanf("%i", &menu );
		system("cls");
		switch(menu) {
			case 1:
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 2:
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 3:
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 4:
				printf("Voltando para o menu principal. \n");
			break;
			default:
				printf("O valor recebido é inválido, digite um valor válido. \n");
			break;
		}
	} while(menu!=4);
}

void menuCadastro (Pacientes paciente[], int *numPacientes) {
	int menu;
	do{	
		printf("Menu do Cadastro de Pacientes \n");
		printf("1-Cadastrar novo paciente \n");
		printf("2-Excluir paciente \n");
		printf("3-Listar pacientes (ordenado por CPF) \n");
		printf("4-Listar pacientes (ordenado por nome) \n");
		printf("5-Voltar p/ menu principal \n");
		scanf("%i", &menu );
		getchar();
		system("cls");
		switch(menu) {
			case 1:
				long long cpf;
				int x;
				do {
					printf("CPF: ");
        			scanf("%lld", &cpf);
        			getchar();
        			
        			if (!cpf_valido(cpf)) {
			        	puts("Erro: Este CPF é inválido");
					}
			                 
				} while (cpf_valido(cpf) != true);

				paciente[*numPacientes].CPF = cpf;
				
				unsigned long int length;
				
				do {
					char buffer[5000];
					printf("Nome: ");
			        //fflush(stdin);
			        gets(buffer);
			        
			        for (int i = 0; buffer[i]!='\0'; i++) {
				      if(buffer[i] >= 'a' && buffer[i] <= 'z') {
				         buffer[i] = buffer[i] -32;
				      }
				    }
			        
			        strncpy(paciente[*numPacientes].nome, buffer, 50); 
			        paciente[*numPacientes].nome[50] = 0;
			        length = strlen(paciente[*numPacientes].nome);
			
			        if (length < 4) {
			        	printf("Erro: O nome deve ter ao menos 4 caracteres \n");
					}
			    } while (length < 4);
							
				listagemDosPacientes(*numPacientes, paciente); // esse não precisa passar por referência, esse não é * e sim & j´´a que é chamada de função
				
				*numPacientes += 1;
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 2:
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 3:
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 4:
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 5:
				printf("Voltando para o menu principal. \n");
			break;
			default:
				printf("O valor recebido é inválido, digite um valor válido. \n");
			break;
		}
	} while(menu!=5);
}

void menuPrincipal (int *numPacientes) {
    int menu;
    
    Pacientes paciente[51];
	
	do{
		printf("Menu Principal \n");
		printf("1-Cadastro de pacientes \n");
		printf("2-Agenda \n");
		printf("3-Fim \n");
		scanf("%i", &menu );
		getchar();
		system("cls");
		
		switch(menu) {
			case 1:
				menuCadastro(paciente, numPacientes);
			break;
			case 2:
				menuAgenda(paciente);
			break;
			case 3:
    			printf("Fechando o sistema. \n");
			break;
			default:
				printf("O valor recebido é inválido, digite um valor válido. \n");
			break;
		}
	} while(menu!=3);
	printf("numPacientes = %i \n", numPacientes);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

	int numPacientes = 0;
	menuPrincipal(&numPacientes);
	
	return 0;
}



		
	
