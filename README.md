# ⚛️ Neutrino

A tiny, fast, Photon-style query engine built in C++ using Apache Arrow.

**Neutrino** is an experimental vectorized execution engine that reads Arrow IPC files, supports simple SQL queries (`SELECT col WHERE col = 'val'`), and runs them through a custom scan + filter pipeline.

---

## 🚀 Features

- Columnar storage access via Arrow IPC
- Simple SQL-like parsing and execution
- Vectorized predicate filtering
- Modular execution architecture
- Photon-style SIMD-ready design

---

## 📂 Example Query

```bash
./neutrino data/transactions.arrow "SELECT sales WHERE region = 'US'"

Total sales (region = 'US'): 420
```