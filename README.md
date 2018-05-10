# cppMarkov
Yet another markov chain library

### Examples:


```c++ 
#include "markov.h"


Markov<int> markov2 {1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0};

int j=30;
for(auto i: markov2){
    cout << i;

    if(!--j) break;
}
cout << "\n";
 ```
    
Output: `111000011111000011111111111011`

----


```c++
Markov<char> markov3 {'l','o','l','o'};

int j=30;
for(auto i: markov3){
    cout << i;

    if(!--j) break;
}
cout << "\n";
```
Output: `lololololololololololololololo`
    
----


```c++
std::string data=R"(Nel mezzo del cammin di nostra vita
mi ritrovai per una selva oscura,
ché la diritta via era smarrita.
Ahi quanto a dir qual era è cosa dura
esta selva selvaggia e aspra e forte
che nel pensier rinova la paura!
Tant' è amara che poco è più morte;
ma per trattar del ben ch'i' vi trovai,
dirò de l'altre cose ch'i' v'ho scorte.
Io non so ben ridir com' i' v'intrai,
tant' era pien di sonno a quel punto
che la verace via abbandonai.
Ma poi ch'i' fui al piè d'un colle giunto,
là dove terminava quella valle
che m'avea di paura il cor compunto,
guardai in alto e vidi le sue spalle
vestite già de' raggi del pianeta
che mena dritto altrui per ogne calle.)";



Markov<std::string> markov;

markov.train(data);
markov.set_start_state("^"); //special charachters for line begin/end
markov.set_stop_state("$");

for(auto i: markov){
    cout << i << " ";
}

cout << "\n";

```

Output: `^ Ahi quanto a dir qual era pien di nostra vita `
