#include <stdio.h>
#include <string.h>

typedef struct {
    int naipe;
    int carta;
} Carta;

typedef struct {
	Carta carta_mao[4];
	Carta monte[52]; 
}Jogador;

char* mostraCarta(int vcarta)
{
	char retorno[10];
	char* v_retorno;
	strcpy(retorno, " ");
	
	
	switch(vcarta) {
        case 0:
            strcpy(retorno, "As");
            break;
            
        case 1:
            strcpy(retorno, "2");
            break;
        case 2:
            strcpy(retorno, "3");
            break;
        case 3:
            strcpy(retorno, "4");
            break;
        case 4:
            strcpy(retorno, "5");
            break;
        case 5:
            strcpy(retorno, "6");
            break;
        case 6:
            strcpy(retorno, "7");
            break;
        case 7:
            strcpy(retorno, "8");
            break;
        case 8:
            strcpy(retorno, "9");
            break;
        case 9:
            strcpy(retorno, "10");
            break;
        case 10:
            strcpy(retorno, "Valete");
            break;
        case 11:
            strcpy(retorno, "Dama");
            break;
        case 12:
            strcpy(retorno, "Rei");
            break;
        case -1:
        	strcpy(retorno, "Vazio");
    }
    
    v_retorno = &retorno[0] ;
    return v_retorno;
}

char* mostraNaipe(int vnaipe)
{
	char retorno[10];
	char* v_retorno;
	strcpy(retorno, " ");
	
	switch(vnaipe) {
        case 0:
            strcpy(retorno, "Copas");
            break;
        case 1:
            strcpy(retorno, "Ouros");
            break;
        case 2:
            strcpy(retorno, "Paus");
            break;
        case 3:
            strcpy(retorno, "Espadas");
            break;
		case -1:
			strcpy(retorno, "Vazio");            
    }

    v_retorno = &retorno[0] ;
    return v_retorno;
}


void mostra_baralho(Carta carta)
{
    int i, j;
    char  vnaipe[15] ;
	char  vcarta[15] ;
    strcpy(vnaipe, mostraNaipe(carta.naipe));
    strcpy(vcarta, mostraCarta(carta.carta));	
    
	printf("\n %s de %s ", vcarta, vnaipe);
	
};


int main() {
	
	srand(time(NULL));
	int i,j,k,l,m, jog, passa;
	int escolha;
	int qtd_jogador = 3;
	Carta cartas_na_mesa[20];
	int num_cartas_mesa;
	Carta vazio = {-1, -1};
	
	printf("#######################\n");
	printf("Bem vindo ao Rouba Monte\n");
	printf("1 - Jogar\n");
	printf("2 - Sair\n");
	printf("#######################\n");
	printf("Qual a sua escolha? ");
	scanf("%d", &escolha);
	
	while(escolha == 1){
		
		int terminou = 0;
		
		//Cria o baralho
		Carta baralho[52];
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 13; j++) {
		        baralho[i * 13 + j].naipe = i;
		        baralho[i * 13 + j].carta = j;
		    }
		}
		
		//Mostra o Baralho
		/*
		for(i = 0; i < 52; i++){
			mostra_baralho(baralho[i]);
		}
		*/
		
		//Qauntidades de Jogadores
		printf("Quantos Jogadores vao jogar?");
		scanf("%d", &qtd_jogador);
		if(qtd_jogador > 8 || qtd_jogador < 3){
			printf("Esse numero de jogadores ultrapassam o limite\n");
			break;
		}
		Jogador jogador[qtd_jogador];
		//Dar as cartas para o jogadores
		for(i = 0; i < qtd_jogador; i++){
			for(j = 0; j < 4; j++){
				int aleatorio;
				do{
					aleatorio = rand() % 52;
					if(baralho[aleatorio].carta != -1){
						jogador[i].carta_mao[j] = baralho[aleatorio];
						baralho[aleatorio] = vazio;
						break;
					}
				}while(baralho[aleatorio].carta == -1);
			}
		}
		
		//preenche a mesa de vazio
		for(i = 0; i < 20; i++){
			cartas_na_mesa[i] = vazio;
		}
		
		//preenche o monte dos jogadores de vazio
		for(i = 0; i < qtd_jogador; i++){
			for(j = 0; j < 52; j++){
				jogador[i].monte[j] = vazio;
			}	
		}
		
		//Coloca as cartas na mesa
		for(i = 0; i < 4; i++){
			int aleatorio;
			
			do{
				aleatorio = rand() % 52;
				if(baralho[aleatorio].carta != -1){
					cartas_na_mesa[i] = baralho[aleatorio];
					baralho[aleatorio] = vazio;
					break;
				}
			}while(baralho[aleatorio].carta == -1);
			num_cartas_mesa = 4;
		}
		
		while(terminou != 1){
			
			//Checa se tem carta na mão do jogador
			for(i = 0; i < qtd_jogador; i ++){
				k = 0;
				for(j = 0; j < 4; j++){
					if(jogador[i].carta_mao[j].carta == vazio.carta){
						k = k + 1;
					}
				}
				if(k == 4){
					for(j = 0; j < 4; j++){
						int aleatorio;
						do{
							aleatorio = rand() % 52;
							if(baralho[aleatorio].carta != -1){
								jogador[i].carta_mao[j] = baralho[aleatorio];
								baralho[aleatorio] = vazio;
								break;
							}
							l = 0;
							for(k = 0; k < 52; k++){
								if(baralho[k].carta == -1){
									l++;	
								}
								if(l >= 52){
									printf("\n\n!!!! Acabou o Jogo !!!\n\n");
									int maior = 0;
									int ganhador = 0;
									for(i = 0; i < qtd_jogador; i++){
										m = 0;
										printf("\nJogador %d -- Monte: \n", i);
										for(j = 1; j < 52; j++){
											if(jogador[i].monte[j].carta != -1){
												mostra_baralho(jogador[i].monte[j]);
												m = m + 1;
											}
										}
										printf("\n");
										if(maior < m){
											ganhador = i;
											maior = m;
										}
									}
									printf("\n\nO ganhador e o jogador ---> %d <------\n\n", ganhador);
									printf("Deseja simular novamente? 1.Sim 2.Nao: ");
									scanf("%d", &escolha);
									terminou = 1;
									break;
								}
							}
							if(terminou == 1){
								break;
							}
						}while(baralho[aleatorio].carta == -1);
					}	
				}
			}
			if(terminou == 1){
				break;
			}
			
			//Checa se tem cartas na mesa
			if(num_cartas_mesa == 0){
				for(i = 0; i < 4; i++){
					int aleatorio;
			
					do{
						aleatorio = rand() % 52;
						if(baralho[aleatorio].carta != -1){
							cartas_na_mesa[i] = baralho[aleatorio];
							baralho[aleatorio] = vazio;
							break;
						}
					}while(baralho[aleatorio].carta == -1);
					num_cartas_mesa = 4;
				}
			}else{
				num_cartas_mesa = 0;
				for(i = 0; i < 20; i++){
					if(cartas_na_mesa[i].carta != -1){
						num_cartas_mesa = num_cartas_mesa + 1;
					}
				}
			}
			
			//Mostra as Cartas dos jogadores
			for(i = 0; i < qtd_jogador; i++){
				printf("\n°° Jogador %d: °° \n", i);
				for(j = 0; j < 4; j++){
					mostra_baralho(jogador[i].carta_mao[j]);
				}
				printf("\n\n°°  Monte:  °° ");
				for(j = 1; j < 52; j++){
					if(jogador[i].monte[j].carta != vazio.carta){
						mostra_baralho(jogador[i].monte[j]);	
					}
				}
				printf("\n");
			}
			
			printf("\n### Cartas na Mesa ###\n");
			for(i = 0; i < num_cartas_mesa; i++){
				mostra_baralho(cartas_na_mesa[i]);
			}
			
			
			for(i = 0; i < qtd_jogador; i++){
				passa = 0;
				printf("\n\n++++ Vez do Jogador %d ++++++\n\n", i);
				for(jog = 0; jog < qtd_jogador; jog++){
					if(i != jog){
						int index_monte_jog = 0;
						int index_monte_i = 0;
						for(j = 1; j < 52; j++){
							if(jogador[jog].monte[j].carta != -1){
								index_monte_jog = index_monte_jog + 1;
							}
						}
						if(index_monte_jog != 0){
							for(j = 0; j < 4; j++){
								if(jogador[i].carta_mao[j].carta == jogador[jog].monte[index_monte_jog].carta && jogador[i].carta_mao[j].carta != -1){
									for(k = 1; k < 52; k++){
										if(jogador[i].monte[k].carta != -1){
											index_monte_i = index_monte_i + 1;
										}
									}
									for(k = 1; k <= index_monte_jog+1; k++){
										jogador[i].monte[index_monte_i+1] = jogador[jog].monte[k];
										jogador[jog].monte[k] = vazio;
										index_monte_i++;
									}
									jogador[i].monte[index_monte_i+1] = jogador[i].carta_mao[j];
									jogador[i].carta_mao[j] = vazio;
									passa = 1;
									printf("\n!!!! O Jogador %d roubou o monte do jogador %d !!!!!\n", i, jog);
									break;
								}
							}
						}
					}
					if(passa == 1){
						break;
					}
				}
				for(j = 0; j <= num_cartas_mesa; j++){
					for(k = 0; k < 4; k++){
						if(jogador[i].carta_mao[k].carta == cartas_na_mesa[j].carta && jogador[i].carta_mao[k].carta != -1){
							for(l = 1; l < 52; l++){
								if(jogador[i].monte[l].carta == -1){
									jogador[i].monte[l] = cartas_na_mesa[j];
									jogador[i].monte[l+1] = jogador[i].carta_mao[k];
									
									while(cartas_na_mesa[j+1].carta != vazio.carta){
										cartas_na_mesa[j] = cartas_na_mesa[j+1];
										cartas_na_mesa[j+1] = vazio;
										j++;
									}
									
									jogador[i].carta_mao[k] = vazio;
									
									printf(" ---- O jogador %d adicionou no seu monte as carta: -------", i);
									mostra_baralho(jogador[i].monte[l]);
									mostra_baralho(jogador[i].monte[l+1]);
									printf("\n");
									passa = 1;
									break;
								}
							}
						}
						if(passa == 1){
							break;
						}
						if(k == 3 && j == num_cartas_mesa && passa == 0){
							printf("O jogador %d nao teve nenhuma carta, tera que descartar uma\n\n", i);
							int aleatorio;
							
							do{
								aleatorio = rand() % 5;
								
								if(jogador[i].carta_mao[aleatorio].carta != -1){
									for(l = 0; l < 20; l++){
										if(cartas_na_mesa[l].carta == -1){
											cartas_na_mesa[l] = jogador[i].carta_mao[aleatorio]; 
											printf(" -------- Foi descartado a carta ------------");
											mostra_baralho(jogador[i].carta_mao[aleatorio]);
											printf("\n");
											jogador[i].carta_mao[aleatorio] = vazio;
											break;
										}
									}
									break;
								}
							}while(jogador[i].carta_mao[aleatorio].carta == vazio.carta);
						}
					}
					if(passa == 1){
						break;
					}
				}
			}
			
							
		}
	}
	
	printf("Tchau\n");

    return 0;
}
