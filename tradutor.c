#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define columns 256
#define sizeMatrix 100

int posicaoAtualPilha = 0;
int valorAlocadoPilha = 0;
int posicaoPilhaVariaveisLocaisRegistradores[8] = {0,0,0,0,0,0,0,0}; //%rdi, %rsi e %rdx ser?o salvos, respectivamente, nas posi??es 5, 6 e 7 desse vetor;
int ifCount = 1;

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

//INICIALIZA A MATRIZ DE TRADU??O COM O ARQUIVO .blp
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

//PASSA COMO PAR?METROS A MATRIZ DE TRADU??O, A PALAVRA DA SINTAXE A SER PROCURADA E O N?MERO DA LINHA ATUAL
//VERIFICA SE A PALAVRA DA SINTAXE ESCOLHIDA EST? NO PROGRAMA
//CASO ESTEJA, RETORNA 1. CASO CONTR?RIO, RETORNA ZERO E PRINTA "ERRO DE SINTAXE"
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
            if(strncmp(sintaxe,"endif",5)==0)
            {
                if(strncmp(ptrMatrizTraducao,"if",2)==0)
                {
                    break;
                }
            }

            if(strncmp(ptrMatrizTraducao,"function",8)==0)
            {
                break;
            }

            ptrPercorreLinha = ptrMatrizTraducao;
            while(*ptrPercorreLinha!='\0')
            {
                if(strcmp(sintaxe,"return")==0)
                {
                    if(strncmp(ptrPercorreLinha,sintaxe, strlen(sintaxe)) == 0)
                    {
                        printf("Linha%d: %s\n", countCopy + 1,sintaxe);
                        return countCopy;
                    }
                }
                else if(strncmp(ptrPercorreLinha,sintaxe, strlen(sintaxe) + 1) == 0)
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

//VERIFICA SE A LINHA ATUAL ? UMA DECLARA??O DE FUN??O E SE A SINTAXE DAS PR?XIMAS LINHAS EST? COMPLETA (AT? O 'end')
int verificaDeclaracaoFunc(char *line, int count)
{
    int r, p1, p2, p3, fn;
    int countBackup;
    char fmt[30] = "\n\n#C?DIGO DA FUN??O:\n\n";

    r = sscanf((line + count * 256),"function f%d pi%d pi%d pi%d", &fn, &p1, &p2, &p3);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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
                        printf("\n.globl f%d\nf%d:\npushq %%rbp\nmovq %%rsp, %%rbp%s\nleave\nret\n\n", fn, fn, fmt);
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

int verificaDefVar(char *line, int count)
{

    int r = 0;
    int idVar, constValue;
    int contadoraValorAlocarPilha = 1; //A QUANTIDADE DE MEM?RIA ALOCADA PARA A PILHA DEVE SER M?LTIPLA DE 16
    float tmp;
    r = sscanf((line + count * 256), "var vi%d", &idVar);
    if(r == 1)
    {
        posicaoAtualPilha += 4;
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);

        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;

        while(tmp < 1)
        {
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha)
        {
            printf("subq $%d, %%rsp", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
            printf("        #var vi%d em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocaisRegistradores[idVar-1] = posicaoAtualPilha;

        }
        else
        {
            printf("#var vi%d em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocaisRegistradores[idVar-1] = posicaoAtualPilha;
        }

        valorAlocadoPilha = contadoraValorAlocarPilha * 16;

        return 1;
    }
    r = sscanf((line + count * 256), "vet va%d size ci%d", &idVar, &constValue);
    if(r == 2)
    {
        posicaoAtualPilha = posicaoAtualPilha + 4 * constValue;
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);

        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;

        while(tmp < 1)
        {
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha)
        {
            printf("subq $%d, %%rsp", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
            printf("        #vet va%d[0] em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocaisRegistradores[idVar-1] = posicaoAtualPilha;
        }
        else
        {
            printf("#vet va%d[0] em -%d(%%rbp)\n\n", idVar, posicaoAtualPilha);
            posicaoPilhaVariaveisLocaisRegistradores[idVar-1] = posicaoAtualPilha;
        }

        valorAlocadoPilha = contadoraValorAlocarPilha * 16;

        return 1;
    }

    return 0;
}

int verificaCondicional(char* line, int count)
{
    int r, condition;
    int countBackup;

    //var
    r = sscanf((line + count * 256),"if vi%d", &condition);

    if(r == 1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + (count*256));
        countBackup = count;
        count = verificaSintaxe(line, "endif", count);
        if(count!= 0)
        {
            count = countBackup;

            /*TESTE TEMPOR?RIO

                posicaoPilhaVariaveisLocais[0]=4;
                posicaoPilhaVariaveisLocais[1]=8;
                posicaoPilhaVariaveisLocais[2]=12;
                posicaoPilhaVariaveisLocais[3]=16;
                posicaoPilhaVariaveisLocais[4]=40;

            TESTE TEMPOR?RIO */

            if (condition <= 5)
            {
                //printf("Linha %d: %s\n", count, line);
                printf("\n#CONDICIONAL %d\n\n", ifCount);
                //posicaoPilhaVariaveisLocais
                printf("cmpl $0, -%d(%%rbp)\n",posicaoPilhaVariaveisLocaisRegistradores[condition-1]);
                printf("je endif%d\n\n", ifCount);
                printf("#bloco da condicional %d\n\nendif%d:\n\n",ifCount, ifCount);
                ifCount++;
                //lance da contadora de ifs pra organizar os labels dos ifs em assembly
            }
            else
            {
                printf("-={ Erro: par?metro inv?lido }=-");
            }

            return 1;
        }
        else
        {
            return 0;
        }
    }

    //param
    r = sscanf((line + count * 256),"if pi%d", &condition);

    //printf("-={ Teste condicional: R = %d }=- \n", r);//teste

    if(r == 1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + (count*256));
        countBackup = count;
        count = verificaSintaxe(line, "endif", count);
        if(count!= 0)
        {
            count = countBackup;

            if (condition == 1)
            {
                //printf("Linha %d: %s\n", count, line);
                printf("\n#CONDICIONAL %d\n\n", ifCount);
                printf("cmpl $0, %%edi\n");
                printf("je endif%d\n\n", ifCount);
                printf("#bloco da condicional %d\n\nendif%d:\n\n",ifCount, ifCount);
                ifCount++;
                //lance da contadora de ifs pra organizar os labels dos ifs em assembly
            }
            else if (condition == 2)
            {
                //printf("Linha %d: %s\n", count, line);
                printf("\n#CONDICIONAL %d\n\n", ifCount);
                printf("cmpl $0, %%esi\n");
                printf("je endif%d\n\n", ifCount);
                printf("#bloco da condicional %d\n\nendif%d:\n\n",ifCount, ifCount);
                ifCount++;
                //lance da contadora de ifs pra organizar os labels dos ifs em assembly
            }
            else if (condition == 3)
            {
                //printf("Linha %d: %s\n", count, line);
                printf("\n#CONDICIONAL %d\n\n", ifCount);
                printf("cmpl $0, %%edx\n");
                printf("je endif%d\n\n", ifCount);
                printf("#bloco da condicional %d\n\nendif%d:\n\n",ifCount, ifCount);
                ifCount++;
                //lance da contadora de ifs pra organizar os labels dos ifs em assembly
            }
            else
            {
                printf("-={ Erro: par?metro inv?lido }=-");
            }

            return 1;
        }
        else
        {
            return 0;
        }
    }

    //const
    r = sscanf((line + count * 256),"if ci%d", &condition);
    if(r == 1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + (count*256));
        countBackup = count;
        count = verificaSintaxe(line, "endif", count);
        if(count!= 0)
        {
            count = countBackup;
            printf("\n#CONDICIONAL %d\n\n", ifCount);
            printf("cmpl $0, $%d\n", condition);
            printf("je endif%d\n\n", ifCount);
            printf("#bloco da condicional %d\n\nendif%d:\n\n",ifCount, ifCount);
            ifCount++;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

int verificaRetorno(char *line, int count)
{

    int r, retorno;

    r = sscanf(line + count * 256, "return vi%d", &retorno);
    if(r==1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);
        printf("movl -%d(%%rbp), %%eax\n\n", posicaoPilhaVariaveisLocaisRegistradores[retorno-1]);
        return 1;
    }

    r = sscanf(line + count * 256, "return pi%d", &retorno);
    if(r==1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);
        if(retorno == 1)
        {
            printf("movl %%edi, %%eax\n\n");
            return 1;
        }
        else if(retorno == 2)
        {
            printf("movl %%esi, %%eax\n\n");
            return 1;
        }
        else if(retorno == 3)
        {
            printf("movl %%edx, %%eax\n\n");
            return 1;
        }
    }

    r = sscanf(line + count * 256, "return ci%d", &retorno);
    if(r==1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);
        printf("movl $%d, %%eax\n\n", retorno);
        return 1;
    }

    return 0;
}

int verificaChamadaFunc(char *line, int count)
{

    int r, fn, p1, p2, p3;
    char param1[10] = {'\0'}, param2[10] = {'\0'}, param3[10] = {'\0'};
    int contadoraValorAlocarPilha = 1; //A QUANTIDADE DE MEM?RIA ALOCADA PARA A PILHA DEVE SER M?LTIPLA DE 16
    float tmp;

    r = sscanf(line + 256 * count, "call f%d %s %s %s", &fn, param1, param2, param3);
    if(r == 1)
    {
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);
        printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
        return 1;
    }

    else if(r == 2)
    {
        posicaoAtualPilha += 8;
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);

        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;

        while(tmp < 1)
        {
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha)
        {
            printf("subq $%d, %%rsp\n", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
            posicaoPilhaVariaveisLocaisRegistradores[5] = posicaoAtualPilha;
            printf("movq %%rdi, -%d(%%rbp)        #salva %%rdi em -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);

            //------------------------------------------------PASSAGEM DE PAR?METROS-----------------------------------------------------------------------------------------
            if(strncmp(param1,"vi",2) == 0)
            {
                sscanf(param1, "vi%d", &p1);
                printf("movl -%d(%%rbp), %%edi        #passa vari?vel local como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"va",2) == 0)
            {
                sscanf(param1, "va%d", &p1);
                printf("leaq -%d(%%rbp), %%rdi        #passa endere?o inicial de vari?vel local array como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1-1]);
            }
            else if(strncmp(param1,"pi",2) == 0)
            {
                sscanf(param1, "pi%d", &p1);
                if(p1 == 1){
                    printf("movl %%edi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movl %%esi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movl %%edx, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }

            }
            else if(strncmp(param1,"pa",2) == 0)
            {
                sscanf(param1, "pa%d", &p1);

                if(p1 == 1){
                    printf("movq %%rdi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movq %%rsi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movq %%rdx, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }

            }
            else if(strncmp(param1,"ci",2) == 0)
            {
                sscanf(param1, "ci%d", &p1);
                printf("movl $%d, %%edi        #passa constante como primeiro par?metro\n\n", p1);

            }
            //---------------------------------------------------------------------------------------------------------------------------------------------------------------
            printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
            printf("movq -%d(%%rbp), %%rdi        #recupera %%rdi de -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("addq $%d, %%rsp        #desaloca valor alocado para registradores ap?s recuper?-los\n\n", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
        }
        else
        {
            posicaoPilhaVariaveisLocaisRegistradores[5] = posicaoAtualPilha;
            printf("movq %%rdi, -%d(%%rbp)        #salva %%rdi em -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);

            //------------------------------------------------PASSAGEM DE PAR?METROS-----------------------------------------------------------------------------------------
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1
            if(strncmp(param1,"vi",2) == 0)
            {
                sscanf(param1, "vi%d", &p1);
                printf("movl -%d(%%rbp), %%edi        #passa vari?vel local como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"va",2) == 0)
            {
                sscanf(param1, "va%d", &p1);
                printf("leaq -%d(%%rbp), %%rdi        #passa endere?o inicial de vari?vel local array como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"pi",2) == 0)
            {
                sscanf(param1, "pi%d", &p1);
                if(p1 == 1){
                    printf("movl %%edi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movl %%esi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movl %%edx, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"pa",2) == 0)
            {
                sscanf(param1, "pa%d", &p1);

                if(p1 == 1){
                    printf("movq %%rdi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movq %%rsi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movq %%rdx, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"ci",2) == 0)
            {
                sscanf(param1, "ci%d", &p1);
                printf("movl $%d, %%edi        #passa constante como primeiro par?metro\n\n", p1);

            }
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1
            //---------------------------------------------------------------------------------------------------------------------------------------------------------------

            printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
            printf("movq -%d(%%rbp), %%rdi        #recupera %%rdi de -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
        }
        posicaoAtualPilha -= 8;
        return 1;
    }

    else if(r == 3)
    {

        posicaoAtualPilha += 16;

        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);

        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;

        while(tmp < 1)
        {
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha)
        {
            printf("subq $%d, %%rsp\n", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
            posicaoPilhaVariaveisLocaisRegistradores[5] = posicaoAtualPilha - 8;
            posicaoPilhaVariaveisLocaisRegistradores[6] = posicaoAtualPilha;
            printf("movq %%rdi, -%d(%%rbp)        #salva %%rdi em -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq %%rsi, -%d(%%rbp)        #salva %%rsi em -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);

            //------------------------------------------------PASSAGEM DE PAR?METROS-----------------------------------------------------------------------------------------
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1
            if(strncmp(param1,"vi",2) == 0)
            {
                sscanf(param1, "vi%d", &p1);
                printf("movl -%d(%%rbp), %%edi        #passa vari?vel local como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"va",2) == 0)
            {
                sscanf(param1, "va%d", &p1);
                printf("leaq -%d(%%rbp), %%rdi        #passa endere?o inicial de vari?vel local array como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"pi",2) == 0)
            {
                sscanf(param1, "pi%d", &p1);
                if(p1 == 1){
                    printf("movl %%edi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movl %%esi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movl %%edx, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"pa",2) == 0)
            {
                sscanf(param1, "pa%d", &p1);

                if(p1 == 1){
                    printf("movq %%rdi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movq %%rsi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movq %%rdx, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"ci",2) == 0)
            {
                sscanf(param1, "ci%d", &p1);
                printf("movl $%d, %%edi        #passa constante como primeiro par?metro\n\n", p1);

            }
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2

            if(strncmp(param2,"vi",2) == 0)
            {
                sscanf(param2, "vi%d", &p2);
                printf("movl -%d(%%rbp), %%esi        #passa vari?vel local como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"va",2) == 0)
            {
                sscanf(param2, "va%d", &p2);
                printf("leaq -%d(%%rbp), %%rsi        #passa endere?o inicial de vari?vel local array como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"pi",2) == 0)
            {
                sscanf(param2, "pi%d", &p2);
                if(p2 == 1){
                    printf("movl %%edi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movl %%esi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movl %%edx, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"pa",2) == 0)
            {
                sscanf(param2, "pa%d", &p2);

                if(p2 == 1){
                    printf("movq %%rdi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movq %%rsi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movq %%rdx, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"ci",2) == 0)
            {
                sscanf(param2, "ci%d", &p2);
                printf("movl $%d, %%esi        #passa constante como segundo par?metro\n\n", p2);

            }

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2
            //---------------------------------------------------------------------------------------------------------------------------------------------------------------

            printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
            printf("movq -%d(%%rbp), %%rdi        #recupera %%rdi de -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq -%d(%%rbp), %%rsi        #recupera %%rsi de -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);
            printf("addq $%d, %%rsp        #desaloca valor alocado para registradores ap?s recuper?-los\n\n", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
        }
        else
        {
            posicaoPilhaVariaveisLocaisRegistradores[5] = posicaoAtualPilha - 8;
            posicaoPilhaVariaveisLocaisRegistradores[6] = posicaoAtualPilha;
            printf("movq %%rdi, -%d(%%rbp)        #salva %%rdi em -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq %%rsi, -%d(%%rbp)        #salva %%rsi em -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);

            //------------------------------------------------PASSAGEM DE PAR?METROS-----------------------------------------------------------------------------------------
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1
            if(strncmp(param1,"vi",2) == 0)
            {
                sscanf(param1, "vi%d", &p1);
                printf("movl -%d(%%rbp), %%edi        #passa vari?vel local como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"va",2) == 0)
            {
                sscanf(param1, "va%d", &p1);
                printf("leaq -%d(%%rbp), %%rdi        #passa endere?o inicial de vari?vel local array como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"pi",2) == 0)
            {
                sscanf(param1, "pi%d", &p1);
                if(p1 == 1){
                    printf("movl %%edi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movl %%esi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movl %%edx, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"pa",2) == 0)
            {
                sscanf(param1, "pa%d", &p1);

                if(p1 == 1){
                    printf("movq %%rdi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movq %%rsi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movq %%rdx, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"ci",2) == 0)
            {
                sscanf(param1, "ci%d", &p1);
                printf("movl $%d, %%edi        #passa constante como primeiro par?metro\n\n", p1);

            }
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2

            if(strncmp(param2,"vi",2) == 0)
            {
                sscanf(param2, "vi%d", &p2);
                printf("movl -%d(%%rbp), %%esi        #passa vari?vel local como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"va",2) == 0)
            {
                sscanf(param2, "va%d", &p2);
                printf("leaq -%d(%%rbp), %%rsi        #passa endere?o inicial de vari?vel local array como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"pi",2) == 0)
            {
                sscanf(param2, "pi%d", &p2);
                if(p2 == 1){
                    printf("movl %%edi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movl %%esi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movl %%edx, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"pa",2) == 0)
            {
                sscanf(param2, "pa%d", &p2);

                if(p2 == 1){
                    printf("movq %%rdi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movq %%rsi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movq %%rdx, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"ci",2) == 0)
            {
                sscanf(param2, "ci%d", &p2);
                printf("movl $%d, %%esi        #passa constante como segundo par?metro\n\n", p2);

            }

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2
            //---------------------------------------------------------------------------------------------------------------------------------------------------------------

            printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
            printf("movq -%d(%%rbp), %%rdi        #recupera %%rdi de -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq -%d(%%rbp), %%rsi        #recupera %%rsi de -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);
        }
        posicaoAtualPilha -= 16;
        return 1;
    }

    else if(r == 4)
    {

        posicaoAtualPilha += 24;
        printf("Linha %d: %s\n\n", count + 1, line + 256 * count);

        tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;

        while(tmp < 1)
        {
            contadoraValorAlocarPilha++;
            tmp = (contadoraValorAlocarPilha * 16)/posicaoAtualPilha;
        }

        if(contadoraValorAlocarPilha * 16 > valorAlocadoPilha)
        {
            printf("subq $%d, %%rsp\n", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
            posicaoPilhaVariaveisLocaisRegistradores[5] = posicaoAtualPilha - 16;
            posicaoPilhaVariaveisLocaisRegistradores[6] = posicaoAtualPilha - 8;
            posicaoPilhaVariaveisLocaisRegistradores[7] = posicaoAtualPilha;
            printf("movq %%rdi, -%d(%%rbp)        #salva %%rdi em -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq %%rsi, -%d(%%rbp)        #salva %%rsi em -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);
            printf("movq %%rdx, -%d(%%rbp)        #salva %%rdx em -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[7], posicaoPilhaVariaveisLocaisRegistradores[7]);

            //------------------------------------------------PASSAGEM DE PAR?METROS-----------------------------------------------------------------------------------------
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1

            if(strncmp(param1,"vi",2) == 0)
            {
                sscanf(param1, "vi%d", &p1);
                printf("movl -%d(%%rbp), %%edi        #passa vari?vel local como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"va",2) == 0)
            {
                sscanf(param1, "va%d", &p1);
                printf("leaq -%d(%%rbp), %%rdi        #passa endere?o inicial de vari?vel local array como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"pi",2) == 0)
            {
                sscanf(param1, "pi%d", &p1);
                if(p1 == 1){
                    printf("movl %%edi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movl %%esi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movl %%edx, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"pa",2) == 0)
            {
                sscanf(param1, "pa%d", &p1);

                if(p1 == 1){
                    printf("movq %%rdi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movq %%rsi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movq %%rdx, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"ci",2) == 0)
            {
                sscanf(param1, "ci%d", &p1);
                printf("movl $%d, %%edi        #passa constante como primeiro par?metro\n\n", p1);

            }

            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2

            if(strncmp(param2,"vi",2) == 0)
            {
                sscanf(param2, "vi%d", &p2);
                printf("movl -%d(%%rbp), %%esi        #passa vari?vel local como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"va",2) == 0)
            {
                sscanf(param2, "va%d", &p2);
                printf("leaq -%d(%%rbp), %%rsi        #passa endere?o inicial de vari?vel local array como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"pi",2) == 0)
            {
                sscanf(param2, "pi%d", &p2);
                if(p2 == 1){
                    printf("movl %%edi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movl %%esi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movl %%edx, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"pa",2) == 0)
            {
                sscanf(param2, "pa%d", &p2);

                if(p2 == 1){
                    printf("movq %%rdi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movq %%rsi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movq %%rdx, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"ci",2) == 0)
            {
                sscanf(param2, "ci%d", &p2);
                printf("movl $%d, %%esi        #passa constante como segundo par?metro\n\n", p2);

            }

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2

            //PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3

            if(strncmp(param3,"vi",2) == 0)
            {
                sscanf(param3, "vi%d", &p3);
                printf("movl -%d(%%rbp), %%edx        #passa vari?vel local como terceiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p3 - 1]);
            }
            else if(strncmp(param3,"va",2) == 0)
            {
                sscanf(param3, "va%d", &p3);
                printf("leaq -%d(%%rbp), %%rdx        #passa endere?o inicial de vari?vel local array como terceiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p3 - 1]);
            }
            else if(strncmp(param3,"pi",2) == 0)
            {
                sscanf(param3, "pi%d", &p3);
                if(p3 == 1){
                    printf("movl %%edi, %%edx        #passa par?metro %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 2){
                    printf("movl %%esi, %%edx        #passa par?metro %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 3){
                    printf("movl %%edx, %%edx        #passa par?metro %d atual como terceiro par?metro\n\n", p3);
                }
            }
            else if(strncmp(param3,"pa",2) == 0)
            {
                sscanf(param3, "pa%d", &p3);

                if(p3 == 1){
                    printf("movq %%rdi, %%rdx        #passa par?metro array %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 2){
                    printf("movq %%rsi, %%rdx        #passa par?metro array %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 3){
                    printf("movq %%rdx, %%rdx        #passa par?metro array %d atual como terceiro par?metro\n\n", p3);
                }
            }
            else if(strncmp(param3,"ci",2) == 0)
            {
                sscanf(param3, "ci%d", &p3);
                printf("movl $%d, %%edx        #passa constante como terceiro par?metro\n\n", p2);

            }

            //PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3
            //---------------------------------------------------------------------------------------------------------------------------------------------------------------

            printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
            printf("movq -%d(%%rbp), %%rdi        #recupera %%rdi de -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq -%d(%%rbp), %%rsi        #recupera %%rsi de -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);
            printf("movq -%d(%%rbp), %%rdx        #recupera %%rdx de -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[7], posicaoPilhaVariaveisLocaisRegistradores[7]);
            printf("addq $%d, %%rsp        #desaloca valor alocado para registradores ap?s recuper?-los\n\n", contadoraValorAlocarPilha * 16 - valorAlocadoPilha);
        }
        else
        {
            posicaoPilhaVariaveisLocaisRegistradores[5] = posicaoAtualPilha - 16;
            posicaoPilhaVariaveisLocaisRegistradores[6] = posicaoAtualPilha - 8;
            posicaoPilhaVariaveisLocaisRegistradores[7] = posicaoAtualPilha;
            printf("movq %%rdi, -%d(%%rbp)        #salva %%rdi em -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq %%rsi, -%d(%%rbp)        #salva %%rsi em -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);
            printf("movq %%rdx, -%d(%%rbp)        #salva %%rdx em -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[7], posicaoPilhaVariaveisLocaisRegistradores[7]);

            //------------------------------------------------PASSAGEM DE PAR?METROS-----------------------------------------------------------------------------------------
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1
            if(strncmp(param1,"vi",2) == 0)
            {
                sscanf(param1, "vi%d", &p1);
                printf("movl -%d(%%rbp), %%edi        #passa vari?vel local como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"va",2) == 0)
            {
                sscanf(param1, "va%d", &p1);
                printf("leaq -%d(%%rbp), %%rdi        #passa endere?o inicial de vari?vel local array como primeiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p1 - 1]);
            }
            else if(strncmp(param1,"pi",2) == 0)
            {
                sscanf(param1, "pi%d", &p1);
                if(p1 == 1){
                    printf("movl %%edi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movl %%esi, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movl %%edx, %%edi        #passa par?metro %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"pa",2) == 0)
            {
                sscanf(param1, "pa%d", &p1);

                if(p1 == 1){
                    printf("movq %%rdi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 2){
                    printf("movq %%rsi, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
                else if(p1 == 3){
                    printf("movq %%rdx, %%rdi        #passa par?metro array %d atual como primeiro par?metro\n\n", p1);
                }
            }
            else if(strncmp(param1,"ci",2) == 0)
            {
                sscanf(param1, "ci%d", &p1);
                printf("movl $%d, %%edi        #passa constante como primeiro par?metro\n\n", p1);

            }
            //PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1 PARAM 1

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2

            if(strncmp(param2,"vi",2) == 0)
            {
                sscanf(param2, "vi%d", &p2);
                printf("movl -%d(%%rbp), %%esi        #passa vari?vel local como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"va",2) == 0)
            {
                sscanf(param2, "va%d", &p2);
                printf("leaq -%d(%%rbp), %%rsi        #passa endere?o inicial de vari?vel local array como segundo par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p2 - 1]);
            }
            else if(strncmp(param2,"pi",2) == 0)
            {
                sscanf(param2, "pi%d", &p2);
                if(p2 == 1){
                    printf("movl %%edi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movl %%esi, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movl %%edx, %%esi        #passa par?metro %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"pa",2) == 0)
            {
                sscanf(param2, "pa%d", &p2);

                if(p2 == 1){
                    printf("movq %%rdi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 2){
                    printf("movq %%rsi, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
                else if(p2 == 3){
                    printf("movq %%rdx, %%rsi        #passa par?metro array %d atual como segundo par?metro\n\n", p2);
                }
            }
            else if(strncmp(param2,"ci",2) == 0)
            {
                sscanf(param2, "ci%d", &p2);
                printf("movl $%d, %%esi        #passa constante como segundo par?metro\n\n", p2);

            }

            //PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2 PARAM 2

            //PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3

            if(strncmp(param3,"vi",2) == 0)
            {
                sscanf(param3, "vi%d", &p3);
                printf("movl -%d(%%rbp), %%edx        #passa vari?vel local como terceiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p3 - 1]);
            }
            else if(strncmp(param3,"va",2) == 0)
            {
                sscanf(param3, "va%d", &p3);
                printf("leaq -%d(%%rbp), %%rdx        #passa endere?o inicial de vari?vel local array como terceiro par?metro\n\n", posicaoPilhaVariaveisLocaisRegistradores[p3 - 1]);
            }
            else if(strncmp(param3,"pi",2) == 0)
            {
                sscanf(param3, "pi%d", &p3);
                if(p3 == 1){
                    printf("movl %%edi, %%edx        #passa par?metro %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 2){
                    printf("movl %%esi, %%edx        #passa par?metro %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 3){
                    printf("movl %%edx, %%edx        #passa par?metro %d atual como terceiro par?metro\n\n", p3);
                }
            }
            else if(strncmp(param3,"pa",2) == 0)
            {
                sscanf(param3, "pa%d", &p3);

                if(p3 == 1){
                    printf("movq %%rdi, %%rdx        #passa par?metro array %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 2){
                    printf("movq %%rsi, %%rdx        #passa par?metro array %d atual como terceiro par?metro\n\n", p3);
                }
                else if(p3 == 3){
                    printf("movq %%rdx, %%rdx        #passa par?metro array %d atual como terceiro par?metro\n\n", p3);
                }
            }
            else if(strncmp(param3,"ci",2) == 0)
            {
                sscanf(param3, "ci%d", &p3);
                printf("movl $%d, %%edx        #passa constante como terceiro par?metro\n\n", p2);

            }

            //PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3 PARAM 3
            //---------------------------------------------------------------------------------------------------------------------------------------------------------------

            printf("call f%d        #chama a fun??o f%d\n\n", fn, fn);
            printf("movq -%d(%%rbp), %%rdi        #recupera %%rdi de -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[5], posicaoPilhaVariaveisLocaisRegistradores[5]);
            printf("movq -%d(%%rbp), %%rsi        #recupera %%rsi de -%d(%%rbp)\n", posicaoPilhaVariaveisLocaisRegistradores[6], posicaoPilhaVariaveisLocaisRegistradores[6]);
            printf("movq -%d(%%rbp), %%rdx        #recupera %%rdx de -%d(%%rbp)\n\n", posicaoPilhaVariaveisLocaisRegistradores[7], posicaoPilhaVariaveisLocaisRegistradores[7]);
        }

        posicaoAtualPilha -= 24;

        return 1;
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL,"Portuguese");
    char line[sizeMatrix][columns];
    int count = 0; //A LINHA ATUAL ? (count + 1)
    inicializaMatrizTraducao(line, sizeMatrix, columns);

    /*PRINTA ARQUIVO .blp
    for(int i = 0; i<sizeMatrix; i++){
        if(line[i][0]!='\0'){
            printf("%s\n",line[i]);
        }
    }*/

    //L? UMA LINHA POR V?Z
    while (count<100)
    {

        /*________________________________________VERIFICA SE ? DECLARA??O DE FUN??O________________________________________*/
        if(verificaDeclaracaoFunc(line,count) == 1)
        {
            posicaoAtualPilha = 0;
            valorAlocadoPilha = 0;

            for(int i = 0; i<5; i++)
            {
                posicaoPilhaVariaveisLocaisRegistradores[i] = 0;
            }

            count++;
            continue;
        }

        /*___________________________________________________________________________________________________________________________________________*/


        /*________________________________________VERIFICA SE ? DEFINI??O DE VARI?VEL________________________________________*/
        if(verificaDefVar(line, count) == 1)
        {
            count++;
            continue;
        }
        /*___________________________________________________________________________________________________________________________________________*/

        /*________________________________________VERIFICA SE ? CONDICIONAL________________________________________*/
        if(verificaCondicional(line, count) == 1)
        {
            count++;
            continue;
        }
        /*___________________________________________________________________________________________________________________________________________*/

        /*________________________________________VERIFICA SE ? RETORNO________________________________________*/
        if(verificaRetorno(line, count) == 1)
        {
            count++;
            continue;
        }
        /*___________________________________________________________________________________________________________________________________________*/

        /*________________________________________VERIFICA SE ? CHAMADA DE FUNCAO________________________________________*/
        if(verificaChamadaFunc(line, count) == 1)
        {
            count++;
            continue;
        }
        /*___________________________________________________________________________________________________________________________________________*/

        count++;
    }
    return 0;
}
