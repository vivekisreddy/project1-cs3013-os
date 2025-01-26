prolific: prolific.c
	gcc -o prolific prolific.c

clean:
	rm -f prolific

explorer: explorer.c
	gcc -o explorer explorer.c

clean:
	rm -f explorer
  
generation: generation.c
	gcc -o generation generation.c

clean:
	rm -f generation

generation: slug.c
	gcc -o slug slug.c

clean:
	rm -f slug

