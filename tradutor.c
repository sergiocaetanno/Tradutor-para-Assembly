#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define columns 256
#define sizeMatrix 100

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

int verificaDeclaracaoFunc(char *line, int count)
{

    int r, p1, p2, p3, fn;
    int countBackup;

    r = sscanf((line + count * 256) ,"function f%d pi%d pi%d pi%d", &fn, &p1, &p2, &p3);
    if(r == 4)
    {
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
        printf("Linha %d: %s\n", count + 1, line);
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
}




int main()
{
    setlocale(LC_ALL,"Portuguese");
    char line[sizeMatrix][columns];
    int count = 0; //A LINHA ATUAL É (count + 1)
    int retorno;

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
        retorno = verificaDeclaracaoFunc(line ,count);
        if(retorno == 1)
        {
            count++;
            continue;
        }

        /*___________________________________________________________________________________________________________________________________________*/


        /*________________________________________VERIFICA SE É DEFINIÇÃO DE VARIÁVEL________________________________________
        retorno = verificaDefVar();
        if(retorno == 1)
        {
            count++;
            continue;
        }

        ___________________________________________________________________________________________________________________________________________*/

        count++;
    }
    return 0;
}
