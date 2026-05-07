#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_alfabet 256

int max(int a,int b){return (a > b) ? a : b;}

void rezolvare_1(){
    int tablou[] = {2,5,8,12,16,23,38,56,72,91};
    int n = sizeof(tablou) / sizeof(tablou[0]);
    int key = 23;
    int st =0 , dr = n-1, poazitie = -1;
    while (st <= dr)
    {
        int mij = st + (dr - st) / 2;
        if (tablou[mij] == key)
        {
            poazitie = mij;
            break; 
        }
        else if (tablou[mij] < key)
            st = mij + 1;
        else
            dr = mij - 1;
        
    }
    if(poazitie != -1)
        printf("Elementul %d se afla pe pozitia %d\n", key, poazitie);
    else
        printf("Elementul %d nu a fost gasit in tablou\n", key);
    
    
}
void preprocesare_bad_char(char *str, int dimensiune, int badchar[max_alfabet]){
   for (int i = 0; i < max_alfabet; i++) badchar[i] = -1;
 
    for (int i = 0; i < dimensiune; i++) badchar[(int)str[i]] = i;
}

void boyer_moore(char *text, char *model) {
    int m = strlen(model);
    int n = strlen(text);
    int badchar[max_alfabet];

    preprocesare_bad_char(model, m, badchar);

    int s = 0; // s este deplasarea modelului fata de text
    int pas = 1;

    printf("--- Exercitiul 4: Simulare Boyer-Moore ---\n");
    while (s <= (n - m)) {
        int j = m - 1;

        // Comparam modelul de la dreapta la stanga
        while (j >= 0 && model[j] == text[s + j]) j--;

        if (j < 0) {
            printf("Pas %d: Model gasit la index %d\n", pas++, s);
            s += (s + m < n) ? m - badchar[(int)text[s + m]] : 1;
        } else {
            // Saltul se face pe baza caracterului gresit (Bad Character Heuristic)
            printf("Pas %d: Nepotrivire la index %d (text '%c' != model '%c'). Salt...\n", 
                    pas++, s + j, text[s + j], model[j]);
            s += max(1, j - badchar[(int)text[s + j]]);
        }
    }
    printf("\n");
}
void cautare_directa(char *text, char *model) {
    int n = strlen(text);
    int m = strlen(model);
    int pas = 1;

    printf("--- Exercitiul 5: Cautare Directa (Pas cu Pas) ---\n");
    for (int i = 0; i <= n - m; i++) {
        int j;
        printf("Pas %d: Verificam pozitia %d: ", pas++, i);
        
        for (j = 0; j < m; j++) {
            if (text[i + j] != model[j]) break;
        }

        if (j == m) printf("-> MATCH gasit!\n");
        else printf("-> Nepotrivire la caracterul %d\n", j);
    }
}

int main() {
    // Exercitiul 1
    rezolvare_1();

    // Exercitiul 2 & 3 sunt teoretice (incluse in explicatii)

    // Exercitiul 4
    char sir4[] = "abcxabcdabxabcdabcdabcy";
    char model4[] = "abcdabcy";
    boyer_moore(sir4, model4);

    // Exercitiul 5
    char s5[100], p5[100];
    printf("--- Exercitiul 5: Introducere date ---\n");
    printf("Introduceti sirul de caractere (s): ");
    scanf("%s", s5);
    printf("Introduceti modelul (p): ");
    scanf("%s", p5);
    cautare_directa(s5, p5);

    return 0;
}