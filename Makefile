# RULES
compile :
	g++ main.cpp panel.cpp os_info.cpp -o main -I /usr/include/python3.6m -lpython3.6m `pkg-config gtkmm-3.0 --cflags --libs`

execute :
	./main

clean :
	rm -f main

# .PHONY TARGET
.PHONY :