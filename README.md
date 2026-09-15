<div align="center">

# AwesomeCoin

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
- 🔑 **Claves reales y sesión**: la clave pública (derivada por SHA-256) es la dirección on-chain; el acceso a la cartera exige la clave privada (`login`), y las transferencias se firman con la clave del emisor — las inválidas se consignan como `[FIRMA_INVALIDA]`.
- 💰 **Balances**: cada transacción liquida sus montos al minar el bloque (`senderAmount` / `receiverAmount`) y el bloque acumula las comisiones (`FeeBlock`) para el minero.
- 👛 **Cartera** (`src/core/Cuenta.h`): wallet con validación de clave privada en el registro y consulta de saldos por dirección.
- 🖥️ **CLI interactiva** multiplataforma (sin `conio.h` ni dependencias de Windows).
- 🧾 **Lista de transacciones pendientes** (lista enlazada propia) que se consolida en un único bloque al salir.
- 🧪 **Suite de pruebas** en `tests/`: SHA-256 contra vectores oficiales FIPS 180-4 (NIST) y casos de cadena, PoW, balances, firmas e inmutabilidad.

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
    src/core/Usuario.cpp \
    src/crypto/sha256.cpp

./blockchain
```

### Windows (MinGW-w64)

```powershell
g++ -std=c++17 -O2 -Wall -Wextra `
    -Isrc/core -Isrc/blockchain -Isrc/crypto `
    -o blockchain.exe `
    src/main.cpp src/blockchain/Block.cpp `
    src/blockchain/Blockchain.cpp src/core/Usuario.cpp `
    src/crypto/sha256.cpp

.\blockchain.exe
```

> **Notas de compilación**
> - Todo el código es C++17 estándar y portable: sin `conio.h` ni dependencias de Windows (ramas `#ifdef _WIN32` para `cls`/`clear`).
> - `src/crypto/sha256.h` implementa el hash en la propia cabecera con un guard de inclusión; `sha256.cpp` compila la unidad coherente.
> - El proyecto compila **sin errores y sin warnings** con `-Wall -Wextra` (verificado con GCC 15).

## 🧪 Pruebas

El proyecto incluye una suite en `tests/` con vectores oficiales de SHA-256 (FIPS 180-4) y casos de cadena, PoW, balances, firmas y mutaciones:

```bash
# SHA-256 contra los vectores oficiales FIPS 180-4 (NIST)
g++ -std=c++17 -O2 -Wall -Wextra -Isrc/crypto \
    -o test_sha256 tests/test_sha256.cpp src/crypto/sha256.cpp
./test_sha256

# Blockchain: genesis, PoW, encadenado, comisiones, balances, firmas e inmutabilidad
g++ -std=c++17 -O2 -Wall -Wextra \
    -Isrc/core -Isrc/blockchain -Isrc/crypto \
    -o test_blockchain tests/test_blockchain.cpp \
    src/blockchain/Block.cpp src/blockchain/Blockchain.cpp \
    src/core/Usuario.cpp src/crypto/sha256.cpp
./test_blockchain
```

Salida esperada en ambos: `TODOS LOS TESTS PASARON` (16 comprobaciones en total).

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
| `1` | **Crear cuenta** — genera clave privada aleatoria (6 dígitos) y su clave pública derivada por **SHA-256**. Guárdalas: se muestran una sola vez. |
| `2` | **Ingresar en cuenta** — pide la **clave privada** y valida la sesión (`login`); sin ella no hay cartera. |
| `3` | **Salir** — mina el bloque con todas las transacciones pendientes, imprime la cadena y la valida. |

Dentro de una cuenta:

```
Que desea realizar ?
Realizar Transferencia--(1)
Salir--(2)
```

| Opción | Acción |
|---|---|
| `1` | Registrar una transferencia: pide **dirección del receptor** (su clave pública), **monto** y **comisión del minero**. Se acumula en la lista pendiente. |
| `2` | Volver al menú principal. |

### Ejemplo de sesión

```text
Que desea realizar ? Crear Cuenta--(1)
Cuenta creada con exito.
Tu clave privada es: 297046 - Guardala en un lugar seguro, no se volvera a mostrar.
Tu clave publica (direccion) es: 8bbebe80e7762f0e404a80a3ed5fa113eeedf124d9914bba4b9c5e7c31519c26

Que desea realizar ? Ingresar en Cuenta--(2)
Ingresa tu clave privada: 297046
Sesion abierta. Bienvenido de vuelta.

Que desea realizar ? Realizar Transferencia--(1)
Direccion del receptor (clave publica): 8bbebe80e7762f0e404a80a3ed5fa113eeedf124d9914bba4b9c5e7c31519c26
Cuanto dinero desea enviar ?: 150
Cuanta Comision desea darle al minero ?: 5

Presione ENTER para continuar...

Que desea realizar ? Salir--(3)

00f0d8bb121ea2e8e1f88f3c661227b5e221932da14333063094f7a882b3e556++++++++++++++++13
Block mined: 00f0d8bb121ea2e8e1f88f3c661227b5e221932da14333063094f7a882b3e556

Block ===================================
Index: 0
Nonce: 0
FeeBlock: 0
Hash: 7c5fd242e40ab6f87ed0fa2ce7ab7b2a22962dfbe1d09bb4a15be844016720be
Previous Hash: 0
Is Block Valid?: 1

Block ===================================
Index: 1
Amount: 150.000000
Fee: 5.000000
SenderKey: 8bbebe80e7762f0e404a80a3ed5fa113eeedf124d9914bba4b9c5e7c31519c26
ReceiverKey: 8bbebe80e7762f0e404a80a3ed5fa113eeedf124d9914bba4b9c5e7c31519c26
SenderBalance: -150.000000
ReceiverBalance: 150.000000
Timestamp: 1789437987
Nonce: 13
FeeBlock: 5
Hash: 00f0d8bb121ea2e8e1f88f3c661227b5e221932da14333063094f7a882b3e556
Previous Hash: 7c5fd242e40ab6f87ed0fa2ce7ab7b2a22962dfbe1d09bb4a15be844016720be
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
├── tests/
│   ├── test_sha256.cpp            ← vectores oficiales SHA-256 (FIPS 180-4)
│   └── test_blockchain.cpp        ← genesis, PoW, balances, firmas, mutaciones
├── config/                        (reservado)
├── examples/                      (reservado)
├── scripts/                       (reservado)
└── src/
    ├── main.cpp                   ← CLI: menús, sesión y cierre de cadena
    ├── blockchain/
    │   ├── Blockchain.h/.cpp      ← cadena, génesis, minado y validación
    │   ├── Block.h/.cpp           ← bloque: hash, PoW, fee y liquidación
    │   └── TransactionData.h      ← transacción + saldos + lista enlazada
    ├── core/
    │   ├── Usuario.h/.cpp         ← identidad: claves SHA-256, sesión y saldo
    │   └── Cuenta.h               ← cartera: wallet y balances
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

- [x] **Transacciones reales**: la transferencia usa la clave pública del usuario logueado como `senderKey` (verificación de sesión por clave privada) y las firmas inválidas se consignan con `LLAVE_FALLIDA` (`_ComprobationKey`).
- [x] **Balances**: cada transacción liquida `senderAmount`/`receiverAmount` al minar el bloque (`EFECTUAR INTERCAMBIO DE MONTOS`) y `Cuenta` expone la cartera.
- [x] **Hash portable**: el bloque se hashea directamente con SHA-256, sin el `std::hash` intermedio (no estándar) → hashes reproducibles entre plataformas.
- [x] **Pruebas**: `tests/` con vectores oficiales SHA-256 (FIPS 180-4) y casos de cadena, PoW, balances, firmas y mutaciones.
- [ ] **Múltiples bloques**: hoy la consola consolida todo en un bloque al salir; permitir cerrar/minar bloques de forma incremental.
- [ ] **Persistencia**: volcar la cadena a disco (`*.json`, SQLite) — `.gitignore` ya reserva rutas `*.db`.
- [ ] **Mejoras**: `system("clear")` por códigos ANSI, smart pointers para la propiedad de bloques y una criptografía de firma real (ECDSA/Ed25519).

## ⚠️ Advertencia

Proyecto **educativo**: la implementación criptográfica y el consenso son simplificados (PoW de dificultad 2, SHA-256 didáctico con bits como texto, cadena en memoria, firma por hash de la clave privada en lugar de ECDSA). **No usar en producción ni manejar valor real.**

## 📄 Licencia

Sin licencia declarada todavía — todos los derechos reservados a su autor.

---

<div align="center">
Hecho con C++17 · <a href="docs/ARCHITECTURE.md">Ver arquitectura completa</a>
</div>

