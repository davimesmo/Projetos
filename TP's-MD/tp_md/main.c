#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int x;
    int y;
}Pares;

int compareY(const void *a, const void *b){
     Pares *elem1 = (Pares *)a;
     Pares *elem2 = (Pares *)b;
    
    return elem1->y - elem2->y;
}
int compareX(const void *a, const void *b){
     Pares *elem1 = (Pares *)a;
     Pares *elem2 = (Pares *)b;
    
    if(elem1->x == elem2->x){
        if(elem1->y == elem2->y){
        return 0;}
        else if(elem1->y < elem2->y){
            return -1;
        }else{
            return 1;
        }
    }else{
        return elem1->x - elem2->x;
    }
}

int main(){
    int qtde;
    scanf("%i", &qtde);
    int pontos[50];
    for(int i = 0; i<qtde; i++){
        scanf("%i", &pontos[i]);
    }
    Pares pares[999];
    int cont = 0;
    int aux = 0; 
    while(aux < 18){
        if(scanf("%i %i", &pares[cont].x, &pares[cont].y) != EOF){
         cont++;
         aux++;
        }else{
            break;
        } 
    }
    //checar se é reflexiva
    char retorno = 'V';
    int ehReflexiva =0;
    int auxiliar = 0;
    int *reflexo = (int*)malloc(qtde * sizeof(int));
    for (int j = 0; j < qtde; j++){
    int a = 0;    
        for(int k=0; k < cont; k++){
            if(pontos[j] == pares[k].x && pontos[j] == pares[k].y){
                    a+=1;
            }
        }
    if (a == 0){
        retorno = 'F';
        reflexo[auxiliar] = pontos[j];
        auxiliar+=1;
        ehReflexiva++;
    }
    }
    printf("Propriedades\n");
    printf("1. Reflexiva: %c\n", retorno);
    if(retorno == 'F'){
        for(int g = 0; g< auxiliar; g++){
            if(g == (auxiliar -1)){
            printf("(%i, %i)", reflexo[g], reflexo[g]);}else{
            printf("(%i, %i), ", reflexo[g], reflexo[g]);    
            }
        }
        printf("\n");
    }

    //checar se é irreflexiva
    auxiliar = 0;
    retorno = 'V';
    int possuiIguais = 0;
    for (int u = 0; u < qtde; u++){
    int a = 0;    
        for(int f=0; f < cont; f++){
            if(pontos[u] == pares[f].x && pontos[u] == pares[f].y){
                    a+=1;
                    possuiIguais+=1;
            }
        }
    if (a == 1){
        retorno = 'F';
        reflexo[auxiliar] = pontos[u];
        auxiliar+=1;
    }
    }
    printf("2. Irreflexiva: %c\n", retorno);
    int ehIrreflexiva =0;
    if(retorno == 'F'){
        ehIrreflexiva = 1;
        for(int h = 0; h< auxiliar; h++){
            if(h == (auxiliar-1)){
            printf("(%i, %i)", reflexo[h], reflexo[h]);}else{
            printf("(%i, %i), ", reflexo[h], reflexo[h]);    
            }
        }
        printf("\n");
    }
    //checagem de simetria
    retorno = 'V';
    auxiliar = 0;
    int aux3 = 0;
    int ehSimetrica =0;
    Pares *simetricos = (Pares*)malloc(cont * sizeof(Pares));
    Pares *asimetricos = (Pares*)malloc(cont * sizeof(Pares));
    for(int c = 0; c < cont; c++ ){
    aux = 0;  
        if(pares[c].x != pares[c].y){
           for (int p = 0; p < cont; p++){
           if(pares[c].x == pares[p].y && pares[c].y == pares[p].x){
            aux+=1;
            int repetiu = 0;
            for(int iterador = 0; iterador < auxiliar; iterador++){
                if(pares[p].y == simetricos[iterador].y && pares[p].x == simetricos[iterador].x ||pares[p].x == simetricos[iterador].y && pares[p].y == simetricos[iterador].x ){
                    repetiu++;  
                }
            }
            if(repetiu == 0){
            if(pares[c].x < pares[c].y){
            simetricos[auxiliar].x = pares[c].x;
            simetricos[auxiliar].y = pares[c].y;}else{
            simetricos[auxiliar].x = pares[c].y;
            simetricos[auxiliar].y = pares[c].x;    
            }
            auxiliar++; }
           }
            
           }
           
        }else{
            aux = 1;
        }
    if(aux == 0){
        retorno = 'F';          
            asimetricos[aux3].x = pares[c].x;
            asimetricos[aux3].y = pares[c].y;
            aux3+=1;   
            ehSimetrica++;      
         
    }
    }
    int num = sizeof(asimetricos) / sizeof(asimetricos[0]);
    
    qsort(asimetricos, (aux3), sizeof(Pares), compareY);
    qsort(simetricos, (auxiliar), sizeof(Pares), compareX);

    printf("3. Simetrica: %c\n", retorno);
    if(retorno == 'F'){
        for(int q = 0; q < aux3; q++){
            if(q == (aux3-1)){
                printf("(%i, %i)", asimetricos[q].y, asimetricos[q].x);
            }else{
                printf("(%i, %i), ", asimetricos[q].y, asimetricos[q].x);
            }
        }
        printf("\n");
    }
    int ehAntisimetrica = 0;
    if(retorno == 'F' && possuiIguais >=0){
        printf("4. Anti-Simetrica: V\n");
    }else if(retorno == 'V' && possuiIguais > 0){
        printf("4. Anti-Simetrica: F\n");
        ehAntisimetrica = 1;
        for(int d = 0; d < auxiliar; d++ ){
            if(d==(auxiliar-1)){
                printf("((%i, %i), (%i, %i))", simetricos[d].x, simetricos[d].y, simetricos[d].y, simetricos[d].x);
            }else{
                printf("((%i, %i), (%i, %i)), ", simetricos[d].x, simetricos[d].y, simetricos[d].y, simetricos[d].x);
            }
        }
        printf("\n");
    }
    if (ehAntisimetrica == 0 && ehIrreflexiva == 0)
    {
        printf("5. Assimetrica: V\n");
    }else{
        printf("5. Assimetrica: F\n");
    }
    //checagem transitiva
    retorno = 'V';
    Pares *intransitivos = (Pares*)malloc(cont * sizeof(Pares));
    int aux5 =0;
    int aux6 = 0;
    int ehTransistiva = 0;
    for(int v = 0; v<cont; v++){
        int aux4 = 0;
        if(pares[v].x != pares[v].y){
             
           // printf("ENTROU DIFERENTES %i\n", v);
            for(int contador = 0; contador < cont; contador++){
                if(pares[contador].x == pares[v].y && pares[contador].x != pares[contador].y){
                    //printf("ENTROU confere no y - n:%i xc%i yc%i xv%i yv%i\n", contador, pares[contador].x, pares[contador].y, pares[v].x, pares[v].y);
                    for(int it = 0; it < cont; it++){
                        if(pares[it].y == pares[contador].y && pares[it].x == pares[v].x){
                            //printf("ENTROU confere se o z é igual ao y e se o x é igual ao x - X:%i, Y:%i, Z:%i\n", pares[it].x, pares[v].y, pares[it].y );
                            aux4++;
                        
                            
                        }

                    }
                    if(aux4 == 0){
                        intransitivos[aux5].x = pares[v].x;
                        intransitivos[aux5].y = pares[contador].y;
                        aux5++;
                    }
                }
            }
        }else{
            aux4++;
        }
        
        if(aux4 == 0){
            retorno = 'F';
            ehTransistiva++;
        }
    }
    printf("6. Transitiva: %c\n", retorno);
    if(retorno == 'F'){
        for(int fc = 0; fc <aux5; fc++ ){
            if(fc == (aux5-1)){
                printf("(%i, %i)", intransitivos[fc].x, intransitivos[fc].y);
            }else{
                printf("(%i, %i), ", intransitivos[fc].x, intransitivos[fc].y);
            }
        }
        printf("\n");
    }
    printf("\n");
    if(ehReflexiva == 0 && ehSimetrica == 0 && ehTransistiva ==0){
        printf("Relacao de Equivalencia: V\n");
    }else{
        printf("Relacao de Equivalencia: F\n");
    }
    if(ehReflexiva == 0 && ehAntisimetrica == 0 && ehTransistiva == 0){
        printf("Relacao de Ordem Parcial: V\n");
    }else{
        printf("Relacao de Orde Parcial: F\n");
        
    }
    printf("\n");
    //fecho reflexivo
    if(ehReflexiva == 0){
        printf("Fecho reflexivo da relaçao: R\n");
    }else{
        printf("Fecho reflexivo da relaçao:\n");
        
    }
    printf("\n");
    return 0;
}
