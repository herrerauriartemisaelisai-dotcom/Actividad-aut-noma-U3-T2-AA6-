#include <iostream>
using namespace std;

// Tope de días que vamos a guardar (como un “máximo” del sistema)
const int MAX = 365;

// ===================== PROTOTIPOS =====================
// Estas funciones son las “puertas de entrada” para que el usuario escriba bien los datos
int leerEnteroMinimo(const string &mensaje, int minimo);
int leerEnteroRango(const string &mensaje, int min, int max);

// Esto solo es para mostrar todo bonito en pantalla
void mostrarRegistros(int pasos[], int minutos[], int calorias[], int n);

// Acciones del menú (lo que el usuario puede hacer)
void ingresarDatos(int pasos[], int minutos[], int calorias[], int &n);
void insertarRegistro(int pasos[], int minutos[], int calorias[], int &n);
void modificarRegistro(int pasos[], int minutos[], int calorias[], int n);
void buscarRegistro(int pasos[], int minutos[], int calorias[], int n);
void ordenarRegistros(int pasos[], int minutos[], int calorias[], int n);
void eliminarRegistro(int pasos[], int minutos[], int calorias[], int &n);

// Para el análisis (estadísticas)
double media(int v[], int n);
double mediana(int v[], int n);
int moda(int v[], int n);

// Extra (un “plus” para cada arreglo)
int maximo(int v[], int n);
int minimo(int v[], int n);
int contarDiasSobre(int v[], int n, int umbral);

void analisisEstadistico(int pasos[], int minutos[], int calorias[], int n);

// ===================== MAIN =====================
int main() {
    // Ojo: estos 3 arreglos van “en combo”
    // El mismo índice i significa “el mismo día” en pasos, minutos y calorías
    int pasos[MAX], minutos[MAX], calorias[MAX];
    int n = 0; // cuántos días llevamos guardados hasta ahora

    int opcion;

    do {
        cout << "\n===== SISTEMA DE ACTIVIDAD FISICA (ARREGLOS) =====\n";
        cout << "Registros actuales: " << n << "\n";
        cout << "1. Ingresar datos (manual)\n";
        cout << "2. Insertar registro en posicion\n";
        cout << "3. Modificar registro\n";
        cout << "4. Buscar registro\n";
        cout << "5. Ordenar registros (por pasos)\n";
        cout << "6. Eliminar registro\n";
        cout << "7. Analisis estadistico\n";
        cout << "8. Mostrar todos los registros\n";
        cout << "0. Salir\n";

        // Aquí evitamos que el usuario se salga del menú con cualquier cosa rara
        opcion = leerEnteroRango("Seleccione una opcion: ", 0, 8);

        // Según lo que elija, mandamos a la función correspondiente
        switch (opcion) {
            case 1: ingresarDatos(pasos, minutos, calorias, n); break;
            case 2: insertarRegistro(pasos, minutos, calorias, n); break;
            case 3: modificarRegistro(pasos, minutos, calorias, n); break;
            case 4: buscarRegistro(pasos, minutos, calorias, n); break;
            case 5: ordenarRegistros(pasos, minutos, calorias, n); break;
            case 6: eliminarRegistro(pasos, minutos, calorias, n); break;
            case 7: analisisEstadistico(pasos, minutos, calorias, n); break;
            case 8: mostrarRegistros(pasos, minutos, calorias, n); break;
            case 0: cout << "Saliendo...\n"; break;
        }

    } while (opcion != 0);

    return 0;
}

// ===================== VALIDACIONES =====================

// Esta función es como un “filtro”: no deja pasar números menores al mínimo
// Ej: pasos, minutos o calorías no deberían ser negativos
int leerEnteroMinimo(const string &mensaje, int minimo) {
    int x;
    do {
        cout << mensaje;
        cin >> x;

        // Si aquí escriben letras o algo loco, lo limpiamos y pedimos otra vez
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            x = minimo - 1; // para que obligatoriamente repita
        } else if (x < minimo) {
            cout << "Debe ser >= " << minimo << ". Intente de nuevo.\n";
        }
    } while (x < minimo);
    return x;
}

// Esta es la “barrera” para que el usuario solo elija números dentro del rango permitido
// Ej: opciones del menú o índices válidos
int leerEnteroRango(const string &mensaje, int min, int max) {
    int x;
    do {
        cout << mensaje;
        cin >> x;

        // Si se equivocan escribiendo texto, lo corregimos sin que el programa muera
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            x = min - 1;
        } else if (x < min || x > max) {
            cout << "Debe estar entre " << min << " y " << max << ".\n";
        }
    } while (x < min || x > max);
    return x;
}

// ===================== UTILIDAD =====================
void mostrarRegistros(int pasos[], int minutos[], int calorias[], int n) {
    if (n == 0) {
        cout << "No hay registros.\n";
        return;
    }

    cout << "\nIndice | Pasos | Minutos | Calorias\n";
    cout << "-----------------------------------\n";

    // Vamos día por día (mismo índice = mismo día) y mostramos el “combo” completo
    for (int i = 0; i < n; i++) {
        cout << "  " << i << "    |  " << pasos[i]
             << "   |   " << minutos[i]
             << "    |   " << calorias[i] << "\n";
    }
}

// ===================== PARTE I: GESTION =====================

// 1) Ingreso manual
void ingresarDatos(int pasos[], int minutos[], int calorias[], int &n) {
    if (n == MAX) {
        cout << "Ya se llego al maximo de registros.\n";
        return;
    }

    // No dejamos que pidan más días de los que caben
    int cant = leerEnteroRango("Cuantos dias desea ingresar? ", 1, MAX - n);

    for (int i = 0; i < cant; i++) {
        cout << "\n--- Dia " << (n + 1) << " ---\n";

        // Guardamos todo en el mismo “n” para que sea el mismo día en los 3 arreglos
        pasos[n]    = leerEnteroMinimo("Pasos (>=0): ", 0);
        minutos[n]  = leerEnteroMinimo("Minutos (>=0): ", 0);
        calorias[n] = leerEnteroMinimo("Calorias (>=0): ", 0);

        n++; // ya ocupamos un día más
    }

    cout << "Datos ingresados correctamente.\n";
}

// 2) Insertar en posición específica
void insertarRegistro(int pasos[], int minutos[], int calorias[], int &n) {
    if (n == MAX) {
        cout << "No se puede insertar. Arreglo lleno.\n";
        return;
    }
    if (n == 0) {
        cout << "No hay datos. Use 'Ingresar datos' primero.\n";
        return;
    }

    // Puede insertar en cualquier parte, incluso al final (pos = n)
    int pos = leerEnteroRango("Posicion a insertar (0 a n): ", 0, n);

    int p = leerEnteroMinimo("Pasos (>=0): ", 0);
    int m = leerEnteroMinimo("Minutos (>=0): ", 0);
    int c = leerEnteroMinimo("Calorias (>=0): ", 0);

    // Aquí “corremos” todo a la derecha para abrir un espacio en la posición elegida
    // Y ojo: se hace en los 3 arreglos para que no se desordene el día
    for (int i = n; i > pos; i--) {
        pasos[i] = pasos[i - 1];
        minutos[i] = minutos[i - 1];
        calorias[i] = calorias[i - 1];
    }

    // Ahora sí, colocamos el nuevo día justo donde el usuario pidió
    pasos[pos] = p;
    minutos[pos] = m;
    calorias[pos] = c;

    n++;
    cout << "Registro insertado.\n";
}

// 3) Modificar un registro
void modificarRegistro(int pasos[], int minutos[], int calorias[], int n) {
    if (n == 0) {
        cout << "No hay registros.\n";
        return;
    }

    int pos = leerEnteroRango("Indice a modificar (0 a n-1): ", 0, n - 1);

    // Cambiamos el “mismo día” en las 3 cosas, para que siga siendo coherente
    pasos[pos]    = leerEnteroMinimo("Nuevo pasos (>=0): ", 0);
    minutos[pos]  = leerEnteroMinimo("Nuevo minutos (>=0): ", 0);
    calorias[pos] = leerEnteroMinimo("Nuevo calorias (>=0): ", 0);

    cout << "Registro modificado.\n";
}

// 4) Buscar en cualquiera de los arreglos
void buscarRegistro(int pasos[], int minutos[], int calorias[], int n) {
    if (n == 0) {
        cout << "No hay registros.\n";
        return;
    }

    cout << "\nBuscar en:\n1) Pasos\n2) Minutos\n3) Calorias\n";
    int tipo = leerEnteroRango("Opcion: ", 1, 3);
    int valor = leerEnteroMinimo("Valor a buscar (>=0): ", 0);

    int encontrado = 0;

    // Vamos revisando día por día, y si coincide, mostramos todo el paquete de ese día
    for (int i = 0; i < n; i++) {
        bool match = false;

        if (tipo == 1 && pasos[i] == valor) match = true;
        if (tipo == 2 && minutos[i] == valor) match = true;
        if (tipo == 3 && calorias[i] == valor) match = true;

        if (match) {
            cout << "Encontrado en indice " << i
                 << " | Pasos: " << pasos[i]
                 << " | Minutos: " << minutos[i]
                 << " | Calorias: " << calorias[i] << "\n";
            encontrado++;
        }
    }

    if (encontrado == 0) cout << "No se encontro el valor.\n";
}

// 5) Ordenar asc/desc (por PASOS)
void ordenarRegistros(int pasos[], int minutos[], int calorias[], int n) {
    if (n == 0) {
        cout << "No hay registros.\n";
        return;
    }

    cout << "\n1) Ascendente\n2) Descendente\n";
    int tipo = leerEnteroRango("Opcion: ", 1, 2);

    // Ordenamos por pasos… pero sin “romper” los otros datos
    // O sea: si se mueve un día, se mueve completo (pasos, minutos y calorías)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {

            bool condicion = false;
            if (tipo == 1 && pasos[j] > pasos[j + 1]) condicion = true;
            if (tipo == 2 && pasos[j] < pasos[j + 1]) condicion = true;

            if (condicion) {
                // Intercambiamos “el día completo” usando una variable aux
                int aux;

                aux = pasos[j]; pasos[j] = pasos[j + 1]; pasos[j + 1] = aux;
                aux = minutos[j]; minutos[j] = minutos[j + 1]; minutos[j + 1] = aux;
                aux = calorias[j]; calorias[j] = calorias[j + 1]; calorias[j + 1] = aux;
            }
        }
    }

    cout << "Registros ordenados por pasos.\n";
}

// 6) Eliminar por posición o por condición
void eliminarRegistro(int pasos[], int minutos[], int calorias[], int &n) {
    if (n == 0) {
        cout << "No hay registros.\n";
        return;
    }

    cout << "\nEliminar:\n1) Por posicion\n2) Por condicion (minutos == 0)\n";
    int tipo = leerEnteroRango("Opcion: ", 1, 2);

    if (tipo == 1) {
        int pos = leerEnteroRango("Indice a eliminar (0 a n-1): ", 0, n - 1);

        // Quitamos ese día y “cerramos el hueco” corriendo todo a la izquierda
        for (int i = pos; i < n - 1; i++) {
            pasos[i] = pasos[i + 1];
            minutos[i] = minutos[i + 1];
            calorias[i] = calorias[i + 1];
        }

        n--;
        cout << "Registro eliminado.\n";

    } else {
        // Regla extra: borrar días donde no hubo actividad (minutos == 0)
        int eliminados = 0;
        int i = 0;

        // Usamos while porque cuando borramos, todo se recorre y hay que revisar el índice otra vez
        while (i < n) {
            if (minutos[i] == 0) {
                for (int k = i; k < n - 1; k++) {
                    pasos[k] = pasos[k + 1];
                    minutos[k] = minutos[k + 1];
                    calorias[k] = calorias[k + 1];
                }
                n--;
                eliminados++;
                // aquí NO avanzamos i, porque ahora cayó otro registro justo en este mismo índice
            } else {
                i++;
            }
        }

        cout << "Eliminados por condicion (minutos==0): " << eliminados << "\n";
    }
}

// ===================== ANALISIS =====================

// Promedio “normalito”: sumamos todo y dividimos para n
double media(int v[], int n) {
    if (n == 0) return 0;

    long suma = 0; // por si la suma se pone grande con muchos días
    for (int i = 0; i < n; i++) suma += v[i];

    return (double)suma / n;
}

// La mediana es el “valor del medio”, pero para eso primero necesitamos ordenar (sin dañar el original)
double mediana(int v[], int n) {
    if (n == 0) return 0;

    int copia[MAX];

    // Hacemos una copia para que los datos reales no cambien de orden
    for (int i = 0; i < n; i++) copia[i] = v[i];

    // Ordenamos la copia (simple y suficiente para la tarea)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (copia[j] > copia[j + 1]) {
                int aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
            }
        }
    }

    // Si hay cantidad impar, el del medio es directo
    if (n % 2 == 1) return copia[n / 2];

    // Si hay cantidad par, el “medio” se saca promediando los dos del centro
    return (copia[n / 2 - 1] + copia[n / 2]) / 2.0;
}

// La moda es el valor que más se repite (el “más popular”)
int moda(int v[], int n) {
    if (n == 0) return 0;

    int mejorValor = v[0];
    int mejorFrecuencia = 1;

    // Vamos probando cada valor y contando cuántas veces aparece
    for (int i = 0; i < n; i++) {
        int cont = 0;
        for (int j = 0; j < n; j++) {
            if (v[j] == v[i]) cont++;
        }

        // Si este gana por repetición, se convierte en la nueva moda
        if (cont > mejorFrecuencia) {
            mejorFrecuencia = cont;
            mejorValor = v[i];
        }
    }

    return mejorValor;
}

// Extra: sacar el número más alto del arreglo (el “día más heavy” en ese dato)
int maximo(int v[], int n) {
    int mx = v[0];
    for (int i = 1; i < n; i++) if (v[i] > mx) mx = v[i];
    return mx;
}

// Extra: sacar el número más bajito del arreglo (el “día más flojo” en ese dato)
int minimo(int v[], int n) {
    int mn = v[0];
    for (int i = 1; i < n; i++) if (v[i] < mn) mn = v[i];
    return mn;
}

// Cuenta cuántos días llegaron a cierta meta (por ejemplo: 10.000 pasos)
int contarDiasSobre(int v[], int n, int umbral) {
    int cont = 0;
    for (int i = 0; i < n; i++) if (v[i] >= umbral) cont++;
    return cont;
}

// Aquí sacamos todo el resumen estadístico de cada arreglo
void analisisEstadistico(int pasos[], int minutos[], int calorias[], int n) {
    if (n == 0) {
        cout << "No hay registros para analizar.\n";
        return;
    }

    cout << "\n===== ANALISIS ESTADISTICO =====\n";

    cout << "\n--- PASOS ---\n";
    cout << "Media: " << media(pasos, n) << "\n";
    cout << "Mediana: " << mediana(pasos, n) << "\n";
    cout << "Moda: " << moda(pasos, n) << "\n";
    cout << "Extra (Dias con >= 10000 pasos): " << contarDiasSobre(pasos, n, 10000) << "\n";

    cout << "\n--- MINUTOS ---\n";
    cout << "Media: " << media(minutos, n) << "\n";
    cout << "Mediana: " << mediana(minutos, n) << "\n";
    cout << "Moda: " << moda(minutos, n) << "\n";
    cout << "Extra (Maximo de minutos en un dia): " << maximo(minutos, n) << "\n";

    cout << "\n--- CALORIAS ---\n";
    cout << "Media: " << media(calorias, n) << "\n";
    cout << "Mediana: " << mediana(calorias, n) << "\n";
    cout << "Moda: " << moda(calorias, n) << "\n";
    cout << "Extra (Minimo de calorias en un dia): " << minimo(calorias, n) << "\n";
}
