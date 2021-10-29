CC:=gcc
exe_queue:=main_queue
exe_stack:=main_stack
obj_queue:=main_queue.o queue.o list.o mm.o
obj_stack:=main_stack.o stack.o list.o mm.o
src:=queue.h stack.h list.h mm.h

all: $(obj_queue) $(obj_stack) $(src)
	$(CC) -o $(exe_queue) $(obj_queue)
	$(CC) -o $(exe_stack) $(obj_stack)
%.o: %.c
	$(CC) -c -o $@ $<

	
.PHONY:clean
clean:
	rm -rf $(obj_queue) $(exe_queue) $(obj_stack) $(exe_stack)

