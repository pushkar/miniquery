#!/bin/bash

# Local test script that mimics the GitHub workflow
set -e

echo "🧪 Running local tests..."

# Check if we're in the right directory
if [ ! -f "CMakeLists.txt" ]; then
    echo "❌ Error: CMakeLists.txt not found. Please run this script from the project root."
    exit 1
fi

# Generate test data
echo "📊 Generating test data..."
cd data
if ! python -c "import pyarrow" 2>/dev/null; then
    echo "⚠️  pyarrow not found. Installing..."
    pip install pyarrow
fi
python generate_arrow_data.py
cd ..

# Build main project
echo "🔨 Building main project..."
mkdir -p build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make -j$(nproc)
cd ..

# Test main project
echo "🧪 Testing main project..."
cd build
./neutrino ../data/transactions.arrow "SELECT sales WHERE region = 'US'"
cd ..

# Build playground
echo "🎮 Building playground..."
cd playground
make clean
make
cd ..

# Test playground
echo "🧪 Testing playground..."
cd playground
./ipc_scan
cd ..

# Verify compile_commands.json
echo "📋 Verifying compile_commands.json..."
if [ -f "build/compile_commands.json" ]; then
    echo "✅ compile_commands.json generated successfully"
else
    echo "❌ compile_commands.json not found"
    exit 1
fi

echo "�� All tests passed!" 