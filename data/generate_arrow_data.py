import pyarrow as pa
import pyarrow.ipc as ipc

# Sample data
data = {
    "region": ["US", "US", "EU", "ASIA", "US", "EU"],
    "sales": [100.0, 200.0, 150.0, 130.0, 120.0, 180.0]
}

# Create table
table = pa.table(data)

# Write to IPC (Feather v2 compatible)
with pa.OSFile("transactions.arrow", "wb") as sink:
    with ipc.new_file(sink, table.schema) as writer:
        writer.write_table(table)
        