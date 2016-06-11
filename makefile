all : dir bin/cmd
	@echo "\nCompile complete !!\n"

dir :
	@echo    "checking directories ..."
	@mkdir -p bin obj lib output

bin/cmd : obj/main.o library
	@echo -n " > linking object files ...       "
	@g++  $< -o $@ -Llib -lCmd -lRt -lBmp
	@echo "Success !!"

library :
	@echo    "checking libcmd.a ..."
	@cd src/cmd ;make -f cmd.make --no-print-directory --silent;
	
	@echo    "checking libRt.a ..."
	@cd src/rt ;make -f rt.make --no-print-directory --silent;

	@echo    "checking libBmp.a ..."
	@cd src/bmp ;make -f bmp.make --no-print-directory --silent;

obj/main.o : src/main.cpp src/cmd/cmd.h src/util/help_function.h src/util/myUsage.h
	@echo -n " > compilng main.cpp ...          "
	@g++ -c $< -o $@
	@echo "Success !!"
	
clean :
	@echo -n "cleaning bin/ obj/ lib/ ...       "
	@rm -f bin/* obj/* lib/*
	@echo "Success !!"

