<div align="center">

# ⛓️ AwesomeCoin

**Blockchain educativa escrita en C++17 · consola interactiva · prueba de trabajo (PoW) · SHA-256 implementado desde cero**

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![Plataforma](https://img.shields.io/badge/plataforma-Linux%20%7C%20Windows-lightgrey)
![Dependencias](https://img.shields.io/badge/dependencias-solo%20STL-green)

</div>

---

## 📖 Descripción

**AwesomeCoin** es una implementación educativa de una blockchain en C++ puro (sin librerías externas). Permite crear cuentas con par de claves, acumular transferencias en una lista pendiente y, al cerrar la aplicación, **minarlas en un bloque** mediante **prueba de trabajo (Proof of Work)**, imprimir la cadena completa y **validar su integridad**.

El proyecto surgió como práctica académica (originalmente `Project2` en Visual Studio) y está portado a una estructura multiplataforma que compila limpiamente en **Linux** y **Windows** con `-Wall -Wextra` sin avisos.

## ✨ Características

- ⛓️ **Cadena de bloques en memoria** con bloque **génesis** (`Previous Hash = 0`).
- ⛏️ **Minado PoW**: se incrementa el *nonce* hasta hallar un hash cuyo prefijo hexadecimal empiece por tantos `0` como marca la dificultad (`2` por defecto → prefijo `00`).
- #️⃣ **SHA-256 implementado a mano** (`src/crypto/sha256.h`): padding, expansión de palabras, 64 rondas de compresión y salida hexadecimal de 64 caracteres.
- 🔗 **Encadenado y validación**: cada bloque referencia el hash del anterior; `isChainValid()` recalcula todos los hashes y comprueba los enlaces.
- 💸 **Comisiones (fee)**: cada transferencia lleva comisión para el minero; el bloque acumula el total (`FeeBlock`).
- 👤 **Cuentas**: clave privada aleatoria de 6 dígitos y clave pública derivada con hash.
- 🖥️ **CLI interactiva** multiplataforma (sin `conio.h` ni dependencias de Windows).
- 🧾 **Lista de transacciones pendientes** (lista enlazada propia) que se consolida en un único bloque al salir.

## 📋 Requisitos

| Requisito | Detalle |
|---|---|
| Compilador | GCC ≥ 8 / Clang ≥ 7 / MinGW-w64 — soporte **C++17** |
| Sistema operativo | Linux, macOS o Windows |
| Dependencias externas | **Ninguna** — solo la librería estándar de C++ (STL) |

## 🔨 Compilación

Los módulos se incluyen entre sí con rutas relativas a `src/`, por lo que hay que pasar los directorios de cabeceras con `-I`:

### Linux / macOS

```bash
g++ -std=c++17 -O2 -Wall -Wextra \
    -Isrc/core -Isrc/blockchain -Isrc/crypto \
    -o blockchain \
    src/main.cpp \
    src/blockchain/Block.cpp \
    src/blockchain/Blockchain.cpp \
    src/core/Usuario.cpp

./blockchain
```

### Windows (MinGW-w64)

```powershell
g++ -std=c++17 -O2 -Wall -Wextra `
    -Isrc/core -Isrc/blockchain -Isrc/crypto `
    -o blockchain.exe `
    src/main.cpp src/blockchain/Block.cpp `
    src/blockchain/Blockchain.cpp src/core/Usuario.cpp

.\blockchain.exe
```

> **Notas de compilación**
> - `src/core/Cuenta.cpp` y `src/crypto/sha256.cpp` están vacíos por ahora (módulos reservados); no hace falta compilarlos.
> - La versión original usaba cabeceras exclusivas de Windows (`conio.h`, `_getch()`, `system("cls")`); el código actual es portable y usa ramas condicionales `#ifdef _WIN32`.
> - El proyecto compila **sin errores y sin warnings** con `-Wall -Wextra` (verificado con GCC 15).

## 🎮 Uso

Al ejecutar el programa se muestra un menú principal:

```
Que desea realizar ?
Crear Cuenta--(1)
Ingresar en Cuenta--(2)
Salir--(3)
```

| Opción | Acción |
|---|---|
| `1` | **Crear cuenta** — genera clave privada aleatoria (6 dígitos) y su clave pública derivada por hash. Guárdalas: se muestran una sola vez. |
| `2` | **Ingresar en cuenta** — abre el submenú de transacciones. |
| `3` | **Salir** — mina el bloque con todas las transacciones pendientes, imprime la cadena y la valida. |

Dentro de una cuenta:

```
Que desea realizar ?
Realizar Transferencia--(1)
Salir--(2)
```

| Opción | Acción |
|---|---|
| `1` | Registrar una transferencia: pide **monto** y **comisión del minero**. Se acumula en la lista pendiente. |
| `2` | Volver al menú principal. |

### Ejemplo de sesión

```text
Que desea realizar ? Crear Cuenta--(1)
Tu clave privada es: 483920 Guardala en un lugar seguro
Tu clave publica es: 197384655... Guardala para evitar errores

Que desea realizar ? Ingresar en Cuenta--(2)
Que desea realizar ? Realizar Transferencia--(1)
Cuanto dinero desea enviar ?: 99.99
Cuanta Comision desea darle al minero ?: 0.25

Presione ENTER para continuar...

Que desea realizar ? Salir--(3)

008ceccb5cacc735e6eaae02e835861f554b66d7ba4c233204bcaa350556c60d++++++++++++++++18
Block mined: 008ceccb5cacc735e6eaae02e835861f554b66d7ba4c233204bcaa350556c60d

Block ===================================
Index: 0
Nonce: 0
FeeBlock: 0
Hash: f0bc3794128101cae0e54ba7cc25c60d9e435ca422246e7bd6c7e4000c5c5cf4
Previous Hash: 0
Is Block Valid?: 1

Block ===================================
Index: 1
Amount: 99.990000
Fee: 0.250000
SenderKey: Joe
ReceiverKey: Sally
Timestamp: 1789383978
Nonce: 18
FeeBlock: 0.25
Hash: 008ceccb5cacc735e6eaae02e835861f554b66d7ba4c233204bcaa350556c60d
Previous Hash: f0bc3794128101cae0e54ba7cc25c60d9e435ca422246e7bd6c7e4000c5c5cf4
Is Block Valid?: 1

Is chain still valid? 1
ESTA CADENA ES VALIDA
```

## 🧱 Anatomía de un bloque

| Campo | Tipo | Descripción |
|---|---|---|
| `index` | `int` | Altura del bloque en la cadena (génesis = 0) |
| `timestamp` | `time_t` | Momento de creación de cada transacción |
| `transactions` | `ListTransactions*` | Lista enlazada de transacciones consolidadas |
| `fee` | `double` | Suma de comisiones de las transacciones del bloque |
| `_nNonce` | `int64_t` | Contador que se incrementa durante el minado |
| `previousHash` | `string` | Hash del bloque anterior (`"0"` para el génesis) |
| `blockHash` | `string` | SHA-256 hex (64 caracteres) de todo lo anterior |

## 📂 Estructura del proyecto

```text
blockchain/
├── README.md                      ← este archivo
├── docs/
│   └── ARCHITECTURE.md            ← arquitectura técnica completa
├── config/                        (reservado)
├── examples/                      (reservado)
├── scripts/                       (reservado)
├── tests/                         (reservado)
└── src/
    ├── main.cpp                   ← CLI: menús, sesión y cierre de cadena
    ├── blockchain/
    │   ├── Blockchain.h/.cpp      ← cadena, génesis, minado y validación
    │   ├── Block.h/.cpp           ← bloque: hash, PoW y comisiones
    │   └── TransactionData.h      ← transacción + lista enlazada
    ├── core/
    │   ├── Usuario.h/.cpp         ← cuentas: claves pública/privada
    │   └── Cuenta.h/.cpp          (reservado — cartera)
    └── crypto/
        └── sha256.h/.cpp          ← SHA-256 implementado desde cero
```

## 🏛️ Arquitectura (resumen)

Cuatro capas con dependencias unidireccionales; los detalles completos (diagramas de clases, pipeline de hashing, modelo de memoria, complejidad y seguridad) están en **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)**:

```
main.cpp (CLI)  →  core/Usuario (identidad)
       ↓
blockchain/ (Blockchain → Block → ListTransactions)
       ↓
crypto/sha256 (hash)
```

- **`Blockchain`** posee el `std::vector<Block*>` y orquesta: crea el génesis en su constructor, `addBlock()` construye el bloque con el hash del último, mina con PoW y lo añade.
- **`Block`** calcula su hash sobre el contenido de sus transacciones + fee + nonce + hash previo, y valida integridad recalculándolo.
- **`ListTransactions`** es una lista enlazada propia (LIFO) de `NodoTransaction`, cada uno envolviendo una `TransactionData`.

## 🗺️ Roadmap

Tareas pendientes marcadas en los comentarios del propio código:

- [ ] **Balances**: efectuar el intercambio de montos al minar el bloque (`Blockchain.cpp`, todo `EFECTUAR INTERCAMBIO DE MONTOS`) y conectar la clase `Usuario`/`Cuenta`.
- [ ] **Transacciones reales**: usar la clave pública del usuario logueado como `senderKey` en vez de los remitentes de prueba (`"Joe"`/`"Sally"`) y validar firma (`_ComprobationKey`, todo `COMPROBAR PRIVADA`).
- [ ] **Múltiples bloques**: hoy la consola consolida todo en un bloque al salir; permitir cerrar/minar bloques de forma incremental.
- [ ] **Persistencia**: volcar la cadena a disco (`*.json`, SQLite) — `.gitignore` ya reserva rutas `*.db`.
- [ ] **Pruebas**: poblar `tests/` con casos de validación de cadena, mutaciones y SHA-256 contra vectores oficiales NIST.
- [ ] **Mejoras**: reemplazar `std::hash` intermedio por SHA-256 directo, `system("clear")` por códigos ANSI, smart pointers para la propiedad de bloques.

## ⚠️ Advertencia

Proyecto **educativo**: la implementación criptográfica y el consenso son simplificados (PoW de dificultad 2, SHA-256 con `std::hash` intermedio, cadena en memoria). **No usar en producción ni manejar valor real.**

## 📄 Licencia

Sin licencia declarada todavía — todos los derechos reservados a su autor.

---

<div align="center">
Hecho con C++17 · <a href="docs/ARCHITECTURE.md">Ver arquitectura completa</a>
</div>

