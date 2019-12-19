# RULES
compile :
	g++ main.cpp panel.cpp os_info.cpp -o main `pkg-config gtkmm-3.0 --cflags --libs`

execute :
	./main

clean :
	rm -f main

# .PHONY TARGET
.PHONY :