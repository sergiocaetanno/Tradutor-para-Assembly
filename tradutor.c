#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define columns 256
#define sizeMatrix 100

int posicaoAtualPilha = 0;
int valorAlocadoPilha = 0;
int posicaoPilhaVariaveisLocais[5];

// REMOVE O '\n' DO FIM DA LINHA
void remove_newline(char *ptr)
{
    while (*ptr)
    {
        if (*ptr == '\n')
            *ptr = 0;
        else
            ptr++;
    }
}


//INICIALIZA A MATRIZ DE TRADUÇÃO COM O ARQUIVO .blp
void inicializaMatrizTraducao(char *line,int nLinhas, int nColunas)
{


    char getLine[columns];

    for(int i = 0; i<nLinhas; i++)
    {
        for(int j = 0; j<nColunas; j++)
        {

            *((line+j)+i*columns) = '\0';
        }
    }
    int i = 0;
    while(fgets(getLine, columns, stdin) != NULL)
    {
        remove_newline(getLine);
        strcpy((line + i * columns),getLine);
        i++;
    }

}

//PASSA COMO PARÂMETROS A MATRIZ DE TRADUÇÃO, A PALAVRA DA SINTAXE A SER PROCURADA E O NÚMERO DA LINHA ATUAL
//VERIFICA SE A PALAVRA DA SINTAXE ESCOLHIDA ESTÁ NO PROGRAMA
//CASO ESTEJA, RETORNA 1. CASO CONTRÁRIO, RETORNA ZERO E PRINTA "ERRO DE SINTAXE"
int verificaSintaxe(char *ptrMatrizTraducao, char sintaxe[columns], int countCopy)
{

    char *ptrPercorreLinha;

    countCopy++;
    ptrMatrizTraducao = ptrMatrizTraducao + (columns * countCopy);

    while(countCopy < sizeMatrix)
    {

        if(*ptrMatrizTraducao == '\0')
        {
            countCopy++;
            ptrMatrizTraducao = ptrMatrizTraducao + columns;
            continue;
        }
        else
        {
            if(strncmp(ptrMatrizTraducao,"function",8)==0){
                break;
            }

            ptrPercorreLinha = ptrMatrizTraducao;
            while(*ptrPercorreLinha!='\0')
            {
                if(strncmp(ptrPercorreLinha,sintaxe, strlen(sintaxe) + 1) == 0)
                {
                    printf("Linha%d: %s\n", countCopy + 1,sintaxe);
                    return countCopy;
                }
                ptrPercorreLinha++;
            }
            countCopy++;
            ptrMatrizTraducao = ptrMatrizTraducao + columns;

        }
    }
    printf("\n\n-- ERRO DE SINTAXE --\n\n");
    return 0;
}

//VERIFICA SE A LINHA ATUAL É UMA DECLARAÇÃO DE FUNÇÃO E SE A SINTAXE DAS PRÓXIMAS LINHAS ESTÁ COMPLETA (ATÉ O 'end')
int verificaDeclaracaoFunc(char *line, int count)
{

    int r, p1, p2, p3, fn;
    int countBackup;

    r = sscanf((line + count * 256) ,"function f%d pi%d pi%d pi%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }

            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }


    r = sscanf((line + count * 256),"function f%d pi%d pi%d pa%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256),"function f%d pi%d pa%d pi%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256),"function f%d pa%d pi%d pi%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256),"function f%d pi%d pa%d pa%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256),"function f%d pa%d pi%d pa%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256),"function f%d pa%d pa%d pi%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256),"function f%d pa%d pa%d pa%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d pi%d pi%d", &fn, &p1, &p2);
    if(r == 3)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d pi%d pa%d", &fn, &p1, &p2);
    if(r == 3)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d pa%d pi%d", &fn, &p1, &p2);
    if(r == 3)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d pa%d pa%d", &fn, &p1, &p2);
    if(r == 3)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d pi%d", &fn, &p1);
    if(r == 2)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d pa%d", &fn, &p1);
    if(r == 2)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    r = sscanf((line + count * 256), "function f%d", &fn);
    if(r == 1)
    {
        printf("Linha %d: %s\n", count + 1, line + count * 256);
        countBackup = count;
        count = verificaSintaxe(line, "def", count);
        if(count!= 0)
        {
            count = verificaSintaxe(line, "enddef", count);
            if(count != 0)
            {
                count = verificaSintaxe(line,"return",count);
                if(count!=0)
                {
                    count = verificaSintaxe(line,"end",count);
                    if(count !=0)
                    {
                        count = countBackup;
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp\nleave\nret\n\n", fn, fn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

int verificaDefVar(char *line, int count){

    int r = 0;
    int idVar, constValue;
    int contadoraValorAlocarPilha = 1; //A QUANTIDADE DE MEMÓRIA ALOCADA PARA A PILHA DEVE SER MÚLTIPLA DE 16
    float tmp;
    r = sscanf((line + count * 256), "var vi%d", &idVar);
    if(r == 1){
    	posicaoAtualPilha += 4;
        printf("Linha %d: %s\n", count + 1, line + 256 * count);
        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        while(tmp < 1){
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha){
            printf("subq $%d, %%rsp", contadoraValorAlocarPilha * 16);
            printf("        #var vi%d em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocais[idVar-1] = posicaoAtualPilha;

        }
        else{
            printf("#var vi%d em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocais[idVar-1] = posicaoAtualPilha;
        }

        valorAlocadoPilha = contadoraValorAlocarPilha * 16;

        return 1;
    }
    r = sscanf((line + count * 256), "vet va%d size ci%d", &idVar, &constValue);
    if(r == 2){
    	posicaoAtualPilha = posicaoAtualPilha + 4 * constValue;
        printf("Linha %d: %s\n", count + 1, line + 256 * count);
        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        while(tmp < 1){
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha){
            printf("subq $%d, %%rsp", contadoraValorAlocarPilha * 16);
            printf("        #vet va%d[0] em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocais[idVar-1] = posicaoAtualPilha;
        }
        else{
            printf("#vet va%d[0] em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocais[idVar-1] = posicaoAtualPilha;
        }


        valorAlocadoPilha = contadoraValorAlocarPilha * 16;



		return 1;
    }

    return 0;
}


int main()
{
    setlocale(LC_ALL,"Portuguese");
    char line[sizeMatrix][columns];
    int count = 0; //A LINHA ATUAL É (count + 1)
    inicializaMatrizTraducao(line, sizeMatrix, columns);

    /*PRINTA ARQUIVO .blp
    for(int i = 0; i<sizeMatrix; i++){
        if(line[i][0]!='\0'){
            printf("%s\n",line[i]);
        }
    }*/



    //LÊ UMA LINHA POR VÊZ
    while (count<100)
    {

        /*________________________________________VERIFICA SE É DECLARAÇÃO DE FUNÇÃO________________________________________*/
        if(verificaDeclaracaoFunc(line ,count) == 1)
        {
            count++;
            continue;
        }

        /*___________________________________________________________________________________________________________________________________________*/


        /*________________________________________VERIFICA SE É DEFINIÇÃO DE VARIÁVEL________________________________________*/
        if(verificaDefVar(line, count) == 1)
        {
            count++;
            continue;
        }
        /*___________________________________________________________________________________________________________________________________________*/

        count++;
    }
    return 0;
}
