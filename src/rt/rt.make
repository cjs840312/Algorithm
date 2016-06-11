all : ../../lib/libRt.a

<<<<<<< HEAD:src/rt/make.rt
../../lib/libRt.a : ../../obj/parse_block.o ../../obj/cmdRt.o ../../obj/parse_v.o ../../obj/parse_tech.o 
=======
../../lib/libRt.a : ../../obj/parse_block.o ../../obj/cmdRt.o ../../obj/parse_v.o \
						 ../../obj/graph.o ../../obj/modulize.o ../../obj/routing.o
>>>>>>> 731b94615b0f532951ce5d51b0db0d6c1bcde508:src/rt/rt.make
	@echo -n " > making library libRt.a ...     "
	@ar -rcs $@ $^
	@echo "Success !!"

../../obj/cmdRt.o : cmdRt.cpp cmdRt.h
	@echo -n " > compilng cmdRt.cpp ...         "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/parse_block.o : parse_block.cpp RtMgr.h
	@echo -n " > compilng parse_block.cpp ...   "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/parse_v.o : parse_v.cpp RtMgr.h
	@echo -n " > compilng parse_block.cpp ...   "
	@g++ -c $< -o $@
	@echo "Success !!"

<<<<<<< HEAD:src/rt/make.rt
../../obj/parse_tech.o : parse_tech.cpp RtMgr.h
	@echo -n " > compilng parse_tech.cpp ...   "
	@g++ -c $< -o $@
	@echo "Success !!"
=======
../../obj/graph.o : graph.cpp graph.h
	@echo -n " > compilng graph.cpp ...         "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/modulize.o : modulize.cpp RtMgr.h
	@echo -n " > compilng modulize.cpp ...      "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/routing.o : routing.cpp RtMgr.h
	@echo -n " > compilng routing.cpp ...       "
	@g++ -c $< -o $@
	@echo "Success !!"
>>>>>>> 731b94615b0f532951ce5d51b0db0d6c1bcde508:src/rt/rt.make
