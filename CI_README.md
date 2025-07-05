# CI/CD Setup for Miniquery

This project includes comprehensive GitHub Actions workflows for continuous integration and testing.

## 🚀 Workflows

### 1. Quick Test (`quick-test.yml`)
A lightweight workflow that runs on Ubuntu and tests the essential functionality:
- Builds the main project with CMake
- Tests the playground code
- Generates test data
- Runs basic functionality tests

**Triggers:** Push to main, Pull requests to main

### 2. Full CI (`ci.yml`)
A comprehensive workflow that tests across multiple platforms and configurations:
- **Platforms:** Ubuntu, macOS, Windows
- **Compilers:** GCC, Clang
- **Tests:** Main project, playground, code quality, documentation

**Jobs:**
- `test`: Matrix testing on Ubuntu/macOS with different compilers
- `test-windows`: Windows testing with vcpkg
- `lint`: Code formatting and CMake syntax checks
- `docs`: Documentation validation

## 🧪 Local Testing

### Run Local Tests
```bash
# Run the local test script (mimics GitHub workflow)
./scripts/test-local.sh
```

### Manual Testing Steps
```bash
# 1. Generate test data
cd data
pip install pyarrow
python generate_arrow_data.py
cd ..

# 2. Build main project
mkdir -p build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make -j$(nproc)
cd ..

# 3. Test main project
cd build
./neutrino ../data/transactions.arrow "SELECT sales WHERE region = 'US'"
cd ..

# 4. Build and test playground
cd playground
make clean
make
./ipc_scan
cd ..
```

## 📋 Prerequisites

### For Local Development
- CMake 3.15+
- C++17 compatible compiler (GCC 7+, Clang 5+)
- Apache Arrow (installed via conda or system package manager)
- Python with pyarrow for data generation

### For CI/CD
- GitHub Actions runners with the specified OS versions
- Conda for Arrow installation (handled automatically)
- vcpkg for Windows builds (handled automatically)

## 🔧 Configuration

### Code Formatting
The project uses `.clang-format` for consistent code formatting:
```bash
# Format all C++ files
find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### Compile Commands
The CMake configuration generates `compile_commands.json` for language servers:
```bash
# Enable compile commands generation
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

## 🐛 Troubleshooting

### Common Issues

1. **Arrow not found**: Install via conda:
   ```bash
   conda install -c conda-forge arrow-cpp
   ```

2. **Compilation errors**: Ensure C++17 is enabled:
   ```bash
   cmake -DCMAKE_CXX_STANDARD=17 ..
   ```

3. **Test data missing**: Regenerate test data:
   ```bash
   cd data && python generate_arrow_data.py
   ```

### CI Debugging

- Check workflow logs in GitHub Actions
- Use the local test script to reproduce issues
- Verify Arrow installation and version compatibility

## 📊 Workflow Status

The workflows will show:
- ✅ **Green**: All tests passed
- ❌ **Red**: Tests failed (check logs for details)
- 🟡 **Yellow**: Some jobs failed (partial success)

## 🔄 Adding New Tests

To add new tests to the CI:

1. **Add to local test script** (`scripts/test-local.sh`)
2. **Add to GitHub workflow** (`.github/workflows/ci.yml`)
3. **Update this documentation**

Example:
```yaml
- name: Run new test
  run: |
    cd new-test-directory
    make test
```

## 📝 Notes

- The Windows workflow is optional and may be slower
- Code formatting is enforced in the lint job
- All workflows generate compile_commands.json for IDE support
- Test data is regenerated in each workflow run to ensure consistency 