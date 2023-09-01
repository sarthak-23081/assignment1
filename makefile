debug: q1.cpp
	g++ -Wall -g -o final_debug MT23081_assignment1.cpp
optimized: q1.cpp
	g++ -Wall -O2 -o final_optimized MT23081_assignment1.cpp
clean:
	rm -f *.o final_debug final_optimized