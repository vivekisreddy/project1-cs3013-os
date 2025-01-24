prolific: prolific.c
	gcc -o prolific prolific.c

clean:
	rm -f prolific

generation: generation.c
	gcc -o generation generation.c

clean:
	rm -f generation