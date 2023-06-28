#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"
#include "heap.h"

typedef struct{
  char* nombre;
  int precioCompra;
  int precioVenta;
  int stockInicial;
  int cantVendida;
}tipoProducto;

typedef struct{
  int gananciaDia;
  int gastoDia;
}tipoDia;

int main()
{
  HashMap *mapaProducto = createMap((long)100);
  HashMap *mapaSemanal = createMap((long)100);
  List * listaDias = createList();
  char caracter[100], *nombre, *archivoCargado;
  int precioCompra, precioVenta, stockInicial, antVendida, opcion, contadorDia = 0;
  FILE *ArchivoPrueba = fopen("ArchivoPrueba.csv", "r");
  fgets(caracter, 99, ArchivoPrueba);
  while (fscanf(ArchivoPrueba, "%m[^,],%d,%d,%d\n", &nombre, &precioCompra, &precioVenta, &stockInicial) != EOF) {
    tipoProducto *producto = malloc(sizeof(tipoProducto));
    producto->nombre = strdup(nombre);
    producto->precioCompra = precioCompra;
    producto->precioVenta = precioVenta;
    producto->stockInicial = stockInicial;
    producto->cantVendida = 0;
    insertMap(mapaProducto, producto->nombre, producto);
    insertMap(mapaSemanal, producto->nombre, producto);
  }
    
  fclose(ArchivoPrueba);

}