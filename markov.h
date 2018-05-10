#ifndef MARKOV_H
#define MARKOV_H
#include <iostream>
#include <map>
#include <unordered_map>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>

template<class T>
class Markov{
public:
    std::unordered_map<T,std::map<T,unsigned int>> matrix; // not really a matrix
    T current_state;
    T start_state, stop_state;
    bool stop_state_exists=false;

    Markov(){
        srand(time(NULL));
    }

    Markov(std::initializer_list<T> l){
        start_state=*l.begin();
        train(static_cast<std::vector<T>>(l));
    }


    void train(std::vector<T> dataset){
        T stato=*dataset.begin();

        bool first=true;
        for(auto word: dataset){
            if(first){
                first=false;
                continue;
            }
            matrix[stato][word]++;
            stato=word;
        }
    }

    void train(std::string data_){

        std::istringstream data(data_);
        std::string line;
        std::vector<std::string> dataset;

        while (std::getline(data, line))
        {
            std::istringstream iss(line);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

            dataset.push_back("^");
            for(auto word: tokens){
                dataset.push_back(word);
            }
            dataset.push_back("$");
        }

        train(dataset);
    }


    T find_next(T stato){

        int sum=0;

        //finds total number of cases
        for(auto const i: matrix[stato]){
            sum+=i.second;
        }

        assert(sum>=1);


        auto random_integer = rand()%sum;

        //picks a case
        for(auto i: matrix[stato]){
            random_integer-=i.second;

            if(random_integer<=0){
                stato=i.first;
                break;
            }
        }

        current_state=stato;
        return stato;

    }

    std::vector<T> run(){
        std::vector<T> ret;
        auto stato = start_state;

        while(1){

            stato=find_next(stato);

            if(stop_state_exists&&stato==stop_state)
                break;

            ret.push_back(stato);
        }

        return ret;
    }

    void print_matrix(){
        for(auto riga: matrix){
            std::cout << "{\"" << riga.first << "\", {";
            for(auto riga2: riga.second){
                std::cout << "{\"" <<riga2.first << "\", " << riga2.second << "}, ";
            }
            std::cout << "} },\n";
        }
        std::cout << std::endl;
    }


    class iterator {
        friend class Markov;
    public:
        T operator *() const {
            return i_.current_state;
        }

        const iterator &operator ++() {
            i_.find_next(i_.current_state);
            return *this;
        }

        iterator operator ++(int) {
            iterator copy(*this);
            i_.find_next(i_.current_state);
            return copy;
        }


        bool operator !=(const iterator &other) const {
            if(i_.stop_state_exists)
                return i_.current_state != other.i_.current_state;
            else
                return true;
        }

    protected:
        iterator(Markov start) : i_ (start) {
        }

    private:
        Markov i_;
    };

    iterator begin() const {
        Markov copy(*this);
        copy.current_state=start_state;
        return iterator(copy);
    }

    iterator end() const {
        Markov copy(*this);
        copy.current_state=stop_state;
        return iterator(copy);
    }

    void set_start_state(const T &value)
    {
        start_state = value;
    }

    void set_stop_state(const T &value)
    {
        stop_state_exists=true;
        stop_state = value;
    }

};



#endif // MARKOV_H
