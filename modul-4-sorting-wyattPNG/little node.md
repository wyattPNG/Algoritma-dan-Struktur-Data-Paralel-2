# Sorting Algorithm Lab

## Struktur File

```
sorting/
├── main.cpp                    # runner utama — jangan diubah
├── metrics.h                   # definisi struct Metrics — jangan diubah
├── data_generator.h/.cpp       # generator data — jangan diubah
├── reporter.h/.cpp             # output tabel — jangan diubah
└── sorting_algorithms.cpp      # <-- file yang kalian kerjakan
```

---

## Cara Compile & Run

```bash
g++ -O2 main.cpp data_generator.cpp sorting_algorithms.cpp reporter.cpp -o sort && ./sort
```
---

## Tugas

Implementasi semua algoritma sorting di dalam `sorting_algorithms.cpp`.

Setiap fungsi sudah memiliki kerangka timer — **jangan ubah atau pindahkan** baris `auto start` dan `m.time_ms`.

---

## Metrik per Algoritma

### `m.comparisons++`
Tambahkan setiap kali **dua elemen dibandingkan** (`>`, `<`, `==`).

### `m.swaps++`
Tambahkan setiap kali **dua elemen ditukar** (`std::swap`).

### `m.shifts++`
Tambahkan setiap kali **satu elemen digeser** satu posisi (assignment, bukan swap).
Digunakan di Insertion Sort dan Shell Sort — karena keduanya menggeser, bukan menukar.

### `m.recursive_calls++`
Tambahkan **di awal** setiap pemanggilan fungsi rekursif.
Digunakan di Merge Sort dan Quick Sort.

### `m.array_accesses++`
Tambahkan setiap kali **mengakses array count[] atau output[]**.
Digunakan di Counting Sort dan Radix Sort sebagai pengganti comparisons.

---

## Ringkasan Metrik per Fungsi

| Fungsi          | comparisons | swaps | shifts | recursive_calls | array_accesses |
|-----------------|:-----------:|:-----:|:------:|:---------------:|:--------------:|
| `bubbleSort`    | ✓           | ✓     |        |                 |                |
| `selectionSort` | ✓           | ✓     |        |                 |                |
| `insertionSort` | ✓           |       | ✓      |                 |                |
| `mergeSort`     | ✓           |       |        | ✓               |                |
| `quickSort`     | ✓           | ✓     |        | ✓               |                |
| `radixSort`     |             |       |        |                 | ✓              |