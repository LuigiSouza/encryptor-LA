#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------- Variáveis Comuns -----------------------------

int i, aux, z;
char Chave[2][64]={{" AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890"},{"r5 6LBdYch3bKSXFOTCjnxARsGV4m1Qtfy0UEWz8q2eauM9Iogk7DPpJvwZHiNl"}};
char CHAVE[8]="NoTaDeZ";

//----------------- Função para poupar linha no getchar duplicado ------------

void pause(){
    getchar();
    getchar();
}

//----------------------------- Descriptografar ------------------------------

void Descriptografar(char choice[100],char chave){

    FILE *cript = fopen("crypto.txt","r");
    FILE *descr = fopen("descrypto.txt","w");

    fflush(stdin);

    int convert;
    int z=0;

    char ler[1000000];

    if (cript==NULL){
        printf("\n\nNao foi possivel ler o texto Criptografado");
        getchar();
        return;
    }
    else{
        if(choice=="cesar"){
            while(fgets(ler, 1000, cript) != NULL){
                for(i=0;i<strlen(ler)-1;i++){
                    ler[i]=(int)ler[i]-(chave);
                }
                fprintf(descr, "%s ", ler);
            }
        }
        else if(choice=="ascii"){
            while(!feof(cript)){
                for(i=0;i<strlen(CHAVE);i++){
                    if(z>strlen(ler)){
                        fprintf(descr, "%s ",ler);
                        z=0;
                        break;
                    }
                    fscanf(cript, "%d", &convert);
                    convert/=(int)CHAVE[i];
                    ler[z]=convert;
                    z++;
                }
            }
        }
        else if(choice=="subs"){
            while(fgets(ler,1000, cript)){
                for(i=0;i<strlen(ler);i++){
                    for(z=0;z<63;z++){
                        if(ler[i]==Chave[1][z]){
                            ler[i]=Chave[0][z];
                            z=63;
                        }
                    }
                }
                fprintf(descr, "%s", ler);
            }
        }
        printf("\n\nMensagem Descriptografada com Sucesso... Voltando ao Menu...");
        getchar();
    }
    fclose(cript);
    fclose(descr);
}

//------------------------------ Substituição --------------------------------

void substituicao(){

    char ler[1000];

    char cripto;

    FILE *texto = fopen("message.txt","r");
    FILE *cript = fopen("crypto.txt","w");

	fflush(stdin);

    system("cls || clear");
    printf("\n\tSubstituicao");
    printf("\n_______________________________________");

	if(texto == NULL){
        printf("\n\nNao foi possivel ler o arquivo...\n\n");
        pause();
        return;
    }
    else{
        while(fgets(ler,1000, texto)){
            for(i=0;i<strlen(ler);i++){
                for(z=0;z<63;z++){
                    if(ler[i]==Chave[0][z]){
                        ler[i]=Chave[1][z];
                        z=63;
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
        Descriptografar("subs", 0);
    }
}

//---------------------------- Tabela Ascii ----------------------------------

void Ascii(){

	int lern[1000];
    char ler[1000];

    char cripto;

    FILE *texto = fopen("message.txt","r");
    FILE *cript = fopen("crypto.txt","w");

	fflush(stdin);

    system("cls || clear");
    printf("\n\tCodigo Ascii");
    printf("\n_______________________________________");

	if(texto == NULL){
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
        Descriptografar("ascii", 0);
    }

}

// ------------------------------------- Cifra de Cesar ----------------------

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
        printf("\n\nMensagem Encriptada com Sucesso... Partindo para Descriptografia...");
        pause();
    }

	fclose(texto);
	fclose(cript);

    if(texto != NULL){
        Descriptografar("cesar", chave);
    }
}

// -------------------------------------- Criptografia Menu ------------------

void Criptografar(){

    int h, continu;

    while(1){

        system("clear || cls");
        printf("\nATENCAO! O arquivo apenas sera lido se outro for nomeado como (message.txt) ");
        printf("\n\nO tal deve se situar mesma pasta onde este programa esta salvo...");
        printf("\nCaso ja tenhas escolhido digitar seu texto, o arquivo sera criptografado normalmente...");
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
                    printf("\nOpcao Invalida");
                    pause();
                }
            }
            break;
        }
        else if(h==2){
            return;
        }
        else{
            printf("\n\nOpcao Invalida...");
            pause();
        }
    }
}

// ----------------------------Digitar a Propria mensagem --------------------

void MenuDigitar(){

    int x;
	int continu;

	while(1){

        fflush(stdin);

		system("clear || cls");
		printf("\nATENCAO! O arquivo a seguir sera nomeado como (message.txt) ");
		printf("\n\nO tal sera salvo na mesma pasta onde este programa esta salvo...");
		printf("\nQualquer arquivo com o mesmo nome sera automaticamente substituido...");
		printf("\n_______________________________________");
		printf("\n\n1- Continuar");
		printf("\n\n2- Sair");
		printf("\n_______________________________________");
		printf("\n\nDigite a Opcao Desejada: ");
		scanf("%d", &continu);

		if(continu==1){
			FILE *texto = fopen("message.txt","w");
			char frase[1000000];

			if(texto==NULL){
				printf("\nNão foi possivel abrir o arquivo...");
				return;
			}
            else{
                system("cls || clear");
                printf("\nDigite o texto desejado: ");

                fflush(stdin);
                scanf(" %[^\n]", frase);
                fprintf(texto, "%s", frase);

                if(strlen(frase)>1000000){
                    printf("\n\nA frase digitade ultrapassa os limites permitidos... O programa seá abortado...");
                    pause();
                    fclose(texto);
                    exit(0);
                }

                while(1){

                    fflush(stdin);

                    printf("\n_______________________________________");
                    printf("\n\n1- Encriptografar");
                    printf("\n\n2- Digitar Outra Frase");
                    printf("\n\n3- Menu");
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
                        MenuDigitar();
                    	break;
                    }
                	else if(x==3){
                        fclose(texto);
                        break;
                    }
                	else{
						printf("\n\nDigite um Opcao Valida...");
                        pause();
                        system("cls || clear");
                        printf("\n%s\n\n", frase);
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
			printf("\n\nOpcao Invalida...");
			pause();
		}
	}
}
// -------------------------------------- Menu Opção NULA --------------------

void OpcaoNula(){

    int y, nova;

    while(1){
        system("cls || clear");
        printf("\nATENCAO! O arquivo apenas sera lido se for nomeado como (crypto.txt) ");
        printf("\n\nO tal deve se situar mesma pasta onde este programa esta salvo...");
        printf("\nCaso ja tenhas escolhido digitar seu texto, o arquivo sera criptografado normalmente...");
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
        printf("\n\nDigite o código conhecido: ");
        scanf("%d", &y);
        if(y==1){
            printf("\n_______________________________________");
            printf("\n\nDigite a Chave conhecida: ");
            scanf("%d", &nova);
            Descriptografar("cesar", nova);
        }
        else if(y==2){
            Descriptografar("ascii", 0);
        }
        else if(y==3){
            Descriptografar("subs", 0);
        }
        else{
            printf("\n\nDigite uma opcao valida...");
            pause();
            continue;
        }
        getchar();
        return;
    }
}

// ------------------------------- MENU ---------------------------------------

void menu(){

    int x;

	while(1){

        fflush(stdin);

		system("clear || cls");
		printf("\n\tEncriptografador");
		printf("\n_______________________________________");
		printf("\n\n1- Digitar um mensagem");
		printf("\n\n2- Encriptografia");
		printf("\n\n3- Descriptografar");
		printf("\n\n4- Sair");
		printf("\n_______________________________________");
		printf("\n\nDigite a opcao desejada: ");
		scanf("%s", &x);

		switch(x){
			case '1':
				MenuDigitar();
				break;
			case '2':
				Criptografar();
				break;
            case '3':
                OpcaoNula();
                break;
			case '4':
				printf("\nFinalizando Programa...\n");
				pause();
				exit (0);
			default:
				printf("\nDigite um Opcao valida!\n");
                pause();
		}
	}
}

// ------------------------------- Main --------------------------------------

int main(int argc, char *argv[]){

	menu();

	return 0;
}
