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

void registro_de_productos(HashMap *mapaProducto, HashMap *mapaSemanal, tipoDia *dia) {
  char *nombre;
  int precioCompra, precioVenta, stockInicial, cantVendida;
  
  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("\n——————————————————————————————-————————————————————————————————————————————————————————\n");
  
  // Mostrar mensaje para que el usuario ingrese los datos del producto
  printf("Ingrese el nombre del producto, precio de compra, precio de venta y stock. Separado por comas\n");
  
  // Leer los valores ingresados por el usuario
  scanf("%m[^,],%d,%d,%d", &nombre, &precioCompra, &precioVenta, &stockInicial);
  
  // Crear un nuevo objeto de tipoProducto utilizando memoria dinámica (malloc)
  tipoProducto *productoAux = malloc(sizeof(tipoProducto));
  
  // Asignar los valores ingresados por el usuario a las variables del objeto productoAux
  productoAux->nombre = strdup(nombre);
  productoAux->precioCompra = precioCompra;
  productoAux->precioVenta = precioVenta;
  productoAux->stockInicial = stockInicial;
  productoAux->cantVendida = 0;
  
  // Actualizar el gasto del día en la estructura tipoDia
  dia->gastoDia += stockInicial * precioCompra;
  
  // Crear una copia del objeto productoAux utilizando memoria dinámica (malloc)
  tipoProducto *copiaProductoAux = malloc(sizeof(tipoProducto));
  
  // Asignar los valores del objeto productoAux a la copiaProductoAux
  copiaProductoAux->nombre = strdup(nombre);
  copiaProductoAux->precioCompra = precioCompra;
  copiaProductoAux->precioVenta = precioVenta;
  copiaProductoAux->stockInicial = stockInicial;
  copiaProductoAux->cantVendida = 0;
  
  // Insertar el objeto productoAux en el HashMap mapaProducto
  insertMap(mapaProducto, productoAux->nombre, productoAux);
  
  // Insertar la copiaProductoAux en el HashMap mapaSemanal
  insertMap(mapaSemanal, copiaProductoAux->nombre, copiaProductoAux);

  // Imprimir mensaje de éxito
  printf("\nEl producto '%s' ha sido agregado correctamente.\n", productoAux->nombre);
  
  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
}

void Control_de_stock(HashMap *mapaProducto, HashMap *mapaSemanal, tipoDia *dia) {
  // Declarar variables
  char *nombre;
  int cantVendida;
  
  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("\n——————————————————————————————-————————————————————————————————————————————————————————\n");
  
  // Solicitar al usuario el nombre del producto y la cantidad vendida
  printf("Ingrese el nombre del producto y las unidades que vendió. Separado por una coma\n");
  
  // Leer los valores ingresados por el usuario
  scanf("%m[^,],%d", &nombre, &cantVendida);
  
  // Buscar el producto en el mapa mapaProducto
  Pair *buscado = searchMap(mapaProducto, nombre);
  
  // Verificar si el producto existe en el mapa
  if (buscado == NULL) {
    printf("\nEl producto no existe.\n");
    // Imprimir línea separadora para mejorar la legibilidad en la salida
    printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
    return;
  }
  
  // Obtener el objeto tipoProducto del mapa
  tipoProducto *productoAux = buscado->value;
  
  // Obtener el objeto tipoProducto del mapa mapaSemanal
  tipoProducto *productoEnSemanal = searchMap(mapaSemanal, nombre)->value;
  
  // Verificar si la cantidad vendida supera el stock disponible o es menor o igual a cero
  if (productoAux->cantVendida + cantVendida > productoAux->stockInicial || cantVendida <= 0) {
    puts("\nNo se puede realizar la venta.");
    // Imprimir línea separadora para mejorar la legibilidad en la salida
    printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
    return;
  }
  
  // Actualizar la cantidad vendida del producto
  productoAux->cantVendida += cantVendida;
  
  // Calcular la ganancia del día
  dia->gananciaDia += cantVendida * (productoAux->precioVenta - productoAux->precioCompra);
  
  // Actualizar la cantidad vendida del producto en el mapa mapaSemanal
  productoEnSemanal->cantVendida += cantVendida;
  
  // Mostrar mensaje de verificación
  printf("\nSe ha registrado la venta de %d unidades del producto '%s'.\n", cantVendida, nombre);

  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
}

void modificar_datos_de_un_producto(HashMap *mapaProducto, HashMap *mapaSemanal) {
  int opcion, nuevoValor;
  char nombreProducto[100];

  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("\n——————————————————————————————-————————————————————————————————————————————————————————\n");
  
  // Solicitar al usuario el nombre del producto a modificar
  printf("Ingrese el nombre del producto a modificar\n");
  scanf("%s", nombreProducto);

  // Buscar el producto en el mapa mapaProducto
  Pair *buscado = searchMap(mapaProducto, nombreProducto);

  // Verificar si el producto existe en el mapa
  if (buscado == NULL) {
    printf("\nEl producto no existe.\n");
    // Imprimir línea separadora para mejorar la legibilidad en la salida
    printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
    return;
  }

  // Obtener el objeto tipoProducto del mapa
  tipoProducto *producto = buscado->value;

  // Obtener el objeto tipoProducto del mapa mapaSemanal
  tipoProducto *productoSemana = searchMap(mapaSemanal, nombreProducto)->value;

  // Mostrar opciones de modificación
  printf("\nSeleccione qué desea cambiar:\n");
  printf("1. Precio de compra\n");
  printf("2. Precio de venta\n");
  printf("3. Stock inicial\n");
  scanf("%d", &opcion);
  getchar();

  switch (opcion) {
    case 1:
      // Modificar el precio de compra
      printf("\nIngrese el nuevo precio de compra\n");
      scanf("%d", &nuevoValor);
      getchar();
      producto->precioCompra = nuevoValor;
      productoSemana->precioCompra = nuevoValor;
      break;
    case 2:
      // Modificar el precio de venta
      printf("\nIngrese el nuevo precio de venta\n");
      scanf("%d", &nuevoValor);
      getchar();
      producto->precioVenta = nuevoValor;
      productoSemana->precioVenta = nuevoValor;
      break;
    case 3:
      // Modificar el stock inicial
      printf("\nIngrese el nuevo stock inicial\n");
      scanf("%d", &nuevoValor);
      getchar();
      producto->stockInicial = nuevoValor;
      productoSemana->stockInicial = nuevoValor;
      break;
    default:
      printf("Opción inválida\n");
      return;
  }

  printf("\nLos datos del producto '%s' han sido modificados correctamente.\n", nombreProducto);
  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
}


void Cargar_csv_de_stock(HashMap *mapaProducto, HashMap *mapaSemanal, char *nombre_archivo, tipoDia *dia) {
  char caracter[100], *nombre;
  FILE *archivoCsv = fopen(nombre_archivo, "r");
  int precioCompra, precioVenta, stockInicial, cantVendida, opcion;

  // Verificar si el archivo existe
  if (archivoCsv == NULL) {
    printf("\nEl archivo %s no existe en el directorio actual o está mal escrito.\n", nombre_archivo);
    return;
  }

  // Leer la primera línea del archivo (encabezados)
  fgets(caracter, 99, archivoCsv);

  // Leer los datos de cada línea del archivo CSV
  while (fscanf(archivoCsv, "%m[^,],%d,%d,%d\n", &nombre, &precioCompra, &precioVenta, &stockInicial) != EOF) {
    // Crear un nuevo objeto tipoProducto
    tipoProducto *producto = malloc(sizeof(tipoProducto));
    producto->nombre = strdup(nombre);
    producto->precioCompra = precioCompra;
    producto->precioVenta = precioVenta;
    producto->stockInicial = stockInicial;
    producto->cantVendida = 0;

    // Actualizar el gasto del día
    dia->gastoDia += stockInicial * precioCompra;

    // Insertar el producto en el mapa mapaProducto
    insertMap(mapaProducto, producto->nombre, producto);

    // Verificar si el producto ya existe en el mapa mapaSemanal
    if (searchMap(mapaSemanal, producto->nombre) == NULL)
      insertMap(mapaSemanal, producto->nombre, producto);
    else {
      // Si el producto ya existe en mapaSemanal, actualizar el stock inicial
      tipoProducto *productoExistente = searchMap(mapaSemanal, producto->nombre)->value;
      productoExistente->stockInicial += stockInicial;
    }
  }

  // Mostrar mensaje de éxito
  printf("\nArchivo importado correctamente.\n");
  fclose(archivoCsv);
}


void comparar_y_graficar_informes() {
  // Imprimir línea separadora para mejorar la legibilidad en la salida
  printf("\n——————————————————————————————-————————————————————————————————————————————————————————\n");
  // Ejecutar el primer comando de Python para generar un informe o gráfico
  system("python pythonSemanalComparacion.py");

  // Ejecutar el segundo comando de Python para generar otro informe o gráfico
  printf("\n");
  system("python pythonSemanalComparacion.py");
  // Imprimir línea separadora para mejorar la legibilidad en la salida
    printf("——————————————————————————————-————————————————————————————————————————————————————————\n");
}


void Exportar_mapa(char *nombre_archivoDinero, char *nombre_archivo, Heap *monticuloMaximo, Heap *monticuloMinimo, List* listaDia) {
  int contador = 1;
  tipoDia *dineroDia = lastList(listaDia);

  // Exportar el archivo con información sobre ganancia y gastos
  FILE *archivoDinero = fopen(nombre_archivoDinero, "w");
  fprintf(archivoDinero, "Ganancia,Gastos\n");
  fprintf(archivoDinero, "%d,%d\n", dineroDia->gananciaDia, dineroDia->gastoDia);
  fclose(archivoDinero);

  // Exportar el archivo con información sobre los productos
  FILE *archivo = fopen(nombre_archivo, "w");
  fprintf(archivo, "Producto,Precio de Compra,Precio de Venta,Stock,CantVendida\n");

  tipoProducto *productoMax = heap_top(monticuloMaximo);
  tipoProducto *productoMin = heap_top(monticuloMinimo);

  // Exportar los primeros 5 productos con mayor venta
  while (contador <= 5) {
    fprintf(archivo, "%s,%d,%d,%d,%d", productoMax->nombre,
            productoMax->precioCompra, productoMax->precioVenta,
            productoMax->stockInicial, productoMax->cantVendida);
    productoMax->stockInicial = productoMax->stockInicial - productoMax->cantVendida;
    productoMax->cantVendida = 0;
    fprintf(archivo, "\n");
    heap_popMax(monticuloMaximo);
    productoMax = heap_top(monticuloMaximo);
    contador++;
  }

  // Exportar los siguientes 5 productos con menor venta
  while (contador <= 10) {
    fprintf(archivo, "%s,%d,%d,%d,%d", productoMin->nombre,
            productoMin->precioCompra, productoMin->precioVenta,
            productoMin->stockInicial, productoMin->cantVendida);
    productoMin->stockInicial = productoMin->stockInicial - productoMin->cantVendida;
    productoMin->cantVendida = 0;
    fprintf(archivo, "\n");
    heap_pop(monticuloMinimo);
    productoMin = heap_top(monticuloMinimo);
    contador++;
  }

  // Mostrar mensaje de éxito
  printf("\nArchivo exportado correctamente.\n");
  printf("————————————————————————————————————————————————————————————\n\n");
  fclose(archivo);
}

void Exportar_mapa_semanal(char *nombre_archivo, Heap *monticuloMaximo, Heap *monticuloMinimo, List* listaDia) {
  int contador = 1;
  FILE *archivo = fopen(nombre_archivo, "w");
  fprintf(archivo, "Producto,Precio de Compra,Precio de Venta,Stock,CantVendida,GastoDia,GananciaDia\n");

  tipoProducto *productoMax = heap_top(monticuloMaximo);
  tipoProducto *productoMin = heap_top(monticuloMinimo);
  tipoDia *auxiliar = firstList(listaDia);

  // Exportar los primeros 5 productos con mayor venta
  while (contador <= 5) 
  {
    fprintf(archivo, "%s,%d,%d,%d,%d,%d,%d", productoMax->nombre, productoMax->precioCompra, productoMax->precioVenta, productoMax->stockInicial, productoMax->cantVendida, auxiliar->gastoDia, auxiliar->gananciaDia);
    fprintf(archivo, "\n");
    productoMax->stockInicial = productoMax->stockInicial - productoMax->cantVendida;
    productoMax->cantVendida = 0;
    heap_popMax(monticuloMaximo);
    productoMax = heap_top(monticuloMaximo);
    contador++;
    auxiliar = nextList(listaDia);
  }

  // Exportar los siguientes 3 productos con menor venta junto con los datos de gasto y ganancia correspondientes
  while (contador <= 10) 
  {
    if (contador <= 7) 
    {
      fprintf(archivo, "%s,%d,%d,%d,%d,%d,%d\n", productoMin->nombre, productoMin->precioCompra, productoMin->precioVenta, productoMin->stockInicial, productoMin->cantVendida, auxiliar->gastoDia, auxiliar->gananciaDia);
      auxiliar = nextList(listaDia);
    } 
    else 
    {
      fprintf(archivo, "%s,%d,%d,%d,%d\n", productoMin->nombre, productoMin->precioCompra, productoMin->precioVenta, productoMin->stockInicial, productoMin->cantVendida);
    }
    contador++;
    heap_pop(monticuloMinimo);
    productoMin = heap_top(monticuloMinimo);
  }

  // Mostrar mensaje de éxito
  printf("\nArchivo exportado correctamente.\n");
  printf("————————————————————————————————————————————————————————————\n\n");
  fclose(archivo);

  // Exportar el nombre del archivo a un archivo adicional y ejecutar un script de Python
  FILE *nombreArchivo = fopen("nombre.csv", "w");
  fprintf(nombreArchivo, "%s", nombre_archivo);
  fclose(nombreArchivo);
  system("python pythonSemanal.py");
}

void finalizarDia(HashMap *mapaProducto, HashMap *mapaSemanal, List *listaDia, int *contadorDia, tipoDia *dia) {
  Heap *monticuloMaximo = createHeap();
  Heap *monticuloMinimo = createHeap();
  tipoDia *auxDia = malloc(sizeof(tipoDia));
  auxDia = memcpy(auxDia, dia, sizeof(tipoDia));
  pushBack(listaDia, auxDia);

  // Si no es el último día de la semana (días 1 a 6)
  if (*contadorDia != 7) 
  {
    Pair *aux = firstMap(mapaProducto);
    while (aux != NULL) 
    {
      tipoProducto *producto = (tipoProducto *)aux->value;
      heap_pushMax(monticuloMaximo, producto, producto->cantVendida);
      heap_pushMin(monticuloMinimo, producto, producto->cantVendida);
      aux = nextMap(mapaProducto);
    }
    char *nombre_archivo = "csvDiario.csv";
    char *nombre_archivoDinero = "csvDiarioDinero.csv";
    Exportar_mapa(nombre_archivoDinero, nombre_archivo, monticuloMaximo, monticuloMinimo, listaDia);
    free(monticuloMaximo);
    free(monticuloMinimo);
    system("python pythonDiarioMax.py");
    system("python pythonDiarioMin.py");
    system("python pythonDiarioGanancia.py");
    dia->gananciaDia = 0;
    dia->gastoDia = 0;
  }
  // Si es el último día de la semana (día 7)
  else 
  {
    Pair *aux = firstMap(mapaSemanal);
    char *nombre_archivo;
    while (aux != NULL) 
    {
      tipoProducto *producto = (tipoProducto *)aux->value;
      heap_pushMax(monticuloMaximo, producto, producto->cantVendida);
      heap_pushMin(monticuloMinimo, producto, producto->cantVendida);
      aux = nextMap(mapaSemanal);
    }
    printf("\n¿Cómo quiere llamar el archivo de esta semana? Introduzca el formato (.csv)\n");
    scanf("%m[^\n]", &nombre_archivo);
    getchar();
    Exportar_mapa_semanal(nombre_archivo, monticuloMaximo, monticuloMinimo, listaDia);
    dia->gananciaDia = 0;
    dia->gastoDia = 0;
    exit(EXIT_SUCCESS);
  }
}


int main() {
  tipoDia *dia = malloc(sizeof(tipoDia));
  dia->gananciaDia = 0;
  dia->gastoDia = 0;
  HashMap *mapaProducto = createMap((long)100);
  HashMap *mapaSemanal = createMap((long)100);
  List *listaDias = createList();
  char caracter[100], *nombre, *archivoCargado;
  int precioCompra, precioVenta, stockInicial, opcion, contadorDia = 1;
  FILE *ArchivoPrueba = fopen("ArchivoPrueba.csv", "r");
  // Leer el encabezado del archivo
  fgets(caracter, 99, ArchivoPrueba);
  // Leer los datos de los productos del archivo
  while (fscanf(ArchivoPrueba, "%m[^,],%d,%d,%d\n", &nombre, &precioCompra,
                &precioVenta, &stockInicial) != EOF) {
    tipoProducto *producto = malloc(sizeof(tipoProducto));
    producto->nombre = strdup(nombre);
    producto->precioCompra = precioCompra;
    producto->precioVenta = precioVenta;
    producto->stockInicial = stockInicial;
    producto->cantVendida = 0;
    insertMap(mapaProducto, producto->nombre, producto);
    // Crear una copia del producto para el mapa semanal
    tipoProducto *copiaProductoAux = malloc(sizeof(tipoProducto));
    copiaProductoAux->nombre = strdup(nombre);
    copiaProductoAux->precioCompra = precioCompra;
    copiaProductoAux->precioVenta = precioVenta;
    copiaProductoAux->stockInicial = stockInicial;
    copiaProductoAux->cantVendida = 0;
    // Actualizar el gasto diario
    dia->gastoDia += stockInicial * precioCompra;
    // Insertar el producto en los mapas correspondientes
    insertMap(mapaProducto, producto->nombre, producto);
    insertMap(mapaSemanal, producto->nombre, copiaProductoAux);
  }

  fclose(ArchivoPrueba);

  while (true) {
    printf("\n------ Menú Principal ------\n");
    printf("1. Registro de productos\n");
    printf("2. Control de stock\n");
    printf("3. Modificar datos de un producto\n");
    printf("4. Comparar y graficar dos informes semanales\n");
    printf("5. Cargar csv de stock\n");
    printf("6. Finalizar el día, creación de gráfico e informe\n");
    printf("\nSeleccione una opción: \n");
    scanf("%d", &opcion);
    getchar();
    switch (opcion) {
    case 1:
      registro_de_productos(mapaProducto, mapaSemanal, dia);
      break;
    case 2:
      Control_de_stock(mapaProducto, mapaSemanal, dia);
      break;
    case 3:
      modificar_datos_de_un_producto(mapaProducto, mapaSemanal);
      break;
    case 4:
      comparar_y_graficar_informes();
      break;
    case 5:
      printf(
          "\n——————————————————————————————-————————————————————————————————————————————————————————\n");
      printf("Ingrese el nombre del archivo, introduzca el formato (.csv)\n");
      scanf("%m[^\n]", &archivoCargado);
      
      getchar();
      if (strstr(archivoCargado, ".csv") == 0) {
        printf("\nEl formato del archivo '%s' es incorrecto.\n",
               archivoCargado);
        printf(
            "——————————————————————————————-————————————————————————————————————————————————————————\n\n");
        break;
      }
      Cargar_csv_de_stock(mapaProducto, mapaSemanal, archivoCargado, dia);
      printf(
          "——————————————————————————————-————————————————————————————————————————————————————————\n\n");
      break;
    case 6:
      finalizarDia(mapaProducto, mapaSemanal, listaDias, &contadorDia, dia);
      contadorDia++;
      break;
    default:
      break;
    }
  }
}