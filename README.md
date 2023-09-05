# Tarea-1-ED

# Sistema menu de Biblioteca

## Descripción
Esta tarea es un sistema menu de gestión de biblioteca que permite a los usuarios realizar varias acciones relacionadas con libros y reservas. Los usuarios pueden agregar libros a la biblioteca, ver información detallada de los libros, realizar reservas, cancelar reservas, retirar libros y devolver libros. También pueden ver una lista de libros prestados y cargar datos de libros desde un archivo CSV, así como exportar los datos de la biblioteca a un archivo CSV.

## Cómo Compilar y Ejecutar

**Para compilar y ejecutar este proyecto, siga estos pasos:**

-Abre Replit e inicia sesión en tu cuenta.
-Crea un nuevo proyecto o abre uno existente.
-Tambien puedes importar directamente el repositorio desde github. presionando en el signo + en la parte superior derecha.
```
url:
https://github.com/Matthias4689/Tarea-1-ED
clone:
https://github.com/Matthias4689/Tarea-1-ED.git
```
-En el panel de la izquierda, arrastra el archivo llamado "tarea1.c".

En la terminal de Replit (parte inferior de la pantalla), compila el código utilizando el siguiente comando:

```
gcc tarea1.c -o tarea1
```
Esto compilará tu código y generará un archivo ejecutable llamado "tarea1".
Ahora puedes ejecutar el programa con el siguiente comando:

```
./tarea1
```
Tu programa se ejecutará y podrás interactuar con él a través de la terminal de Replit.

El repositorio viene con 2 archivos .csv, biblioteca.csv y biblioteca_exportada.csv los cuales se pueden usar en las opciones 9 y 10 del menu interactivo respectivamente.

##Funcionalidades
###Funciones Principales
**Registrar Libro**: Permite a los usuarios agregar nuevos libros a la biblioteca. Los detalles del libro, como título, autor, género, ISBN, ubicación y estado, se ingresan manualmente.

**Mostrar Datos de un Libro**: Los usuarios pueden buscar y ver información detallada de un libro específico proporcionando el título y el autor del libro.

**Mostrar Todos los Libros**: Muestra una lista de todos los libros disponibles en la biblioteca, incluyendo detalles como título, autor, género, ISBN, ubicación y estado.

**Reservar Libro**: Los usuarios pueden reservar un libro específico proporcionando el título, el autor y su nombre. La reserva se registra en el sistema y se muestra en la información del libro.

**Cancelar Reserva**: Permite a los usuarios cancelar una reserva existente proporcionando el título del libro, el autor y su nombre. La reserva se elimina del sistema.

**Retirar Libro**: Los usuarios pueden retirar un libro reservado, siempre que el libro esté reservado en su nombre. El libro se retira y la reserva se elimina.

**Devolver Libro**: Permite a los usuarios devolver un libro previamente retirado. La reserva se elimina y el libro se marca como disponible.

**Mostrar Libros Prestados**: Muestra una lista de libros que están actualmente prestados, es decir, aquellos con reservas activas.

###Funciones Adicionales
**Subir Datos desde Archivo CSV**: Los usuarios pueden cargar datos de libros desde un archivo CSV proporcionando el nombre del archivo. Los datos del archivo CSV deben estar formateados correctamente.

**Exportar Datos a Archivo CSV**: Permite a los usuarios exportar los datos de la biblioteca a un archivo CSV proporcionando el nombre del archivo de destino.

###Problemas Conocidos
Algunas operaciones pueden tener problemas si se ingresan datos incorrectos o si se intenta realizar una acción inválida.

###Futuras Mejoras
Ordenar automáticamente la lista de libros por título o autor.
Permitir la edición de libros existentes.
Mejorar la gestión de errores y mensajes de usuario.
