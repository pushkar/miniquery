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

Generate data
```
bash
cd data
pip install pyarrow
python generate_arrow_data.py
```

Run the query engine
```bash
cmake --build build
./build/neutrino ./data/transactions.arrow "SELECT sales WHERE region = 'US'"

Total sales (region = 'US'): 420
```

## Todo

- Integrate Apache Arrow Compute kernels for filter/projection
- Implement partition-aware reading
- Build a query planner module
- Optimize with SIMD or multithreading