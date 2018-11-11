# GraphCli 

Zawiera binarkę pozwalającą na łatwe tworzenie grafów wejściowych.

cli kieruje jakie komendy wpisywać i jakie flagi są opcjonalne/wymagane ale kilka przykładów poniżej


Przykłady tworzenia grafów


./GraphCli create random -v 10 -o rand10 -p 0.3

./GraphCli create full -v 5 -o full6 

Przykład wyświetlania grafu

./GraphCli show -i full5

# Calculations

implementacja algorytmów

make build tworzy nam binarkę

odpalamy ją: 

./commonSubgraph <p1> <p2> //p1 i p2 to ścieżki do dumpów grafów zgodnych z konwencją tworzoną przez GraphCli

