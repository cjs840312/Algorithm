all : ../../lib/libBmp.a

../../lib/libBmp.a : ../../obj/bmp_file.o ../../obj/read_array.o ../../obj/read_file.o
	@echo -n " > making library libBmp.a ...    "
	@ar -rcs $@ $^
	@echo "Success !!"

../../obj/bmp_file.o : bmp_file.cpp bmp_file.h
	@echo -n " > compilng bmp_file.cpp ...      "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/read_file.o : read_file.cpp bmp_file.h
	@echo -n " > compilng read_file.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/read_array.o : read_array.cpp bmp_file.h
	@echo -n " > compilng read_array.cpp ...    "
	@g++ -c $< -o $@
	@echo "Success !!"

clean :
	rm -f a.out *.o