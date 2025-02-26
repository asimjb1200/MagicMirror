CXX = g++
LDFLAGS = `pkg-config --cflags --libs gtkmm-4.0`
SRC = MagicMirror.cc
OUT = my_smart_mirror
STD = -std=c++17

all:
	$(CXX) $(SRC) -o $(OUT) $(LDFLAGS) $(STD)

clean:
	rm -f $(OUT)
