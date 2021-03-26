#include <stdio.h>
#include <ctype.h>
#define NOTLINE 16
#define EXPLINE 131
void LeerCad(char cad[], int);
void expand(char s1[], char s2[]);

int main(void) 
{
	char notation[NOTLINE], expnotation[EXPLINE];
	printf("El siguiente programa expande notaciones abreviadas como a-d-v en abcde...v.\n");
	printf("El programa solicita al usuario que ingrese la notacion abreviada para generar la expansion y mostrarla al usuario.\n");
	printf("Solamente se permite expandir notaciones abreviadas de letras y digitos. En caso de ingresar una notacion abreviada\n");
	printf("de letras, la notacion no puede contener una letra mayuscula con una letra minuscula, como: A - k.\n\n");
	printf("Ingresa la notacion abreviada:");
	LeerCad(notation, NOTLINE);
	expand(notation, expnotation);
	if (notation[0]) {
		printf("\nLa notacion abreviada que recibe el programa es:\n%s\n", notation);
		printf("La notacion expandida es:\n%s", expnotation);
	}
	else
		printf("\nNo se ingreso la notacion abreviada.\n");
	return 0;
}

/* LeerCad: Lee la linea ingresada por el usuario. msize indica la cantidad de caracteres almacenados en cad[] */
void LeerCad(char cad[], int msize)
{
	int c, i = 0;
	
	while ((c = getchar()) != '\n' && c != EOF) 
		if (i < msize - 1 && c != ' ' && c != '\t') 	/* Se excluyen los espacios en blanco obtenidos */
			cad[i++] = c;
	cad[i] = '\0';
}

#define OUT -1	  /* Constante que indica que existe una notacion abreviada que no es de letras y no es de digitos */

/* expand: Interpreta las notaciones abreviadas en s1[] y las expande en s2[]. */
/*         En caso de no existir notaciones abreviadas en s1[], se copian los caracteres en s2[] */
void expand(char s1[], char s2[]) 
{
	int i, j, k, l;
	for (i = j = 0; s1[i] != '\0'; i++) 
		if (isalnum(s1[i])) {	/* El programa busca por el inicio de una notacion abreviada de letras o de digitos */
			k = i + 1;
			if (s1[k] == '-') {		/* El programa busca que exista un guion despues de una letra o digito */
				k++;
				/* El programa verifica que la notacion abreviada cumpla con las caracteristicas deseadas */
				if ((islower(s1[i]) && islower(s1[k])) || (isupper(s1[i]) && isupper(s1[k]))) 
					l = s1[i];
				else if (isdigit(s1[i]) && isdigit(s1[k])) 
					l = s1[i];
				else {
					l = OUT;		/* La notacion abreviada no cumple con las caracteristicas deseadas */
					s2[j++] = s1[i];
				}
				if (l != OUT) {
					for ( ; l < s1[k]; l++) /* Se expande la notacion y se guarda en s2[] */
						s2[j++] = l;
					i++;
				}
			}
			else
				s2[j++] = s1[i];	/* No se encontro el guion, se procede a copiar el caracter directamente a s2[] */
		}
		else 
			s2[j++] = s1[i];      /* No se encontro un digito o letra, se procede a copiar el caracter directamente a s2[] */
	s2[j] = '\0';
}