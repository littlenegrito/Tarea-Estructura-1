# Tarea-Estructura-1

Descripcion:
Este programa sirve para gestionar la atención de pacientes de un hospital, incluyendo las funciones de registrar nuevos pacientes con su información, asignar prioridades, mostrar lista de espera, y atender. El objetivo es automatizar varios pasos del proceso de la cola de espera, ajustando la atención según la prioridad que se le asigne manualmente para asegurar un proceso eficiente pero seguro.

## Cómo compilar y ejecutar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `(https://github.com/littlenegrito/Tarea-Estructura-1.git)`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Antes de ejecutar, copia el codigo "(gcc -o main main.c tdas/extra.c tdas/list.c tdas/map.c && ./main)" en la configuración de ejecutar
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Mostrar la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.
- Mostrar pacientes de prioridad especifica.

### Problemas conocidos:

- La funcionalidad para exportar e importar la lista de espera desde/hacia un archivo CSV aún está en desarrollo.

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Permitir la edición de los datos básicos de los pacientes.
- Recopilar información importante para guardar registros diarios.
