all: bankers

run: bankers
	@./bankers.out

bankers:
	@rm -f bankers.out
	@gcc bankers.c -lpthread -o bankers.out

clean:
	@rm *.out
