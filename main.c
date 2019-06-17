#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------- Variáveis Comuns -----------------------------

int i, aux, z;
// Chave de Substituição
char Chave[2][64]={{" AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890"},{"r5 6LBdYch3bKSXFOTCjnxARsGV4m1Qtfy0UEWz8q2eauM9Iogk7DPpJvwZHiNl"}};
// Chave Tabela Ascii
char CHAVE[8]="NoTaDeZ";

//----------------- Função para poupar linha no getchar duplicado ------------

void pause(){
    getchar();
    getchar();
}

//----------------------------- Descriptografar ------------------------------

void Descriptografar(int choice,char chave){

    // O inteiro CHOICE recebido irá definir o tipo de descriptografia escolhida pelo usuário
    // 123 : Cifra de Cesar
    // 456 : Tabela Ascii
    // 789 : Substituição

    FILE *cript = fopen("crypto.txt","r");
    FILE *descr = fopen("descrypto.txt","w");

    fflush(stdin);

    int convert;
    int z=0;

    char ler[1000000];

    if (cript==NULL){
        printf("_______________________________________");
        printf("\n\nNao foi possivel ler o texto Criptografado");
        getchar();
        return;
    }
    else{
        if(choice==123){
            while(fgets(ler, 1000, cript) != NULL){
                for(i=0;i<strlen(ler)-1;i++){
                    ler[i]=(int)ler[i]-(chave);
                }
                fprintf(descr, "%s ", ler);
            }
        }
        else if(choice==456){
            while(!feof(cript)){
                for(i=0;i<strlen(CHAVE);i++){
                    if(z>strlen(ler)){
                        // Caso o texto já tenha acabado mas o laço ainda está rodando, isso irá encerrá-lo
                        fprintf(descr, "%s ",ler);
                        z=0;
                        break;
                    }
                    // Dividir o Valor do caratere pelo valor da CHAVE
                    fscanf(cript, "%d", &convert);
                    convert/=(int)CHAVE[i];
                    ler[z]=convert;
                    z++;
                }
            }
        }
        else if(choice==789){
            while(fgets(ler,1000, cript)){
                for(i=0;i<strlen(ler);i++){
                    for(z=0;z<64;z++){
                        // Subtituir os Devidos Caracteres
                        if(ler[i]==Chave[1][z]){
                            ler[i]=Chave[0][z];
                            // z = Tamanho da Chave
                            z=64;
                        }
                    }
                }
                fprintf(descr, "%s", ler);
            }
        }
        printf("_______________________________________");
        printf("\n\nMensagem Descriptografada com Sucesso... Voltando ao Menu...");
        getchar();
    }
    fclose(cript);
    fclose(descr);
}

//------------------------------ Substituição --------------------------------

void substituicao(){

    char ler[1000];

    FILE *texto = fopen("message.txt","r");
    FILE *cript = fopen("crypto.txt","w");

	fflush(stdin);

    system("cls || clear");
    printf("\n\tSubstituicao");
    printf("\n_______________________________________");

	if(texto == NULL){
	    printf("_______________________________________");
        printf("\n\nNao foi possivel ler o arquivo...\n\n");
        pause();
        return;
    }
    else{
        while(fgets(ler,1000, texto)){
            for(i=0;i<strlen(ler);i++){
                for(z=0;z<64;z++){
                    // Subtituir os Devidos Caracteres
                    if(ler[i]==Chave[0][z]){
                        ler[i]=Chave[1][z];
                        // z = Tamanho da Chave
                        z=64;
                    }
                }
            }
            fprintf(cript, "%s", ler);
        }
        printf("\n\nMensagem Encriptada com Sucesso... Partindo para Descriptografia...");
        pause();
    }

	fclose(texto);
	fclose(cript);

    if(texto != NULL){
        Descriptografar(789, 0);
    }
}

//------------------------------ Tabela Ascii --------------------------------

void Ascii(){

    int lern[1000];
    char ler[1000];

    FILE *texto = fopen("message.txt","r");
    FILE *cript = fopen("crypto.txt","w");

	fflush(stdin);

    system("cls || clear");
    printf("\n\tCodigo Ascii");
    printf("\n_______________________________________");

	if(texto == NULL){
        printf("_______________________________________");
        printf("\n\nNao foi possivel ler o arquivo...\n\n");
        pause();
        return;
    }
    else{
        while(fgets(ler, 1000, texto) != NULL){
            for(z=0;z<strlen(ler);){
                for(aux=0;aux<strlen(CHAVE);aux++){
                    if(z>strlen(ler)){
                        break;
                    }
                    // Multiplicar o Valor do caratere pelo valor da CHAVE
                    lern[z] = (int)ler[z]*CHAVE[aux];
                    fprintf(cript, "%d ", lern[z]);
                    z++;
                }
            }
        }
        printf("\n\nMensagem Encriptada com Sucesso... Partindo para Descriptografia...");
        pause();
    }

	fclose(texto);
	fclose(cript);

    if(texto != NULL){
        Descriptografar(456, 0);
    }

}

// ---------------------------- Cifra de Cesar -------------------------------

void Cesar(){

    int chave;

    char ler[1000];

    FILE *texto = fopen("message.txt","r");
    FILE *cript = fopen("crypto.txt","w");

	fflush(stdin);

	system("cls || clear");
	printf("\n\tCifra de Cesar");
	printf("\n_______________________________________");
	printf("\n\nDigite a chave desejada: ");
    scanf("%d", &chave);

	if(texto == NULL){
        printf("_______________________________________");
        printf("\n\nNao foi possivel ler o arquivo...\n\n");
        pause();
        return;
    }
    else{
        while(fgets(ler, 1000, texto) != NULL){
            for(i=0;i<strlen(ler);i++){
                ler[i]=(int)ler[i]+(chave);
            }
            fprintf(cript, "%s ", ler);
        }
        printf("\n_______________________________________");
        printf("\n\nMensagem Encriptada com Sucesso... Partindo para Descriptografia...");
        pause();
    }

	fclose(texto);
	fclose(cript);

    if(texto != NULL){
        Descriptografar(123, chave);
    }
}

// --------------------------- Criptografia Menu -----------------------------

void Criptografar(){

    int h, continu;

    while(1){

        system("clear || cls");
        printf("\nATENCAO! O arquivo apenas sera lido se o tal for nomeado como (message.txt) ");
        printf("\n\nEste deve se situar mesma pasta onde este programa esta salvo...");
        printf("\nCaso ja tenhas escolhido digitar manualmente seu texto, o arquivo sera criptografado normalmente...");
        printf("\nUm novo arquivo com nome de (crypto.txt) sera criado, qualquer outro com mesmo nome sera subtituido...");
        printf("\n_______________________________________");
        printf("\n\n1- Continuar");
        printf("\n\n2- Sair");
        printf("\n_______________________________________");
        printf("\n\nDigite a Opcao Desejada: ");

        fflush(stdin);

        scanf("%d", &h);

        if(h==1){
            while(1){

                fflush(stdin);

                system("clear || cls");
                printf("\n\tChaves");
                printf("\n_______________________________________");
                printf("\n\n1- Cifra de Cesar");
                printf("\n\n2- Codigo Ascii");
                printf("\n\n3- Substituicao");
                printf("\n_______________________________________");
                printf("\n\nDigite a Opcao Desejada: ");
                scanf("%d", &continu);
                if(continu==1){
                    Cesar();
                    return;
                }
                else if(continu==2){
                    Ascii();
                    return;
                }
                else if(continu==3){
                    substituicao();
                    return;
                }
                else{
                    printf("_______________________________________");
                    printf("\n\nOpcao Invalida");
                    pause();
                }
            }
            break;
        }
        else if(h==2){
            return;
        }
        else{
            printf("_______________________________________");
            printf("\n\nOpcao Invalida...");
            pause();
        }
    }
}

// -----------------------Digitar a Propria mensagem -------------------------

void MenuDigitar(int opc){

    int x;
	int continu;

	while(1){

        fflush(stdin);

		system("clear || cls");
		printf("\nATENCAO! O arquivo a seguir sera nomeado como (message.txt) ");
		printf("\n\nO tal sera salvo na mesma pasta onde este programa esta salvo...");
		printf("\nQualquer arquivo com o mesmo nome sera automaticamente substituido...");
		printf("\nPara a opcao de apenas 'acrescentar' um texto, a frase sera escrita\na partir do final do arquivo...");
		printf("\n_______________________________________");
		printf("\n\n1- Continuar");
		printf("\n\n2- Sair");
		printf("\n_______________________________________");
		printf("\n\nDigite a Opcao Desejada: ");
		scanf("%d", &continu);

		if(continu==1){

            FILE *texto;

            if(opc==123){
                texto = fopen("message.txt","w");
            }
			else if(opc==456){
                texto = fopen("message.txt","a");
			}

			char frase[1000000];

			if(texto==NULL){
                printf("_______________________________________");
				printf("\n\nNão foi possivel abrir o arquivo...");
				return;
			}
            else{
                system("cls || clear");
                printf("\n\tRecebibento de texto");
                printf("\n_______________________________________");
                printf("\n\nDigite o texto desejado: ");

                fflush(stdin);
                scanf(" %[^\n]", frase);

                if(opc==123){
                    fprintf(texto, "%s", frase);
                }
                else if(opc==456){
                    fprintf(texto, " ");
                    fputs(frase, texto);
                }

                if(strlen(frase)>1000000){
                    printf("_______________________________________");
                    printf("\n\nA frase digitade ultrapassa os limites permitidos... O programa sera abortado...");
                    pause();
                    fclose(texto);
                    exit(0);
                }

                while(1){

                    fflush(stdin);

                    printf("\n_______________________________________");
                    printf("\n\n1- Encriptografar");
                    printf("\n\n2- Digitar Outra Frase");
                    printf("\n\n3- Acrescentar Outra Frase");
                    printf("\n\n4- Menu");
                    printf("\n_______________________________________");
                    printf("\n\nDigite a Opcao Desejada: ");
                    scanf("%d", &x);

                    if(x==1){
                        fclose(texto);
                        Criptografar();
                        break;
                    }
                    else if(x==2){
                        fclose(texto);
                        system("cls || clear");
                        MenuDigitar(123);
                    	break;
                    }
                    else if(x==3){
                        fclose(texto);
                        system("cls || clear");
                        MenuDigitar(456);
                    	break;
                    }
                	else if(x==4){
                        fclose(texto);
                        break;
                    }
                	else{
                        printf("_______________________________________");
						printf("\n\nDigite um Opcao Valida...");
                        pause();
                        system("cls || clear");
                        printf("\n\n\tRecebibento de texto");
                        printf("\n_______________________________________");
                        printf("\n\n '%s'", frase);
                        continue;
                    }
                    break;
                }
                break;
            }
		}
		else if(continu==2){
			return;
		}
		else{
            printf("_______________________________________");
			printf("\n\nOpcao Invalida...");
			pause();
		}
	}
}
// ---------------------------- Menu Opção NULA ------------------------------

void OpcaoNula(){

    int y, nova;

    while(1){
        system("cls || clear");
        printf("\nATENCAO! O arquivo apenas sera lido se for nomeado como (crypto.txt) ");
        printf("\n\nO tal deve se situar mesma pasta onde este programa esta salvo...");
        printf("\nE necessario que o usuario tenha consciencia da chave e codigo utilizado...");
        printf("\nUm novo arquivo com nome de (descrypto.txt) sera criado, qualquer outro com mesmo nome sera subtituido...");
        printf("\n_______________________________________");
        printf("\n\n1- Continuar");
        printf("\n\n2- Sair");
        printf("\n_______________________________________");
        printf("\n\nDigite a opcao desejada: ");
        scanf("%d", &y);
            if(y==1){
                break;
            }
            else if(y==2){
                return;
            }
            else{
                printf("_______________________________________");
                printf("\n\nDigite uma opcao valida...");
                pause();
                continue;
            }
        }
    while(1){
        system("cls || clear");
        printf("\n\tDescriptografador");
        printf("\n_______________________________________");
        printf("\n\n1- Cifra de Cesar");
        printf("\n\n2- Codigo Ascii");
        printf("\n\n3- Substituicao");
        printf("\n_______________________________________");
        printf("\n\nDigite o codigo conhecido: ");
        scanf("%d", &y);
        if(y==1){
            printf("_______________________________________");
            printf("\n\nDigite a Chave conhecida: ");
            scanf("%d", &nova);
            Descriptografar(123, nova);
        }
        else if(y==2){
            Descriptografar(456, 0);
        }
        else if(y==3){
            Descriptografar(789, 0);
        }
        else{
            printf("_______________________________________");
            printf("\n\nDigite uma opcao valida...");
            pause();
            continue;
        }
        getchar();
        return;
    }
}

// --------------------------------- MENU ------------------------------------

void menu(){

    char x;

	while(1){

        fflush(stdin);

		system("clear || cls");
		printf("\n_______________________________________\n");
		printf("\n\tEncriptografador");
		printf("\n_______________________________________");
		printf("\n\n1- Digitar um mensagem");
		printf("\n\n2- Acrescentar mensagem");
		printf("\n\n3- Encriptografia");
		printf("\n\n4- Descriptografar");
		printf("\n\n5- Sair");
		printf("\n_______________________________________");
		printf("\n\nDigite a opcao desejada: ");
		scanf("%s", &x);

		switch(x){
			case '1':
				MenuDigitar(123);
				break;
			case '2':
				MenuDigitar(456);
				break;
			case '3':
				Criptografar();
				break;
            case '4':
                OpcaoNula();
                break;
			case '5':
                printf("_______________________________________");
				printf("\n\nFinalizando Programa...");
				pause();
				exit (0);
			default:
                printf("_______________________________________");
				printf("\n\nDigite um Opcao valida!\n");
                pause();
		}
	}
}

// --------------------------------- Main ------------------------------------

int main(int argc, char *argv[]){

	menu();

	return 0;
}
