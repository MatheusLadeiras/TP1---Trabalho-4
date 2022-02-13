#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MAX_PACIENTES = 50;
const int monthDays[12] = { 31, 28, 31,
						30, 31, 30,
						31, 31, 30,
						31, 30, 31 };

struct Pacientes {
    char nome[MAX_PACIENTES];
    char data_nascimento[9];
    int idade;
    long long CPF;
};

struct Consulta {
    char cpf[12];
    char data[9];
    int hora_inicial;  
    int hora_final; 
};

struct Date {
    int d, m, y;
};

void ordenarCPF(int max, Pacientes paciente[]) {
    int i, j;
    char temp[100];
    long long tempInt;
    for(i = 0; i < max; ++i) {
        for(j = i + 1; j < max; j++) { 
            if(paciente[i].CPF > paciente[j].CPF) {
                strcpy(temp, paciente[i].nome);
                strcpy(paciente[i].nome, paciente[j].nome);
                strcpy(paciente[j].nome, temp);
                
                strcpy(temp, paciente[i].data_nascimento);
                strcpy(paciente[i].data_nascimento, paciente[j].data_nascimento);
                strcpy(paciente[j].data_nascimento, temp);
                
                tempInt = paciente[i].idade;
                paciente[i].idade = paciente[j].idade;
                paciente[j].idade = tempInt;
                
                tempInt = paciente[i].CPF;
                paciente[i].CPF = paciente[j].CPF;
                paciente[j].CPF = tempInt;
            }
        }
    }
}

void ordenarNomes(int max, Pacientes paciente[]) {
    int i, j;
    char temp[100];
    long long tempInt;
    for(i = 0; i < max; ++i) {
        for(j = i + 1; j < max; j++) { 
            if(strcmp(paciente[i].nome, paciente[j].nome) > 0) {
                strcpy(temp, paciente[i].nome);
                strcpy(paciente[i].nome, paciente[j].nome);
                strcpy(paciente[j].nome, temp);
                
                strcpy(temp, paciente[i].data_nascimento);
                strcpy(paciente[i].data_nascimento, paciente[j].data_nascimento);
                strcpy(paciente[j].data_nascimento, temp);
                
                tempInt = paciente[i].idade;
                paciente[i].idade = paciente[j].idade;
                paciente[j].idade = tempInt;
                
                tempInt = paciente[i].CPF;
                paciente[i].CPF = paciente[j].CPF;
                paciente[j].CPF = tempInt;
            }
        }
    }
}

void data_hora_atual(int &dia, int &mes, int &ano,
	int &hora, int &min, int &seg) {
	time_t t = time(NULL);
	struct tm lt = *localtime(&t);
	ano = lt.tm_year + 1900;
	mes = lt.tm_mon + 1;
	dia = lt.tm_mday;
	hora = lt.tm_hour;
	min = lt.tm_min;
	seg = lt.tm_sec;
}

int countLeapYears(Date d) {
    int years = d.y;

    if (d.m <= 2)
        years--;

    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(Date dt1, Date dt2) {
	long int n1 = dt1.y * 365 + dt1.d;

    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);

    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}

bool eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int numero_dias_mes(int mes, int ano) {
    if (mes < 1 || mes > 12 || ano <= 0)
        return -1;

    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 ||
        mes == 8 || mes == 10 || mes == 12)
            return 31;
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        return 30;
    else if (eh_bissexto(ano))
        return 29;
    else
        return 28;
}

bool eh_data_valida(int dia, int mes, int ano) {
    int numero_dias = numero_dias_mes(mes, ano);

    return ano > 0 &&
           mes >= 1 && mes <= 12 &&
           dia >= 1 && dia <= numero_dias_mes(mes, ano);
}

void le_string(char label[], char str[], int tam_max) {

    printf(label);
    fgets(str, tam_max+1, stdin);

    if (str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = 0;

    fflush(stdin);
}

void le_string(char label[], char str[], int tam_min, int tam_max, char msg_erro[]) {

    do {
        le_string(label, str, tam_max);

        if (strlen(str) < tam_min)
            puts(msg_erro);
    } while (strlen(str) < tam_min);
}

bool eh_numero(char str[]) {

    for (int i = 0; i < strlen(str); i++)
        if (! isdigit(str[i]))
            return false;

    return true;
}

void converte_data(char str[], int &dia, int &mes, int &ano) {

    int dt = atoi(str); 

    ano = dt % 10000;
    mes = dt / 10000 % 100;
    dia = dt / 10000 / 100;
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

void listagemDosPacientes(int max, Pacientes paciente[]) {
	int dia, mes, ano;
	max--;
			        
	printf("-------------------------------------------------------------------------------\n");	
	printf("CPF         Nome                                                Dt.Nasc.  Idade\n");	
	printf("-------------------------------------------------------------------------------\n");	
	for (int u=0; u <= max; u++) { 
		converte_data(paciente[u].data_nascimento, dia, mes, ano);
		printf("%lld %-50s %02d/%02d/%04d   %i \n", paciente[u].CPF, paciente[u].nome, dia, mes, ano, paciente[u].idade); 
		/* tem que passar o vetor de consulta pra essa função e ajeitar o nome de variáveis.
		for(int i = 0; i < tamAgenda; i++) {
			if (paciente[u].CPF = consulta[i].cpf) {
				converte_data(consulta[i].data, dia, mes, ano);
				printf("-------------------------------------------------------------------------------\n");
				printf("            Agendado para: %02d/%02d/%04d\n", dia, mes, ano);
				printf("            %i:%i às %i:%i \n", horaInicial e horaFinal divididas em horas e minutos);
			}
		}
		*/
	}
	printf("-------------------------------------------------------------------------------\n");
}
int deletarCadastro (Pacientes paciente[], int *numPacientes) {
	long long cpf;
	do {
		printf("CPF: ");
		scanf("%lld", &cpf);
		printf("%lld \n", cpf);
		getchar();
		
		if (!cpf_valido(cpf)) {
        	puts("Erro: Este CPF é inválido");
		}
                 
	} while (cpf_valido(cpf) != true);
	
	for(int i = 0; i < *numPacientes; i++) {
		printf("i = %i\n", i);
		if(cpf == paciente[i].CPF) {
			
			/* Quem fizer exclusão de cadastro tem que completar isso com os requisitos deExclusão de cadastro b)
			for(int j = 0; j < *numPacientes; j++) {
				if (cpf = cliente[j].CFP) {//Se o cliente tiver consulta marcada
					if(!consulta_passada) {//Tem que ver se alguma delas vai acontecer
						puts("Erro: paciente está agendado para 99/99/9999 as 99:99h."); //Se for, não pode deletar nada e acaba a função
						return 0;
					} else {
						deletarConsultas();// Se não tem que deletar todas elas junto com o cadastro
					}
				} 
			*/
		    strcpy(paciente[i].nome, paciente[*numPacientes - 1].nome);
            strcpy(paciente[i].data_nascimento, paciente[*numPacientes - 1].data_nascimento);
            paciente[i].idade = paciente[*numPacientes - 1].idade;
            paciente[i].CPF = paciente[*numPacientes - 1].CPF;
		
			*numPacientes -= 1;
			printf("Paciente excluído com sucesso!\n");
			return 0;
		}	
	}
	puts("Erro: paciente não cadastrado\n");
	return 0;
}
int cadastrarPacientes(Pacientes paciente[], int *numPacientes) {
	long long cpf;
	do {
		printf("CPF: ");
		scanf("%lld", &cpf);
		getchar();
		
		if (!cpf_valido(cpf)) {
        	puts("Erro: Este CPF é inválido");
		}
                 
	} while (cpf_valido(cpf) != true);

	int x = 0;//tire abaixo para poder repitir cpf
	for(x = 0; x < *numPacientes; x++) {
		if(cpf = paciente[x].CPF) {
			printf("Erro: CPF já cadastrado \n\n");
			return 0;
		}
	}
	
	paciente[*numPacientes].CPF = cpf;

	unsigned long int length;
	
	do {
		char buffer[5000];
		printf("Nome: ");
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
    
    char str[9];
    int dia, mes, ano;
    bool futureDate;
    int diaAtual, mesAtual, anoAtual, horaAtual, minAtual, segAtual;
	data_hora_atual(diaAtual, mesAtual, anoAtual, horaAtual, minAtual, segAtual);
    
    do {
    	futureDate = false;
	    le_string("Data de nascimento: ", str, 8, 8, "Data deve ter 8 digitos");

	    if (eh_numero(str)) {
	        
	        converte_data(str, dia, mes, ano);

	        if (eh_data_valida(dia, mes, ano)) { 
    			Date dt1 = { dia, mes, ano };
    			Date dt2 = { diaAtual, mesAtual, anoAtual };
	            int diferenca = getDifference(dt1, dt2);
	            paciente[*numPacientes].idade = diferenca/365;
	            if (diferenca < 0){
	            	futureDate = true;
	            	printf("Erro: data é futura\n");
				}
	        } else {
	            printf("Erro: %d, %d e %d não formam uma data válida\n", dia, mes, ano);
	        }
	    } else {
	        puts("Erro: data não é numérica\n");
		}
		
	strcpy(paciente[*numPacientes].data_nascimento, str);
	
	} while (!eh_data_valida(dia, mes, ano) || futureDate == true);
	
	if(paciente[*numPacientes].idade < 13) {
		printf("Erro: paciente só tem %i anos\n\n", paciente[*numPacientes].idade);
		return 0;
	}
				
	*numPacientes += 1;
	
	printf("\nCadastro realizado com sucesso! \n\n\n");
	return 0;
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
				cadastrarPacientes(paciente, numPacientes);
			break;
			case 2:
				deletarCadastro(paciente, numPacientes);
				printf("A tarefa %i foi executada. \n\n", menu);
			break;
			case 3:
				ordenarCPF(*numPacientes, paciente);
				listagemDosPacientes(*numPacientes, paciente);
			break;
			case 4:
				ordenarNomes(*numPacientes, paciente);
				listagemDosPacientes(*numPacientes, paciente);
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
	printf("numPacientes = %i \n", *numPacientes);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

	int numPacientes = 0;	
	menuPrincipal(&numPacientes);
	
	return 0;
}



		
	
