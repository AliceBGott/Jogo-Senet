#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

char t[30] = {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X',
              ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ',' ', ' ',
              ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' '
             };

int jogador = 1;
int comecou;
int pVez=0;







int verificaPrimeiraFileira () {
    int i;
    if(jogador == comecou) {
        for(i=0; i<10; i++) {
            if(t[i] == 'X') {
                return 1;
            }
        }
    } else {
        for(i=0; i<10; i++) {
            if(t[i] == 'O') {
                return 1;
            }
        }

    }
    return 0;
}










int verificaPossivel (int e) {
    int i;
    char j;
    char qj;
    if(jogador == comecou) {
        j = 'X';
        qj = 'O';
    } else {
        j = 'O';
        qj ='X';
    }
    for(i=0; i<30; i++) {
        if(t[i] == j) {
            if(t[i+e] == ' ') {
                return 1;
            }
            if(t[i+e] == qj) {
                if(protegida(i+e) == 0) {
                    return 1;
                }
            }

        }
    }
    return 0;

}





int estilete() {
    int a, b, c, d, r;
    a = rand()% 2;
    b = rand()% 2;
    c = rand()% 2;
    d = rand()% 2;

    r = a + b + c + d;
    if (r == 0) {
        r = 6;
    }
    printf("Numero sorteado no estilete: %d\n", r);
    return r;

}







int protegida (int p) {
    if((p<=29) && (t[p] != ' ')) {
        if((p==25) || (p == 27) || (p==28)) {
            return 1;
        }
        if(((p-1 >= 0) && (t[p] == t[p-1])) || ((p+1 <= 29) && (t[p] == t[p+1]))) {
            return 1;
        }
    }
    return 0;
}






int verificaMovimentoProblematico(int e, int p) {
    int i;
    char j;
    if(jogador == comecou) {
        j = 'X';
    } else {
        j = 'O';
    }
    if(t[p-1] != j) {
        printf("Nao eh a sua peca\n");
        return 0;
    }
    if(protegida(p-1+e) == 1) {
        printf("Peca protegida, nao pode ser atacada\n");
        return 0;
    }
    if(t[p-1+e] == j) {
        printf("Nao pode atacar sua propria peca\n");
        return 0;
    }
    if(p-1+e > 29) {
        if(verificaPrimeiraFileira() == 1) {
                printf("Ainda tem peca na primeira fileira\n");
                if(t[29] == ' '){
                    return 2;
                }else{
                    if(t[29] == j){
                            return 0;
                    }
                    return 3;
                }



        }
    }

    return 1;

}







int posicaoUsuario (int e) {
    int p;
    char j;
    if(jogador == comecou) {
        j = 'X';
    } else {
        j = 'O';
    }
    printf("Digite a casa da peca que deseja mover: ");
    scanf("%d", &p);
    while(verificaMovimentoProblematico(e,p) == 0 ) {
        printf("O movimento nao eh possivel, digite novamente: ");
        scanf("%d", &p);
    }


    return p-1;
}








void imprime() {
    int i;

    for(i=0; i<10; i++) {
        printf(" %d ", i+1);
    }
    printf("\n");
    for(i=0; i<10; i++) {
        printf("[%c]",t[i]);
    }
    printf("\n");
    printf("\n");
    for(i=19; i>9; i--) {
        printf(" %2d",i+1);
    }
    printf("\n");
    for(i=19; i>9; i--) {
        printf("[%c]",t[i]);
    }
    printf("\n");
    printf("\n");
    for(i=20; i<30; i++) {
        printf(" %2d", i+1);
    }
    printf("\n");
    for(i=20; i<30; i++) {
        printf("[%c]",t[i]);
    }
    printf("\n");
    printf("\n");

}








void move(int e) {
    int p;
    int i;
    char j, aux;
    printf("Vez do jogador %d\n", jogador);

    if(jogador == comecou) {
        j = 'X';
    } else {
        j = 'O';
    }
    if(verificaPossivel(e) == 0) {
        printf("Nao ha nenhum movimento possivel, passe a vez\n");
        if(jogador == 1) {
            jogador = 2;
        } else {
            jogador = 1;
        }
        return;
    }
    if((j == 'O') && (pVez == 0) ) {
        pVez = 1;
        if(t[8] == 'O') {
            p = 8;
        } else {
            for(i=29; i>=0; i--) {
                if(t[i] == 'O') {
                    p = i;
                    break;
                }
            }
        }
        if(verificaMovimentoProblematico(e,p+1) == 0) {
            if(jogador == 1) {
                jogador = 2;
            } else {
                jogador = 1;
            }
            printf("Passando a vez\n");
            return;
        }
    } else {
        p = posicaoUsuario(e);
    }

    if(p+e == 26) {
        if(t[14] == ' ') {
            t[p] = ' ';
            t[14] = j;
        } else {
            if(t[e-1] == ' '){
                t[p] = ' ';
                t[e-1] = j;
            }else{
                for(i=e;i<29;i++){
                    if(t[i] == ' '){
                        t[i] = j;
                        t[p] = ' ';
                        break;
                    }
                }
            }

        }
    } else {
        //trocaPecaDeLugar
        if(p+e >= 29){
            if(verificaMovimentoProblematico(e, p) == 2){
                t[p] = ' ';
                t[29] = j;
            }
            if(verificaMovimentoProblematico(e,p) == 3){
                aux = t[p];
                t[p] = t[p+e];
                t[p+e] = aux;
            }else{
                 t[p] = ' ';
            }

        }else{
            aux = t[p];
            t[p] = t[p+e];
            t[p+e] = aux;
        }
    }






}









int verificaVenceu() {
    int bolinha=0, xis=0, i;
    for(i=0; i<30; i++) {
        if(t[i] == 'O') {
            bolinha ++;
        }
        if(t[i] == 'X') {
            xis ++;
        }
    }
    if(xis== 0) {
        return comecou;
    }
    if(bolinha == 0) {
        if(comecou == 1) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}











int main (int argc, char * argv[]) {
    int venceu=0;
    int e;
    printf("                               *************\n");
    printf("                               *** SENET ***\n");
    printf("                               *************\n\n");
    printf("\n");
    imprime();
    srand(time(NULL));
    while(estilete() != 1) {

        if(jogador == 1) {
            jogador = 2;
        } else {
            jogador = 1;
        }

    }
    printf("\n");
    printf("Jogador %d comeca\n", jogador);
    printf("Jogador %d = X\n", jogador);
    printf("\n");

    comecou = jogador;

    while(venceu == 0) {
        e = estilete();
        if((e==1) || (e==4) || (e==6)) {
            move(e);
        }
        if((e==2) || (e==3)) {
            move(e);
            if(jogador == 1) {
                jogador = 2;
            } else {
                jogador = 1;
            }
        }
        system("cls");
        printf("                                *************\n");
        printf("                                *** SENET ***\n");
        printf("                                *************\n\n");
        printf("\n");
        imprime();
        venceu = verificaVenceu();

    }





    printf("JOGADOR %d VENCEU!\n", venceu);


    return 0;
}






