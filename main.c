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
  }
  
  fclose(ArchivoPrueba);

  while(true)
  {
  printf("\n--- Menú Principal ---\n");
  printf("1. Registro de productos\n");
  printf("2. Control de stock\n");
  printf("3. Modificar datos de un producto\n");
  printf("4. Comparar y graficar dos informes semanales\n");
  printf("5. Cargar csv de stock\n");
  printf("6. Finalizar el día, creación de gráfico e informe\n");
  printf("Seleccione una opción: \n");
  scanf("%d",&opcion);
  getchar();
  switch (opcion) 
    {
      case 1:
        registro_de_productos(mapaProducto,mapaSemanal);
        break;
      case 2:
        Control_de_stock(mapaProducto,mapaSemanal);
        break;
      case 3:
        modificar_datos_de_un_producto(mapaProducto,mapaSemanal);
        break;
      case 4: 
        mostrarMapa(mapaProducto);
        break;
      case 5:
        printf("\n————————————————————————————————————————————————————————————\n");
        printf("Ingrese el nombre del archivo, introduzca el formato (.csv)\n");
        scanf("%m[^\n]",&archivoCargado);
        getchar();
        if (strstr(archivoCargado,".csv")==0)
        {
          printf("\nEl formato del archivo '%s' es incorrecto.\n", archivoCargado);
              printf("————————————————————————————————————————————————————————————\n\n");
          break;
        }
        Cargar_csv_de_stock(mapaProducto,mapaSemanal, archivoCargado);
      printf("————————————————————————————————————————————————————————————\n\n");
        break;
      case 6:
        finalizarDia(mapaProducto,mapaSemanal,listaDias);
        contadorDia++;
        break;
      default:
        break;
    }
}