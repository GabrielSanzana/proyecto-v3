#include "hashmap.h"
#include "heap.h"
#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nombre;
  int precioCompra;
  int precioVenta;
  int stockInicial;
  int cantVendida;
} tipoProducto;

typedef struct {
  int gananciaDia;
  int gastoDia;
} tipoDia;

void registro_de_productos(HashMap *mapaProducto, HashMap *mapaSemanal) {
  char *nombre;
  int precioCompra, precioVenta, stockInicial, cantVendida;
  printf("Ingrese el nombre del producto, precio de compra, precio de venta y "
         "stock. Separado por comas\n");
  scanf("%m[^,],%d,%d,%d", &nombre, &precioCompra, &precioVenta, &stockInicial);
  tipoProducto *productoAux = malloc(sizeof(tipoProducto));
  productoAux->nombre = strdup(nombre);
  productoAux->precioCompra = precioCompra;
  productoAux->precioVenta = precioVenta;
  productoAux->stockInicial = stockInicial;
  productoAux->cantVendida = 0;

  tipoProducto *copiaProductoAux = malloc(sizeof(tipoProducto));
  copiaProductoAux->nombre = strdup(nombre);
  copiaProductoAux->precioCompra = precioCompra;
  copiaProductoAux->precioVenta = precioVenta;
  copiaProductoAux->stockInicial = stockInicial;
  copiaProductoAux->cantVendida = 0;

  insertMap(mapaProducto, productoAux->nombre, productoAux);
  insertMap(mapaSemanal, copiaProductoAux->nombre, copiaProductoAux);
}

void Control_de_stock(HashMap *mapaProducto, HashMap *mapaSemanal) {
  // pensar en poner variables que sumen la ganancia e inversion total
  char *nombre;
  int cantVendida;
  printf("Ingrese el nombre del producto y las unidades que vendio. Separado "
         "por una coma\n");
  scanf("%m[^,],%d", &nombre, &cantVendida);
  Pair *buscado = searchMap(mapaProducto, nombre);
  if (buscado == NULL) {
    printf("El producto no existe.");
    return;
  }
  tipoProducto *productoAux = buscado->value;
  tipoProducto *productoEnSemanal = searchMap(mapaSemanal, nombre)->value;
  if (productoAux->cantVendida + cantVendida > productoAux->stockInicial ||
      cantVendida <= 0) {
    puts("No se puede.");
    return;
  }
  printf("%d\n", productoAux->cantVendida);
  productoAux->cantVendida = productoAux->cantVendida + cantVendida;
  printf("%d\n", productoAux->cantVendida);

  productoEnSemanal->cantVendida = productoEnSemanal->cantVendida + cantVendida;
  printf("%d\n", productoEnSemanal->cantVendida);
}

void modificar_datos_de_un_producto(HashMap *mapaProducto,
                                    HashMap *mapaSemanal) {
  int opcion, nuevoValor;
  char nombreProducto[100];

  printf("Ingrese el nombre del producto a modificar\n");
  scanf("%s", nombreProducto);
  Pair *buscado = searchMap(mapaProducto, nombreProducto);
  if (buscado == NULL) {
    printf("El producto no existe");
    return;
  }
  tipoProducto *producto = buscado->value;
  tipoProducto *productoSemana = searchMap(mapaSemanal, nombreProducto)->value;
  printf("Seleccione que quiere cambia\n");
  printf("1. Precio de compra\n");
  printf("2. Precio de venta\n");
  printf("3. Stock inicial\n");
  scanf("%d", &opcion);
  getchar();
  switch (opcion) {
  case 1:
    printf("Ingrese el nuevo precio de compra\n");
    scanf("%d", &nuevoValor);
    getchar();
    producto->precioCompra = nuevoValor;
    productoSemana->precioCompra = nuevoValor;
    break;
  case 2:
    printf("Ingrese el nuevo precio de venta\n");
    scanf("%d", &nuevoValor);
    producto->precioVenta = nuevoValor;
    productoSemana->precioVenta = nuevoValor;

    break;
  case 3:
    printf("Ingrese el nuevo stock inicial\n");
    scanf("%d", &nuevoValor);
    producto->stockInicial = nuevoValor;
    productoSemana->stockInicial = nuevoValor;
  default:
    printf("Opcion invalida\n");
    return;
  }
}

void Cargar_csv_de_stock(HashMap *mapaProducto, HashMap *mapaSemanal,
                         char *nombre_archivo) {
  char caracter[100], *nombre;
  FILE *archivoCsv = fopen(nombre_archivo, "r");
  int precioCompra, precioVenta, stockInicial, cantVendida, opcion;

  if (archivoCsv == NULL) {
    printf("\n—————————————————————————————————————————————————————————————————"
           "—————————\n");
    printf(
        "El archivo %s no existe en el directorio actual o esta mal escrito.\n",
        nombre_archivo);
    printf("———————————————————————————————————————————————————————————————————"
           "———————\n\n");
    return;
  }

  fgets(caracter, 99, archivoCsv);

  while (fscanf(archivoCsv, "%m[^,],%d,%d,%d\n", &nombre, &precioCompra,
                &precioVenta, &stockInicial) != EOF) {
    tipoProducto *producto = malloc(sizeof(tipoProducto));
    producto->nombre = strdup(nombre);
    producto->precioCompra = precioCompra;
    producto->precioVenta = precioVenta;
    producto->stockInicial = stockInicial;
    producto->cantVendida = 0;
    insertMap(mapaProducto, producto->nombre, producto);
    if (searchMap(mapaSemanal, producto->nombre) == NULL)
      insertMap(mapaSemanal, producto->nombre, producto);
    else {
      tipoProducto *productoExistente =
          searchMap(mapaSemanal, producto->nombre)->value;
      productoExistente->stockInicial += stockInicial;
    }
  }
  printf("\nArchivo importado.\n");
  fclose(archivoCsv);
}

void mostrarMapa(HashMap *mapaProducto) {
  printf("Productos almacenados:\n");

  Pair *pair = firstMap(mapaProducto);
  while (pair != NULL) {
    tipoProducto *producto = (tipoProducto *)pair->value;
    printf("Nombre: %s\n", producto->nombre);
    printf("Precio de compra: %d\n", producto->precioCompra);
    printf("Precio de venta: %d\n", producto->precioVenta);
    printf("Stock inicial: %d\n", producto->stockInicial);
    printf("Cantidad vendida: %d\n", producto->cantVendida);
    printf("------------------------\n");
    pair = nextMap(mapaProducto);
  }
}

void Exportar_mapa(char *nombre_archivo, Heap *monticuloMaximo,
                   Heap *monticuloMinimo) {
  int contador = 1;
  FILE *archivo = fopen(nombre_archivo, "w");
  fprintf(archivo,
          "Producto,Precio de Compra,Precio de Venta,Stock,CantVendida\n");

  tipoProducto *productoMax = heap_top(monticuloMaximo);
  tipoProducto *productoMin = heap_top(monticuloMinimo);
  while (contador <= 5) {
    fprintf(archivo, "%s,%d,%d,%d,%d", productoMax->nombre,
            productoMax->precioCompra, productoMax->precioVenta,
            productoMax->stockInicial, productoMax->cantVendida);
    fprintf(archivo, "\n");
    heap_pop(monticuloMaximo);
    productoMax = heap_top(monticuloMaximo);
    contador++;
  }
  while (contador <= 5) {
    fprintf(archivo, "%s,%d,%d,%d,%d", productoMin->nombre,
            productoMin->precioCompra, productoMin->precioVenta,
            productoMin->stockInicial, productoMin->cantVendida);
    fprintf(archivo, "\n");
    heap_pop(monticuloMinimo);
    productoMin = heap_top(monticuloMinimo);
    contador++;
  }

  printf("\nArchivo exportado.\n");
  printf("————————————————————————————————————————————————————————————\n\n");
  fclose(archivo);
}

void Exportar_mapa_semanal(char *nombre_archivo, Heap *monticuloMaximo,
                           Heap *monticuloMinimo) {
  int contador = 1;
  FILE *archivo = fopen(nombre_archivo, "w");
  fprintf(archivo,
          "Producto,Precio de Compra,Precio de Venta,Stock,CantVendida\n");

  tipoProducto *productoMax = heap_top(monticuloMaximo);
  tipoProducto *productoMin = heap_top(monticuloMinimo);

  while (contador <= 5) {
    fprintf(archivo, "%s,%d,%d,%d,%d", productoMax->nombre,
            productoMax->precioCompra, productoMax->precioVenta,
            productoMax->stockInicial, productoMax->cantVendida);

    fprintf(archivo, "\n");
    productoMax->stockInicial =
        productoMax->stockInicial - productoMax->cantVendida;
    productoMax->cantVendida = 0;
    heap_pop(monticuloMaximo);
    productoMax = heap_top(monticuloMaximo);
    contador++;
  }

  printf("\nArchivo exportado.\n");
  printf("————————————————————————————————————————————————————————————\n\n");
  fclose(archivo);
}

void finalizarDia(HashMap *mapaProducto, HashMap *mapaSemanal, List *listaDia,
                  int *contadorDia) {
  Heap *monticuloMaximo = createHeap(), *monticuloMinimo = createHeap();
  if (*contadorDia != 7) {
    Pair *aux = firstMap(mapaProducto);
    while (aux != NULL) {
      tipoProducto *producto = (tipoProducto *)aux->value;
      heap_pushMax(monticuloMaximo, producto, producto->cantVendida);
      tipoProducto *aux1 = heap_top(monticuloMaximo);

      printf("MAX %s %d\n", aux1->nombre, aux1->cantVendida);
      heap_pushMin(monticuloMinimo, producto, producto->cantVendida);
      tipoProducto *aux2 = heap_top(monticuloMinimo);
      printf("MIN %s %d\n", aux2->nombre, aux2->cantVendida);
      aux = nextMap(mapaProducto);
    }
    char *nombre_archivo = "csvDiario.csv";

    Exportar_mapa(nombre_archivo, monticuloMaximo, monticuloMinimo);
    free(monticuloMaximo);
    free(monticuloMinimo);
    // system("pythonDiario.py");
  } else {
    Pair *aux = firstMap(mapaSemanal);
    char *nombre_archivo;
    while (aux != NULL) {
      tipoProducto *producto = (tipoProducto *)aux->value;
      heap_pushMax(monticuloMaximo, producto, producto->cantVendida);
      tipoProducto *aux1 = heap_top(monticuloMaximo);
      tipoProducto *aux2 = heap_top(monticuloMinimo);
      printf("MAX %s %d\n", aux1->nombre, aux1->cantVendida);
      heap_pushMin(monticuloMinimo, producto, producto->cantVendida);
      printf("MIN %s %d\n", aux2->nombre, aux2->cantVendida);
      aux = nextMap(mapaSemanal);
    }
    printf("¿Como quiere llamar el archivo de esta semana?\n");
    scanf("%m[^\n]", &nombre_archivo);
    getchar();
    Exportar_mapa_semanal(nombre_archivo, monticuloMaximo, monticuloMinimo);
    exit(EXIT_SUCCESS);
  }
}

int main() {
  HashMap *mapaProducto = createMap((long)100);
  HashMap *mapaSemanal = createMap((long)100);
  List *listaDias = createList();
  char caracter[100], *nombre, *archivoCargado;
  int precioCompra, precioVenta, stockInicial, opcion, contadorDia = 1;
  FILE *ArchivoPrueba = fopen("ArchivoPrueba.csv", "r");
  fgets(caracter, 99, ArchivoPrueba);
  while (fscanf(ArchivoPrueba, "%m[^,],%d,%d,%d\n", &nombre, &precioCompra,
                &precioVenta, &stockInicial) != EOF) {
    tipoProducto *producto = malloc(sizeof(tipoProducto));
    producto->nombre = strdup(nombre);
    producto->precioCompra = precioCompra;
    producto->precioVenta = precioVenta;
    producto->stockInicial = stockInicial;
    producto->cantVendida = 0;
    insertMap(mapaProducto, producto->nombre, producto);
    tipoProducto *copiaProductoAux = malloc(sizeof(tipoProducto));
    copiaProductoAux->nombre = strdup(nombre);
    copiaProductoAux->precioCompra = precioCompra;
    copiaProductoAux->precioVenta = precioVenta;
    copiaProductoAux->stockInicial = stockInicial;
    copiaProductoAux->cantVendida = 0;

    insertMap(mapaProducto, producto->nombre, producto);
    insertMap(mapaSemanal, producto->nombre, copiaProductoAux);
  }

  fclose(ArchivoPrueba);

  while (true) {
    printf("\n--- Menú Principal ---\n");
    printf("1. Registro de productos\n");
    printf("2. Control de stock\n");
    printf("3. Modificar datos de un producto\n");
    printf("4. Comparar y graficar dos informes semanales\n");
    printf("5. Cargar csv de stock\n");
    printf("6. Finalizar el día, creación de gráfico e informe\n");
    printf("Seleccione una opción: \n");
    scanf("%d", &opcion);
    getchar();
    switch (opcion) {
    case 1:
      registro_de_productos(mapaProducto, mapaSemanal);
      break;
    case 2:
      Control_de_stock(mapaProducto, mapaSemanal);
      break;
    case 3:
      modificar_datos_de_un_producto(mapaProducto, mapaSemanal);
      break;
    case 4:
      mostrarMapa(mapaProducto);
      break;
    case 5:
      printf(
          "\n————————————————————————————————————————————————————————————\n");
      printf("Ingrese el nombre del archivo, introduzca el formato (.csv)\n");
      scanf("%m[^\n]", &archivoCargado);
      getchar();
      if (strstr(archivoCargado, ".csv") == 0) {
        printf("\nEl formato del archivo '%s' es incorrecto.\n",
               archivoCargado);
        printf(
            "————————————————————————————————————————————————————————————\n\n");
        break;
      }
      Cargar_csv_de_stock(mapaProducto, mapaSemanal, archivoCargado);
      printf(
          "————————————————————————————————————————————————————————————\n\n");
      break;
    case 6:
      finalizarDia(mapaProducto, mapaSemanal, listaDias, &contadorDia);
      contadorDia++;
      break;
    default:
      break;
    }
  }
}