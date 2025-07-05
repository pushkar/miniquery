CXX = g++
CXXFLAGS = -std=c++17
PKG_CONFIG_FLAGS = $(shell pkg-config --cflags --libs arrow)

ipc_scan: ipc_scan.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(PKG_CONFIG_FLAGS)

clean:
	rm -f ipc_scan