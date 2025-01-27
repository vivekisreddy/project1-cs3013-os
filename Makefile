CC = gcc
CFLAGS = -Wall
PROGRAMS = prolific explorer generation slug slugrace

all: $(PROGRAMS)
	@echo "All programs built successfully."


prolific: prolific.c
	$(CC) $(CFLAGS) -o prolific prolific.c
	@echo "Built prolific."

explorer: explorer.c
	$(CC) $(CFLAGS) -o explorer explorer.c
	@echo "Built explorer."

generation: generation.c
	$(CC) $(CFLAGS) -o generation generation.c
	@echo "Built generation."

slug: slug.c
	$(CC) $(CFLAGS) -o slug slug.c
	@echo "Built slug."

slugrace: slugrace.c
	$(CC) $(CFLAGS) -o slugrace slugrace.c
	@echo "Built slugrace."

clean:
	rm -f $(PROGRAMS)
	@echo "Cleaned up all executables."

run_prolific:
	./prolific

run_explorer:
	./explorer

run_generation:
	./generation

run_slug:
	./slug

run_slugrace:
	./slugrace
