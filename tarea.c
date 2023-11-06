#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIANGULOS 50
#define MAX_LADOS 3
#define LONG_MIN_LADO 3
#define LONG_MAX_LADO 20

struct Triangulo {
    char tipo[20];
    int lados[3];
};

void mostrar_menu() {
    printf("\nMenu de opciones:\n");
    printf("a. Ingresar el tipo de triángulo(escaleno, equilátero, isosceles)\n");
    printf("b. Generar los lados del último triángulo\n");
    printf("c. Generar los lados de un triángulo específico\n");
    printf("d. Volver a generar los lados de todos los triángulos\n");
    printf("e. Dibujar un triángulo\n");
    printf("f. Dibujar todos los triángulos de un tipo\n");
    printf("g. Listar todos los triángulos\n");
    printf("h. Terminar\n");
}

int tipo_triangulo_valido(const char *tipo) {
    char tipo_lower[20];
    strcpy(tipo_lower, tipo);
    for (int i = 0; tipo_lower[i]; i++) {
        tipo_lower[i] = tolower(tipo_lower[i]);
    }

    return (strcmp(tipo_lower, "escaleno") == 0 ||
            strcmp(tipo_lower, "equilatero") == 0 ||
            strcmp(tipo_lower, "isosceles") == 0);
}

int es_triangulo_valido(int lado1, int lado2, int lado3) {
    return (lado1 + lado2 > lado3) && (lado1 + lado3 > lado2) && (lado2 + lado3 > lado1);
}

int agregar_triangulo(struct Triangulo triangulos[], int *cantidad_triangulos) {
    if (*cantidad_triangulos < MAX_TRIANGULOS) {
        char tipo[20];
        printf("Ingrese el tipo de triángulo: ");
        scanf("%s", tipo);

        if (tipo_triangulo_valido(tipo)) {
            strcpy(triangulos[*cantidad_triangulos].tipo, tipo);
            (*cantidad_triangulos)++;
            printf("Triángulo '%s' agregado.\n", tipo);
            return 1;
        } else {
            printf("Tipo de triángulo no válido. Tipos válidos son: escaleno, equilatero, isosceles.\n");
        }
    } else {
        printf("No se pueden agregar más triángulos. Se ha alcanzado el límite.\n");
    }
    return 0;
}

void generar_lados(struct Triangulo triangulos[], int lados_generados[], int cantidad_triangulos, int indice_triangulo) {
    if (indice_triangulo >= 0 && indice_triangulo < cantidad_triangulos) {
        int lado1, lado2, lado3;

        if (strcmp(triangulos[indice_triangulo].tipo, "equilatero") == 0) {
            lado1 = lado2 = lado3 = rand() % (LONG_MAX_LADO - LONG_MIN_LADO + 1) + LONG_MIN_LADO;
        } else if (strcmp(triangulos[indice_triangulo].tipo, "isosceles") == 0) {
            lado1 = lado2 = rand() % (LONG_MAX_LADO - LONG_MIN_LADO + 1) + LONG_MIN_LADO;
            lado3 = rand() % (LONG_MAX_LADO - LONG_MIN_LADO + 1) + LONG_MIN_LADO;
        } else {
            lado1 = rand() % (LONG_MAX_LADO - LONG_MIN_LADO + 1) + LONG_MIN_LADO;
            do {
                lado2 = rand() % (LONG_MAX_LADO - LONG_MIN_LADO + 1) + LONG_MIN_LADO;
            } while (lado2 == lado1);
            do {
                lado3 = rand() % (LONG_MAX_LADO - LONG_MIN_LADO + 1) + LONG_MIN_LADO;
            } while (lado3 == lado1 || lado3 == lado2);
        }

        triangulos[indice_triangulo].lados[0] = lado1;
        triangulos[indice_triangulo].lados[1] = lado2;
        triangulos[indice_triangulo].lados[2] = lado3;
        lados_generados[indice_triangulo] = 1;

        printf("Lados del triángulo '%s' generados: %d, %d, %d\n", triangulos[indice_triangulo].tipo, lado1, lado2, lado3);
    } else {
        printf("Número de triángulo no válido.\n");
    }
}

void generar_lados_ultimo(struct Triangulo triangulos[], int lados_generados[], int *cantidad_triangulos) {
    generar_lados(triangulos, lados_generados, *cantidad_triangulos, *cantidad_triangulos - 1);
}

void generar_lados_especifico(struct Triangulo triangulos[], int lados_generados[], int cantidad_triangulos) {
    int indice_triangulo;
    printf("Elija el número de triángulo: ");
    scanf("%d", &indice_triangulo);
    generar_lados(triangulos, lados_generados, cantidad_triangulos, indice_triangulo - 1);
}

void generar_lados_todos(struct Triangulo triangulos[], int lados_generados[], int cantidad_triangulos) {
    for (int i = 0; i < cantidad_triangulos; i++) {
        lados_generados[i] = 0;
        generar_lados(triangulos, lados_generados, cantidad_triangulos, i);
    }
}

void dibujar_triangulo(const struct Triangulo triangulos[], int cantidad_triangulos, int indice_triangulo) {
    if (indice_triangulo >= 0 && indice_triangulo < cantidad_triangulos) {
        printf("Dibujando triángulo '%s':\n", triangulos[indice_triangulo].tipo);
        int lado1 = triangulos[indice_triangulo].lados[0];
        int lado2 = triangulos[indice_triangulo].lados[1];
        int lado3 = triangulos[indice_triangulo].lados[2];

        for (int i = 0; i < lado1; i++) {
            for (int j = 0; j <= i; j++) {
                printf("* ");
            }
            printf("\n");
        }

        for (int i = 0; i < lado2; i++) {
            for (int j = 0; j <= i; j++) {
                printf("* ");
            }
            printf("\n");
        }

        for (int i = 0; i < lado3; i++) {
            for (int j = 0; j <= i; j++) {
                printf("* ");
            }
            printf("\n");
        }
    } else {
        printf("Número de triángulo no válido.\n");
    }
}

void dibujar_todos_triangulos_tipo(const struct Triangulo triangulos[], int lados_generados[], int cantidad_triangulos) {
    char tipo[20];
    printf("Ingrese el tipo de triángulo: ");
    scanf("%s", tipo);

    printf("Dibujando todos los triángulos de tipo '%s':\n", tipo);
    for (int i = 0; i < cantidad_triangulos; i++) {
        if (strcasecmp(triangulos[i].tipo, tipo) == 0) {
            if (lados_generados[i]) {
                dibujar_triangulo(triangulos, cantidad_triangulos, i);
            } else {
                printf("Triángulo '%s' no generado.\n", triangulos[i].tipo);
            }
        }
    }
}

void listar_todos_triangulos(const struct Triangulo triangulos[], int lados_generados[], int cantidad_triangulos) {
    printf("Listado de todos los triángulos:\n");
    printf("%-10s %-20s %-10s %-10s %-10s\n", "Número", "Tipo", "Lado 1", "Lado 2", "Lado 3");
    for (int i = 0; i < cantidad_triangulos; i++) {
        printf("%-10d %-20s %-10d %-10d %-10d\n", i + 1, triangulos[i].tipo, triangulos[i].lados[0], triangulos[i].lados[1], triangulos[i].lados[2]);
    }
}

int main() {
    srand(time(0));

    struct Triangulo triangulos[MAX_TRIANGULOS];
    int lados_generados[MAX_TRIANGULOS] = {0};
    int cantidad_triangulos = 0;

    while (1) {
        mostrar_menu();
        char opcion;
        printf("Elija una opción (a-h): ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'a':
                agregar_triangulo(triangulos, &cantidad_triangulos);
                break;
            case 'b':
                generar_lados_ultimo(triangulos, lados_generados, &cantidad_triangulos);
                break;
            case 'c':
                generar_lados_especifico(triangulos, lados_generados, cantidad_triangulos);
                break;
            case 'd':
                generar_lados_todos(triangulos, lados_generados, cantidad_triangulos);
                break;
            case 'e':
                int indice_triangulo;
                printf("Elija el número de triángulo: ");
                scanf("%d", &indice_triangulo);
                dibujar_triangulo(triangulos, cantidad_triangulos, indice_triangulo - 1);
                break;
            case 'f':
                dibujar_todos_triangulos_tipo(triangulos, lados_generados, cantidad_triangulos);
                break;
            case 'g':
                listar_todos_triangulos(triangulos, lados_generados, cantidad_triangulos);
                break;
            case 'h':
                printf("Programa terminado.\n");
                exit(0);
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }

    return 0;
}

