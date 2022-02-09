#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Pacientes {
    char nome[51];
    int data_nascimento[9];
    long long CPF[12];
};

struct Consulta {
    char cpf[12];
    char data[9];
    int hora_inicial;  
    int hora_final; 
};

void listagemIndexada(int max, Pacientes paciente[]) {
    for (int u=0; u <= max; u++) {
    printf( "%i) Paciente: %s, ano de nascimento: %d, CPF: %.2f\n", u+1, paciente[u].nome, paciente[u].data_nascimento, paciente[u].CPF); }
    printf("======================================================================================================\n");
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

void menuCadastro (Pacientes paciente[]) {
	int menu;
	// int numPacientes = 0; //sempre que o menu for reaberto ele vai setar como zero novamente, fazer com que se descubra esse valor na hora
	do{
		int numPacientes = 0;
		int j = 0;
		while (paciente[j].nome[0]!='\0') {
	        numPacientes += 1;
	        j++;
    	} 

    	printf("numPacientes: %i \n", numPacientes); 
    	
		printf("Menu do Cadastro de Pacientes \n");
		printf("1-Cadastrar novo paciente \n");
		printf("2-Excluir paciente \n");
		printf("3-Listar pacientes (ordenado por CPF) \n");
		printf("4-Listar pacientes (ordenado por nome) \n");
		printf("5-Voltar p/ menu principal \n");
		scanf("%i", &menu );
		system("cls");
		switch(menu) {
			case 1:
				unsigned long int length;
				
				do {
					char buffer[5000];
					printf("Qual o nome do Paciente? ");
			        
			        fflush(stdin);
			        gets(buffer);
			        
			        for (int i = 0; buffer[i]!='\0'; i++) {
				      if(buffer[i] >= 'a' && buffer[i] <= 'z') {
				         buffer[i] = buffer[i] -32;
				      }
				    }
			        
			        strncpy(paciente[numPacientes].nome, buffer, 30); 
			    	
			        paciente[numPacientes].nome[30] = 0;
			        
			        length = strlen(paciente[numPacientes].nome);
			
			        if (length < 4) {
			        	printf("O valor recebido é inválido, digite um valor válido. \n");
					}
			    } while (length < 4);
							
				listagemIndexada(numPacientes, paciente);
				
				//numPacientes +=1;
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

void menuPrincipal () {
    int menu;
    
    Pacientes paciente[51];
    	
	do{
		printf("Menu Principal \n");
		printf("1-Cadastro de pacientes \n");
		printf("2-Agenda \n");
		printf("3-Fim \n");
		scanf("%i", &menu );
		system("cls");
		
		switch(menu) {
			case 1:
				menuCadastro(paciente);
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
}

int main() {
    setlocale(LC_ALL, "Portuguese");

	menuPrincipal();
	
	return 0;
}



		
	
