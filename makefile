all : bin obj lib output bin/cmd
	@echo "\nCompile complete !!\n"

bin :
	@echo -n " > making directory \"bin\" ...    "
	@mkdir -p bin
	@echo "Success !!"

obj :
	@echo -n " > making directory \"obj\" ...    "
	@mkdir -p obj
	@echo "Success !!"

lib :
	@echo -n " > making directory \"lib\" ...    "
	@mkdir -p lib
	@echo "Success !!"

output :
	@echo -n " > making directory \"output\" ... "
	@mkdir -p output
	@echo "Success !!"

bin/cmd : obj/main.o 
	@cd src/cmd ;make -f make.cmd;
	@echo -n " > linking object files ...        "
	@g++  $^ -o $@ -Llib -lCmd
	@echo "Success !!"

obj/main.o : src/main.cpp src/cmd/cmd.h src/util/help_function.h src/util/myUsage.h
	@echo -n " > compilng main.cpp ...           "
	@g++ -c $< -o $@
	@echo "Success !!"
	
clean :
	@echo -n "deleting binary file ...           "
	@rm -f bin/*
	@echo "Success !!"

	@echo -n "deleting object file ...           " 
	@rm -f obj/*
	@echo "Success !!"

	@echo -n "deleting libaray file ...          " 
	@rm -f lib/*
	@echo "Success !!"
